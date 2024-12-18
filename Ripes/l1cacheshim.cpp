#include "l1cacheshim.h"
#include "processorhandler.h"

namespace Ripes {

L1CacheShim::L1CacheShim(CacheType type, QObject *parent)
    : CacheInterface(parent), m_type(type), m_l2Cache(std::make_unique<L2Cache>()) {
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReset, this, &L1CacheShim::processorReset);
  connect(ProcessorHandler::get(), &ProcessorHandler::processorClocked, this, &L1CacheShim::processorWasClocked, Qt::DirectConnection);
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReversed, this, &L1CacheShim::processorReversed);

  processorReset();
}

void L1CacheShim::access(AInt address, MemoryAccess::Type type) {
  if (!m_l2Cache->isHit(address)) {
    updateStats(false); // L1 miss, go to L2
    m_l2Cache->access(address, type); // L2 access
    updateStats(true);  // L1 hit after L2 access
  } else {
    updateStats(true); // L1 hit
  }
}

void L1CacheShim::processorReset() {
  CacheInterface::reset();
  m_l2Cache->reset(); // Reset the L2 cache
  processorWasClocked();
}

void L1CacheShim::processorReversed() {
  CacheInterface::reverse();
  m_l2Cache->reverse(); // Reverse operation for L2 cache
}

void L1CacheShim::processorWasClocked() {
  if (m_type == CacheType::DataCache) {
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();
    if (dataAccess.type == MemoryAccess::Read) {
      m_l2Cache->access(dataAccess.address, MemoryAccess::Read);
    } else if (dataAccess.type == MemoryAccess::Write) {
      m_l2Cache->access(dataAccess.address, MemoryAccess::Write);
    }
  } else {
    const auto instrAccess = ProcessorHandler::getProcessor()->instrMemAccess();
    if (instrAccess.type == MemoryAccess::Read) {
      m_l2Cache->access(instrAccess.address, MemoryAccess::Read);
    }
  }
}

} // namespace Ripes
