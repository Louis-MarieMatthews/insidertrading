#pragma once

#include "I_InteractiveBitmap.h"
#include "I_AllegroEventAdapter.h"

namespace it
{
  class I_BitmapView : public I_InteractiveBitmap
  {
  public:
    virtual ~I_BitmapView() {};
    virtual I_BitmapView * getNext() = 0;
  };
}