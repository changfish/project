#pragma once

#include "cachesim.h"

namespace Ripes {

class L2CacheShim : public CacheSim {
  Q_OBJECT
public:
  L2CacheShim(QObject *parent = nullptr) : CacheSim(parent) {}

  void access(AInt address, MemoryAccess::Type type) override {
    CacheSim::access(address, type);
  }
};

} // namespace Ripes
