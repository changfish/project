#include "l2cache.h"

namespace Ripes {

L2Cache::L2Cache(QObject *parent) : CacheInterface(parent) {}

void L2Cache::access(AInt address, MemoryAccess::Type type) {
  if (isHit(address)) {
    updateStats(true); // Update L2 hit statistics
  } else {
    updateStats(false); // Update L2 miss statistics
    // No further level of cache; treat as memory access.
  }
}

bool L2Cache::isHit(AInt address) {
  // Simulate a hit/miss decision (replace with actual logic)
  return false; // TODO: Implement L2 cache hit logic
}

} // namespace Ripes
