#include "l2cacheshim.h"

namespace Ripes {

void L2CacheShim::access(AInt address, MemoryAccess::Type type) {
  CacheSim::access(address, type);
}

} // namespace Ripes
