#include "l2cacheshim.h"

namespace Ripes {

void L2CacheShim::access(AInt address, MemoryAccess::Type type) {
  CacheSim::access(address, type); // 使用已有的 CacheSim 逻辑处理 L2 缓存访问
}

} // namespace Ripes
