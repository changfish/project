#include "cacheinterface.h"

namespace Ripes {

class L2CacheSim : public CacheSim {
  Q_OBJECT
public:
  explicit L2CacheSim(QObject *parent = nullptr);
  void access(AInt address, MemoryAccess::Type type) override;
  void reset() override;
  void reverse() override;

  void setPreset(const CachePreset &preset) override;

private:
  void analyzeCacheAccess(CacheTransaction &transaction) const override;
};

} // namespace Ripes
