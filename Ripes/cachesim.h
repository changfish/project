#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include <QObject>

#include "VSRTL/core/vsrtl_register.h"
#include "processors/interface/ripesprocessor.h"
#include "isa/isa_types.h"

namespace Ripes {

class CacheSim;

class CacheInterface : public QObject {
  Q_OBJECT
public:
  CacheInterface(QObject *parent = nullptr) : QObject(parent) {}
  virtual ~CacheInterface() {}

  virtual void access(AInt address, MemoryAccess::Type type) = 0;
  void setNextLevelCache(const std::shared_ptr<CacheSim> &cache) {
    m_nextLevelCache = cache;
  }

  virtual void reset();
  virtual void reverse();

protected:
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
    bool isWriteback = false;
    MemoryAccess::Type type = MemoryAccess::None;
    bool transToValid = false;
    bool tagChanged = false;
  };

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
  unsigned getWritebacks() const;
  CacheSize getCacheSize() const;

  AInt buildAddress(unsigned tag, unsigned lineIdx, unsigned blockIdx) const;

  int getBlockBits() const { return m_blocks; }
  int getWaysBits() const { return m_ways; }
  int getLineBits() const { return m_lines; }
  int getTagBits() const {
    return 32 - 2 - getBlockBits() - getLineBits();
  }

  int getBlocks() const { return static_cast<int>(std::pow(2, m_blocks)); }
  int getWays() const { return static_cast<int>(std::pow(2, m_ways)); }
  int getLines() const { return static_cast<int>(std::pow(2, m_lines)); }
  unsigned getBlockMask() const { return m_blockMask; }
  unsigned getTagMask() const { return m_tagMask; }
  unsigned getLineMask() const { return m_lineMask; }

  unsigned getLineIdx(const AInt address) const;
  unsigned getBlockIdx(const AInt address) const;
  unsigned getTag(const AInt address) const;

  const std::map<unsigned, CacheWay> *getLine(unsigned idx) const;

public slots:
  void setBlocks(unsigned blocks);
  void setLines(unsigned lines);
  void setWays(unsigned ways);

  void reverse() override;

signals:
  void configurationChanged();
  void dataChanged(CacheSim::CacheTransaction transaction);
  void hitrateChanged();

  void statsUpdated(unsigned hits, unsigned misses, unsigned writebacks);
  void resetRequested();
  void undoRequested();

protected:
  virtual void analyzeCacheAccess(CacheTransaction &transaction) = 0;
  virtual void cacheAccess(CacheTransaction &transaction) = 0;

  void sendTransactionStats(CacheTransaction &transaction);

  int m_blocks;
  int m_lines;
  int m_ways;

  unsigned m_blockMask;
  unsigned m_lineMask;
  unsigned m_tagMask;

  CacheSize m_size;

  unsigned m_hits;
  unsigned m_misses;
  unsigned m_writebacks;

  std::map<unsigned, CacheAccessTrace> m_accessTrace;

  WriteAllocPolicy m_wrAllocPolicy;
  ReplPolicy m_replPolicy;
  WritePolicy m_wrPolicy;
};
