#pragma once

#include <unordered_map>
#include <memory>
#include "VSRTL/core/vsrtl_memory.h"
#include "isa/isa_types.h"

namespace Ripes {

/**
 * @brief The L2Cache class
 * Represents the L2 cache in the cache hierarchy.
 */
class L2Cache {
public:
  L2Cache();
  ~L2Cache();

  bool isHit(AInt address);
  void access(AInt address, MemoryAccess::Type type);
  void reset();
  void reverse();

private:
  // Cache structure and management details
  std::unordered_map<AInt, MemoryAccess::Type> cacheEntries;
};

} // namespace Ripes 
