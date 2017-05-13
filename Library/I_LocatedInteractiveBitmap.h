#pragma once

#include "I_InteractiveBitmap.h"
#include "I_LocatedRectangle.h"

namespace it
{
  class I_LocatedInteractiveBitmap : public I_InteractiveBitmap, public I_LocatedRectangle
  {
  public:
    virtual ~I_LocatedInteractiveBitmap() {};
    virtual PlanarPosition const & getPosition() const = 0;
  };
}