#pragma once

#include <QObject>
#include "cachesim.h"

namespace Ripes {

class L3CacheSim : public CacheSim {
  Q_OBJECT
public:
  L3CacheSim(QObject *parent = nullptr);
  
  void access(AInt address, MemoryAccess::Type type) override;

signals:
  void configurationChanged();
};

} // namespace Ripes
