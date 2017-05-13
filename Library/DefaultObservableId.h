#pragma once

#include "I_ObservableId.h"

namespace it
{
  class DefaultObservableId : public I_ObservableId
  {
  public:
    DefaultObservableId();
    // TODO: is it advised to always define a destructor, even if empty?
  };
}