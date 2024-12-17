#pragma once

#include <QObject>
#include <memory> // 使用 shared_ptr 需要這個標頭檔案

#include "cachesim.h"
#include "l2cachesim.h"

#include "VSRTL/core/vsrtl_memory.h"
#include "isa/isa_types.h"

namespace Ripes {

class L1CacheShim : public CacheInterface {
  Q_OBJECT
public:
  enum class CacheType { DataCache, InstrCache };
  L1CacheShim(CacheType type, QObject *parent);
  void access(AInt address, MemoryAccess::Type type) override;

  void setType(CacheType type);

private:
  void processorReset();
  void processorWasClocked();
  void processorReversed();

  void handleL1Access(AInt address, MemoryAccess::Type type); // 新增函數宣告

  CacheType m_type;

  std::shared_ptr<L2CacheSim> m_l2Cache; // 新增 L2 Cache 成員
};

} // namespace Ripes
