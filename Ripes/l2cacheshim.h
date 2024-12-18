#pragma once

#include "cachesim.h"

namespace Ripes {

class L2CacheShim : public CacheSim {
  Q_OBJECT
public:
  L2CacheShim(QObject *parent = nullptr) : CacheSim(parent) {}
};

} // namespace Ripes
