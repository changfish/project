#pragma once

#include <map>
#include <math.h>
#include <vector>

#include <QDataStream>
#include <QObject>

#include "../external/VSRTL/core/vsrtl_register.h"
#include "processors/RISC-V/rv_memory.h"
#include "processors/interface/ripesprocessor.h"

namespace Ripes {
class CacheSim;

enum WriteAllocPolicy { WriteAllocate, NoWriteAllocate };
enum WritePolicy { WriteThrough, WriteBack };
enum ReplPolicy { Random, LRU };

struct CachePreset {
  QString name;
  int blocks;
  int lines;
  int ways;

  WritePolicy wrPolicy;
  WriteAllocPolicy wrAllocPolicy;
  ReplPolicy replPolicy;

  friend QDataStream &operator<<(QDataStream &arch, const CachePreset &object) {
    arch << object.name;
    arch << object.blocks;
    arch << object.lines;
    arch << object.ways;
    arch << object.wrPolicy;
    arch << object.wrAllocPolicy;
    arch << object.replPolicy;
    return arch;
  }

  friend QDataStream &operator>>(QDataStream &arch, CachePreset &object) {
    arch >> object.name;
    arch >> object.blocks;
    arch >> object.lines;
    arch >> object.ways;
    arch >> object.wrPolicy;
    arch >> object.wrAllocPolicy;
    arch >> object.replPolicy;
    return arch;
  }

  bool operator==(const CachePreset &other) const {
    return this->name == other.name;
  }
};

class CacheInterface : public QObject {
  Q_OBJECT
public:
  CacheInterface(QObject *parent) : QObject(parent) {}
  virtual ~CacheInterface() {}

  /**
   * @brief access
   * A function called by the logical "child" of this cache, indicating that it
   * desires to access this cache
   */
  virtual void access(AInt address, MemoryAccess::Type type) = 0;
  void setNextLevelCache(const std::shared_ptr<CacheSim> &cache) {
    m_nextLevelCache = cache;
  }

  /**
   * @brief reset
   * Called by the logical child of this cache to  propagating cache resetting
   * or reversing up the cache hierarchy.
   */
  virtual void reset();
  virtual void reverse();

protected:
  /**
   * @brief m_nextLevelCache
   * Pointer to the next level (logical parent) cache.
   */
  std::shared_ptr<CacheSim> m_nextLevelCache;
};

class CacheSim : public CacheInterface {
  Q_OBJECT
public:
  static constexpr unsigned s_invalidIndex = static_cast<unsigned>(-1);

  struct CacheSize {
    unsigned bits = 0;
    std::vector<QString> components;
  };

  struct CacheWay {
    VInt tag = -1;
    std::set<unsigned> dirtyBlocks;
    bool dirty = false;
    bool valid = false;

    // LRU algorithm relies on invalid cache ways to have an initial high value.
    // -1 ensures maximum value for all way sizes.
    unsigned lru = -1;
  };

  struct CacheIndex {
    unsigned line = s_invalidIndex;
    unsigned way = s_invalidIndex;
    unsigned block = s_invalidIndex;
    void assertValid() const {
      Q_ASSERT(line != s_invalidIndex && "Cache line index is invalid");
      Q_ASSERT(way != s_invalidIndex && "Cache way index is invalid");
      Q_ASSERT(block != s_invalidIndex && "Cache word index is invalid");
    }

    bool operator==(const CacheIndex &other) const {
      return this->line == other.line && this->way == other.way &&
             this->block == other.block;
    }
  };

  struct CacheTransaction {
    AInt address;
    CacheIndex index;

    bool isHit = false;
    bool isWriteback = false; // True if the transaction resulted in an eviction
                              // of a dirty cacheline
    MemoryAccess::Type type = MemoryAccess::None;
    bool transToValid =
        false; // True if the cacheline just transitioned from invalid to valid
    bool tagChanged =
        false; // True if transToValid or the previous entry was evicted
  };

  struct CacheAccessTrace {
    int hits = 0;
    int misses = 0;
    int reads = 0;
    int writes = 0;
    int writebacks = 0;
    CacheTransaction lastTransaction;
    CacheAccessTrace() {}
    CacheAccessTrace(const CacheTransaction &transaction)
        : CacheAccessTrace(CacheAccessTrace(), transaction) {}
    CacheAccessTrace(const CacheAccessTrace &pre,
                     const CacheTransaction &transaction) {
      lastTransaction = transaction;
      reads = pre.reads + (transaction.type == MemoryAccess::Read ? 1 : 0);
      writes = pre.writes + (transaction.type == MemoryAccess::Write ? 1 : 0);
      writebacks = pre.writebacks + (transaction.isWriteback ? 1 : 0);
      hits = pre.hits + (transaction.isHit ? 1 : 0);
      misses = pre.misses + (transaction.isHit ? 0 : 1);
    }
  };

  using CacheLine = std::map<unsigned, CacheWay>;

  CacheSim(QObject *parent);
  void setWritePolicy(WritePolicy policy);
  void setWriteAllocatePolicy(WriteAllocPolicy policy);
  void setReplacementPolicy(ReplPolicy policy);

  void access(AInt address, MemoryAccess::Type type) override;
  void undo();
  void reset() override;

  WriteAllocPolicy getWriteAllocPolicy() const { return m_wrAllocPolicy; }
  ReplPolicy getReplacementPolicy() const { return m_replPolicy; }
  WritePolicy getWritePolicy() const { return m_wrPolicy; }

  const std::map<unsigned, CacheAccessTrace> &getAccessTrace() const {
    return m_accessTrace;
  }

  double getHitRate() const;
  unsigned getHits() const;
  unsigned getMisses() const;

  static double getCombinedHitRate(const CacheSim &l1, const CacheSim &l2);

private:
  std::map<unsigned, CacheAccessTrace> m_accessTrace;
};

} // namespace Ripes
