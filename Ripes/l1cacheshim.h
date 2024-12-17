#pragma once

#include <QObject>
#include <memory> // 引入 shared_ptr

#include "cachesim.h"
#include "l2cachesim.h" // 新增 L2 Cache 頭文件

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

  /**
   * @brief m_memory
   * The cache simulator may be attached to either a ROM or a Read/Write memory
   * element. Accessing the underlying VSRTL component signals are dependent on
   * the given type of the memory.
   */
  CacheType m_type;

  // 新增 L2 Cache 成員
  std::shared_ptr<L2CacheSim> m_l2Cache;
};

} // namespace Ripes
