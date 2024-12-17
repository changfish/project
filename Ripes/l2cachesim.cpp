#include "l2cachesim.h"

namespace Ripes {

L2CacheSim::L2CacheSim(QObject *parent) : CacheInterface(parent) {}

void L2CacheSim::access(AInt address, MemoryAccess::Type type) {
  if (isHit(address)) {
    emit cacheEvent(CacheEvent::Hit, address);
  } else {
    emit cacheEvent(CacheEvent::Miss, address);
    insertAddress(address);
  }
}

bool L2CacheSim::isHit(AInt address) {
  return m_cacheLines.find(address) != m_cacheLines.end();
}

void L2CacheSim::insertAddress(AInt address) {
  if (m_cacheLines.size() >= L2_SIZE) {
    m_cacheLines.erase(m_cacheLines.begin()); // Simple eviction policy (FIFO)
  }
  m_cacheLines.insert(address);
}

} // namespace Ripes
