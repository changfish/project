#include "l1cacheshim.h"
#include "processorhandler.h"
#include "l2cachesim.h"

namespace Ripes {

L1CacheShim::L1CacheShim(CacheType type, QObject *parent)
    : CacheInterface(parent), m_type(type) {
  // 初始化 L2 Cache
  m_l2Cache = std::make_shared<L2CacheSim>(this);

  connect(ProcessorHandler::get(), &ProcessorHandler::processorReset, this,
          &L1CacheShim::processorReset);

  // We must update the cache statistics on each cycle, in lockstep with the
  // processor itself. Connect to ProcessorHandler::processorClocked and ensure
  // that the handler is executed in the thread that the processor lives in
  // (direct connection).
  connect(ProcessorHandler::get(), &ProcessorHandler::processorClocked, this,
          &L1CacheShim::processorWasClocked, Qt::DirectConnection);
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReversed, this,
          &L1CacheShim::processorReversed);

  processorReset();
}

void L1CacheShim::access(AInt, MemoryAccess::Type) {
  // Should never occur; the shim determines accesses based on investigating the
  // associated memory.
  Q_ASSERT(false);
}

void L1CacheShim::processorReset() {
  // Propagate a reset through the cache hierarchy
  CacheInterface::reset();

  if (m_l2Cache) {
    // Reload the initial (cycle 0) state of the processor.
    processorWasClocked();
  }
}

void L1CacheShim::processorReversed() {
  // Start propagating a reverse call through the cache hierarchy
  CacheInterface::reverse();
}

void L1CacheShim::processorWasClocked() {
  if (m_type == CacheType::DataCache) {
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();

    // Determine whether the memory is being accessed in the current cycle, and
    // if so, the access type.
    switch (dataAccess.type) {
    case MemoryAccess::Write:
      handleL1Access(dataAccess.address, MemoryAccess::Write);
      break;
    case MemoryAccess::Read:
      handleL1Access(dataAccess.address, MemoryAccess::Read);
      break;
    case MemoryAccess::None:
    default:
      break;
    }
  } else {
    const auto instrAccess = ProcessorHandler::getProcessor()->instrMemAccess();
    if (instrAccess.type == MemoryAccess::Read) {
      handleL1Access(instrAccess.address, MemoryAccess::Read);
    }
  }
}

// L1 Cache Access Handling
void L1CacheShim::handleL1Access(AInt address, MemoryAccess::Type type) {
  static std::unordered_set<AInt> l1CacheLines;

  if (l1CacheLines.find(address) != l1CacheLines.end()) {
    // Cache hit in L1
    emit cacheEvent(CacheEvent::Hit, address);
  } else {
    // Cache miss in L1
    emit cacheEvent(CacheEvent::Miss, address);

    // Insert into L1 cache (evict if needed)
    if (l1CacheLines.size() >= 16) { // 假設 L1 Cache 大小為 16 行
      l1CacheLines.erase(l1CacheLines.begin()); // FIFO 替換策略
    }
    l1CacheLines.insert(address);

