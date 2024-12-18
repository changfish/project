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
  if (!isHit(address)) {
    updateStats(false); // L1 miss
  } else {
    updateStats(true); // L1 hit
  }
}

void L1CacheShim::processorReset() {
  CacheInterface::reset(); // 這是 CacheInterface 中的函數，已經有實作

  // 如果有需要，可以添加 L2Cache 相關重置邏輯
}

void L1CacheShim::processorReversed() {
  CacheInterface::reverse(); // 這是 CacheInterface 中的函數，已經有實作
}

void L1CacheShim::processorWasClocked() {
  if (m_type == CacheType::DataCache) {
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();

    switch (dataAccess.type) {
    case MemoryAccess::Write:
      m_nextLevelCache->access(dataAccess.address, MemoryAccess::Write);
      break;
    case MemoryAccess::Read:
      m_nextLevelCache->access(dataAccess.address, MemoryAccess::Read);
      break;
    case MemoryAccess::None:
    default:
      break;
    }
  } else {
    const auto instrAccess = ProcessorHandler::getProcessor()->instrMemAccess();
    if (instrAccess.type == MemoryAccess::Read) {
      m_nextLevelCache->access(instrAccess.address, MemoryAccess::Read);
    }
  }
}

bool L1CacheShim::isHit(AInt address) {
  // 應根據具體情境實作命中檢查邏輯
  // 返回 true 或 false，根據該地址是否命中快取
  // 這段邏輯需要根據具體需求進行調整
  return false; // 示例：檢查地址是否命中某快取
}

void L1CacheShim::updateStats(bool hit) {
  // 更新快取命中/未命中統計資訊
  if (hit) {
    // L1 hit statistics
  } else {
    // L1 miss statistics
  }
}

} // namespace Ripes
