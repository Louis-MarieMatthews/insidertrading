#pragma once

#include "I_AllegroEventAdapter.h"
#include "I_LocatedBitmap.h"
#include "I_ConstantObservable.h"

namespace it
{
  class I_EventSensitiveLocatedBitmap : public I_LocatedBitmap, public I_ConstantObservable
  {
  public:
    virtual ~I_EventSensitiveLocatedBitmap() {};
    virtual void processEvent (const I_AllegroEventAdapter*) = 0;
  };
}