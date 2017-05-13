#pragma once

#include "I_AllegroEventAdapter.h"

namespace it
{
  class I_BitmapView
  {
  public:
    virtual ~I_BitmapView() {};
    virtual I_BitmapView * getNext() = 0;
    virtual void reset() = 0;
    virtual void processEvent (I_AllegroEventAdapter const &) = 0;
    virtual bool const & isLastFetchedBitmapUpToDate () const = 0; // TODO: to refactor (what if the same bitmap view is used by different controllers simultaneously?)
    virtual ALLEGRO_BITMAP * fetchBitmap() = 0;
  };
}