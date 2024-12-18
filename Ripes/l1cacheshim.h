#pragma once

#include <QObject>

#include "cachesim.h"
#include "l2cacheshim.h"
#include "processorhandler.h"
#include "VSRTL/core/vsrtl_memory.h"
#include "isa/isa_types.h"
#include "isa/isa_types.h" // 包含 MemoryAccess 定义

namespace Ripes {

class L1CacheShim : public CacheInterface {
  Q_OBJECT
public:
  enum class CacheType { DataCache, InstrCache };
  L1CacheShim(CacheType type, QObject *parent);
  void access(AInt address, MemoryAccess::Type type) override;

  void setType(CacheType type);
  void setL2Cache(const std::shared_ptr<L2CacheShim>& cache) {
    m_l2Cache = cache;
  }

private:
  void processorReset();
  void processorWasClocked();
  void processorReversed();

  CacheType m_type;
  std::shared_ptr<L2CacheShim> m_l2Cache;
};

} // namespace Ripes
