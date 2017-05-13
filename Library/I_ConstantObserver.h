#pragma once

#include "I_ObservableId.h"

namespace it
{
  class I_ConstantObserver
  {
  public:
    virtual ~I_ConstantObserver() {};
    virtual void notifyObserver (I_ObservableId const &) = 0;
  };
}