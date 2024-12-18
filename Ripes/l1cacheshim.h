#pragma once

#include <QObject>
#include "cachesim.h"
#include "l2cache.h" // import L2Cache

#include "VSRTL/core/vsrtl_memory.h"
#include "isa/isa_types.h"

namespace Ripes {

/**
 * @brief The L1CacheShim class
 * Provides a wrapper around the current processor models' data- and instruction
 * memories, to be used in the cache simulator interface.
 */
class L1CacheShim : public CacheInterface {
  Q_OBJECT
public:
  enum class CacheType { DataCache, InstrCache };
  L1CacheShim(CacheType type, QObject *parent);
  void access(AInt address, MemoryAccess::Type type) override;

private:
  void processorReset();
  void processorWasClocked();
  void processorReversed();

  CacheType m_type;

  // Internal L2Cache instance
  std::unique_ptr<L2Cache> m_l2Cache;
};

} // namespace Ripes
