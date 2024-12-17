#include "l3cachesim.h"

namespace Ripes {

L3CacheSim::L3CacheSim(QObject *parent)
    : CacheSim(parent) {}

void L3CacheSim::access(AInt address, MemoryAccess::Type type) {
  CacheTransaction transaction{address, getCacheIndex(address), false, false, type, false, false};
  analyzeCacheAccess(transaction);
}

} // namespace Ripes
