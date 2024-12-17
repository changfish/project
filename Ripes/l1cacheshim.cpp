#include "l1cacheshim.h"
#include "processorhandler.h"

namespace Ripes {

L1CacheShim::L1CacheShim(CacheType type, QObject *parent)
    : CacheInterface(parent), m_type(type) {
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReset, this,
          &L1CacheShim::processorReset);

  connect(ProcessorHandler::get(), &ProcessorHandler::processorClocked, this,
          &L1CacheShim::processorWasClocked, Qt::DirectConnection);
  connect(ProcessorHandler::get(), &ProcessorHandler::processorReversed, this,
          &L1CacheShim::processorReversed);

  processorReset();
}

void L1CacheShim::access(AInt, MemoryAccess::Type) {
  Q_ASSERT(false);
}

void L1CacheShim::processorReset() {
  CacheInterface::reset();
}

void L1CacheShim::processorReversed() {
  CacheInterface::reverse();
}

void L1CacheShim::processorWasClocked() {
  if (m_type == CacheType::DataCache) {
    const auto dataAccess = ProcessorHandler::getProcessor()->dataMemAccess();

    switch (dataAccess.type) {
    case MemoryAccess::Write:
      handleL1Access(dataAccess.address, MemoryAccess::Write);
      break;
    case MemoryAccess::Read:
      handleL1Access(dataAccess.address, MemoryAccess::Read);
      break;
    default:
      break;
    }
  } else {
    const auto instrAccess = ProcessorHandler::getProcessor()->instrMemAccess();
    if (instrAccess.type == MemoryAccess::Read) {
      handleL1Access(instrAccess.address, MemoryAccess::Read);
    }
  }
}

void L1CacheShim::handleL1Access(AInt address, MemoryAccess::Type type) {
    if (m_l2Cache) {
        m_l2Cache->access(address, type);
    }
}

} // namespace Ripes
