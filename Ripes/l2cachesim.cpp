#include "l2cachesim.h"

namespace Ripes {

L2CacheSim::L2CacheSim(QObject *parent)
    : CacheSim(parent) {}

void L2CacheSim::access(AInt address, MemoryAccess::Type type) {
  CacheTransaction transaction{address, getCacheIndex(address), false, false, type, false, false};
  analyzeCacheAccess(transaction);
}

} // namespace Ripes
