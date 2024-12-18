#pragma once

#include "cachesim.h"

namespace Ripes {

/**
 * @brief The L2Cache class
 * Implements a simple L2 cache which acts as the next level cache in the hierarchy.
 */
class L2Cache : public CacheInterface {
  Q_OBJECT
public:
  L2Cache(QObject *parent = nullptr);
  void access(AInt address, MemoryAccess::Type type) override;

private:
  bool isHit(AInt address);
};

} // namespace Ripes
 
