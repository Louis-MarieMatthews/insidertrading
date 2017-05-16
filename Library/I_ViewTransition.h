#pragma once

#include "I_BitmapView.h"

namespace it
{
  class I_ViewTransition
  {
  public:
    virtual ~I_ViewTransition() {};
    virtual I_BitmapView * getTarget() = 0;
    virtual void prepare() = 0;
  };
}