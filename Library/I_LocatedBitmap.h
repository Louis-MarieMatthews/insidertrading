#pragma once

#include "allegro5\allegro.h"
#include "I_LocatedRectangle.h"

namespace it
{
  class I_LocatedBitmap : public I_LocatedRectangle
  {
  public:
    virtual ~I_LocatedBitmap() {};
    virtual ALLEGRO_BITMAP* fetchBitmap() = 0;
  };
}