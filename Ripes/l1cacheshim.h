#pragma once

#include <QObject>
#include <memory> // 使用 shared_ptr 需要這個標頭檔案

#include "cachesim.h"
#include "l2cachesim.h" // 引入 L2 Cache 頭檔案

#include "VSRTL/core/vsrtl_memory.h"
#include "isa/isa_types.h"

namespace Ripes {

/**
 * @brief The CacheShim class
 * Provides a wrapper around the current processor models' data- and instruction
 * memories, to be used in the cache simulator interface.
 */
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

  CacheType m_type;

  // 新增 L2 Cache 成員
  std::shared_ptr<L2CacheSim> m_l2Cache;
};

} // namespace Ripes
