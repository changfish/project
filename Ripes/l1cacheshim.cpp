#include "l1cacheshim.h"
#include "processorhandler.h"

namespace Ripes {

L1CacheShim::L1CacheShim(CacheType type, QObject *parent)
    : CacheInterface(parent), m_type(type) {
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReset, this,
          &L1CacheShim::processorReset);

  connect(ProcessorHandler::get(), &ProcessorHandler::processorClocked, this,
          &L1CacheShim::processorWasClocked, Qt::DirectConnection);
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReversed, this,
          &L1CacheShim::processorReversed);

  processorReset();
}

void L1CacheShim::access(AInt, MemoryAccess::Type) {
  Q_ASSERT(false);
}

void L1CacheShim::processorReset() {
  CacheInterface::reset();

  if (m_nextLevelCache) {
    processorWasClocked();
  }
}

void L1CacheShim::processorReversed() {
  CacheInterface::reverse();
}

void L1CacheShim::processorWasClocked() {
  if (m_type == CacheType::DataCache) {
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();

    if (dataAccess.type == MemoryAccess::Write || dataAccess.type == MemoryAccess::Read) {
      m_nextLevelCache->access(dataAccess.address, dataAccess.type);

      if (m_l2Cache) {
        m_l2Cache->access(dataAccess.address, dataAccess.type);
      }
    }
  } else {
    const auto instrAccess = ProcessorHandler::getProcessor()->instrMemAccess();

    if (instrAccess.type == MemoryAccess::Read) {
      m_nextLevelCache->access(instrAccess.address, MemoryAccess::Read);

      if (m_l2Cache) {
        m_l2Cache->access(instrAccess.address, MemoryAccess::Read);
      }
    }
  }
}

} // namespace Ripes
