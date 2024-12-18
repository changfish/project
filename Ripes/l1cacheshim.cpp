#include "l1cacheshim.h"
#include "processorhandler.h"

namespace Ripes {

L1CacheShim::L1CacheShim(CacheType type, QObject *parent)
    : CacheInterface(parent), m_type(type) {
  // Initialize L2 cache as part of L1 cache setup
  m_l2Cache = std::make_unique<L2Cache>(this);

  connect(ProcessorHandler::get(), &ProcessorHandler::processorReset, this,
          &L1CacheShim::processorReset);

  connect(ProcessorHandler::get(), &ProcessorHandler::processorClocked, this,
          &L1CacheShim::processorWasClocked, Qt::DirectConnection);
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReversed, this,
          &L1CacheShim::processorReversed);

  processorReset();
}

void L1CacheShim::access(AInt address, MemoryAccess::Type type) {
  if (!isHit(address)) {
    updateStats(false); // L1 miss
    m_l2Cache->access(address, type); // Forward to L2 cache
  } else {
    updateStats(true); // L1 hit
  }
}

void L1CacheShim::processorReset() {
  CacheInterface::reset();
  m_l2Cache->reset(); // Reset L2 cache
}

void L1CacheShim::processorReversed() {
  CacheInterface::reverse();
  m_l2Cache->reverse(); // Reverse L2 cache state
}

void L1CacheShim::processorWasClocked() {
  const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();
  if (m_type == CacheType::DataCache && dataAccess.type != MemoryAccess::None) {
    access(dataAccess.address, dataAccess.type);
  }
}

} // namespace Ripes
