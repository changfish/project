#pragma once

#include <QObject>
#include "cachesim.h"
#include "l2cachesim.h"
#include "l3cachesim.h"

namespace Ripes {

class L1CacheShim : public CacheInterface {
  Q_OBJECT
public:
  enum class CacheType { DataCache, InstrCache, L2Cache, L3Cache };
  
  L1CacheShim(CacheType type, QObject *parent = nullptr);
  void access(AInt address, MemoryAccess::Type type) override;

  void setType(CacheType type);

private:
  void processorReset();
  void processorWasClocked();
  void processorReversed();

  CacheType m_type;

  std::shared_ptr<L2CacheSim> m_l2Cache;
  std::shared_ptr<L3CacheSim> m_l3Cache;
};

} // namespace Ripes
