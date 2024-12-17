#include "l1cacheshim.h"
#include "processorhandler.h"

namespace Ripes {

L1CacheShim::L1CacheShim(CacheType type, QObject *parent)
    : CacheInterface(parent), m_type(type) {
  if (type == CacheType::L2Cache) {
    m_l2Cache = std::make_shared<L2CacheSim>(this);
  } else if (type == CacheType::L3Cache) {
    m_l3Cache = std::make_shared<L3CacheSim>(this);
  }

  connect(ProcessorHandler::get(), &ProcessorHandler::processorReset, this,
          &L1CacheShim::processorReset);
  connect(ProcessorHandler::get(), &ProcessorHandler::processorClocked, this,
          &L1CacheShim::processorWasClocked, Qt::DirectConnection);
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReversed, this,
          &L1CacheShim::processorReversed);

  processorReset();
}

void L1CacheShim::processorWasClocked() {
  if (m_type == CacheType::DataCache) {
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();

    switch (dataAccess.type) {
    case MemoryAccess::Write:
      if (m_nextLevelCache) {
        m_nextLevelCache->access(dataAccess.address, MemoryAccess::Write);
      }
      break;
    case MemoryAccess::Read:
      if (m_l2Cache) {
        m_l2Cache->access(dataAccess.address, MemoryAccess::Read);
      }
      break;
    default:
      break;
    }
  } else if (m_type == CacheType::InstrCache) {
    const auto instrAccess = ProcessorHandler::getProcessor()->instrMemAccess();
    if (instrAccess.type == MemoryAccess::Read) {
      if (m_l2Cache) {
        m_l2Cache->access(instrAccess.address, MemoryAccess::Read);
      }
    }
  } else if (m_type == CacheType::L3Cache) {
    // Handle L3 cache access if needed
  }
}

void L1CacheShim::processorReset() {
  CacheInterface::reset();

  if (m_l2Cache) {
    m_l2Cache->reset();
  }

  if (m_l3Cache) {
    m_l3Cache->reset();
  }

  processorWasClocked();
}

} // namespace Ripes
