#pragma once

#include "I_ObservableId.h"

namespace it
{
  class I_ConstantObservable
  {
  public:
    virtual ~I_ConstantObservable() {};
    virtual I_ObservableId const & getObservableId() const = 0;
  };
}