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

void L1CacheShim::access(AInt address, MemoryAccess::Type type) {
  if (m_type == CacheType::DataCache || m_type == CacheType::InstrCache) {
    // L1 Cache 訪問邏輯
    if (m_nextLevelCache) {
      m_nextLevelCache->access(address, type);
    }
  } else if (m_type == CacheType::L2Cache) {
    // 訪問 L2 Cache
    if (m_l2Cache) {
      m_l2Cache->access(address, type);
    }
  } else if (m_type == CacheType::L3Cache) {
    // 訪問 L3 Cache
    if (m_l3Cache) {
      m_l3Cache->access(address, type);
    }
  } else {
    Q_ASSERT(false); // 無效的快取類型
  }
}

void L1CacheShim::processorReset() {
  CacheInterface::reset();

  if (m_nextLevelCache) {
    processorWasClocked();
  }

  // 初始化 L2 和 L3 Cache
  if (m_type == CacheType::L2Cache) {
    m_l2Cache->reset();
  } else if (m_type == CacheType::L3Cache) {
    m_l3Cache->reset();
  }
}

void L1CacheShim::processorReversed() {
  CacheInterface::reverse();
  
  if (m_type == CacheType::L2Cache) {
    m_l2Cache->reverse();
  } else if (m_type == CacheType::L3Cache) {
    m_l3Cache->reverse();
  }
}

void L1CacheShim::processorWasClocked() {
  if (m_type == CacheType::DataCache || m_type == CacheType::InstrCache) {
    // 根據 L1 Cache 訪問邏輯
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();
    if (dataAccess.type == MemoryAccess::Read) {
      m_nextLevelCache->access(dataAccess.address, MemoryAccess::Read);
    } else if (dataAccess.type == MemoryAccess::Write) {
      m_nextLevelCache->access(dataAccess.address, MemoryAccess::Write);
    }
  } else if (m_type == CacheType::L2Cache) {
    // L2 Cache 訪問邏輯
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();
    m_l2Cache->access(dataAccess.address, dataAccess.type);
  } else if (m_type == CacheType::L3Cache) {
    // L3 Cache 訪問邏輯
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();
    m_l3Cache->access(dataAccess.address, dataAccess.type);
  }
}
