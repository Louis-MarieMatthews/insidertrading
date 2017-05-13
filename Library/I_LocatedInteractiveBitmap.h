#pragma once

#include "I_InteractiveBitmap.h"

namespace it
{
  class I_LocatedInteractiveBitmap : public I_InteractiveBitmap
  {
  public:
    virtual ~I_LocatedInteractiveBitmap() {};
    virtual PlanarPosition const & getPosition() const = 0;
  };
}