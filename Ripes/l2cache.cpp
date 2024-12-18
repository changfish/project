#include "l2cache.h"

namespace Ripes {

L2Cache::L2Cache() {}

L2Cache::~L2Cache() {}

bool L2Cache::isHit(AInt address) {
  return cacheEntries.find(address) != cacheEntries.end();
}

void L2Cache::access(AInt address, MemoryAccess::Type type) {
  cacheEntries[address] = type;
}

void L2Cache::reset() {
  cacheEntries.clear();
}

void L2Cache::reverse() {
  // Reverse operation for L2 cache if needed.
}

} // namespace Ripes
