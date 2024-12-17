#pragma once

#include "cachesim.h"

namespace Ripes {

/**
 * @brief The L2CacheSim class
 * Represents a simple L2 cache simulator.
 */
class L2CacheSim : public CacheInterface {
  Q_OBJECT
public:
  L2CacheSim(QObject *parent = nullptr);

  // Overriding the access method to handle memory accesses
  void access(AInt address, MemoryAccess::Type type) override;

private:
  // A simple cache structure for demonstration
  std::unordered_set<AInt> m_cacheLines;
  static constexpr size_t L2_SIZE = 64; // Example cache size (in lines)

  bool isHit(AInt address);
  void insertAddress(AInt address);
};

} // namespace Ripes
