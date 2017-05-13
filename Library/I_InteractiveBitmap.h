#pragma once

#include "allegro5\allegro.h"

#include "I_AllegroEventAdapter.h"
#include "I_ConstantObservable.h"

namespace it
{
  class I_InteractiveBitmap : public I_ConstantObservable
  {
  public:
    virtual ~I_InteractiveBitmap() {};
    virtual void reset() = 0;
    virtual void processEvent (I_AllegroEventAdapter const &) = 0;
    virtual bool const & isLastFetchedBitmapUpToDate () const = 0; // TODO: to refactor (what if the same bitmap view is used by different controllers simultaneously?)
    virtual ALLEGRO_BITMAP * fetchBitmap() = 0;
  };
}