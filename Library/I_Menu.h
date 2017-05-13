#pragma once

#include "allegro5\allegro.h"

#include "I_AllegroEventAdapter.h"

namespace it
{
  class I_Menu // TODO: should the backbuffer be set in each I_Menu constructor?
  {
  public :
    virtual ~I_Menu() {}; // TODO: why defining destructor?
    virtual I_Menu* const getNext() const = 0; // TODO: why = 0? // TODO: why not a reference instead?
    virtual void setNext (I_Menu*) = 0;
    virtual void processFrame (const I_AllegroEventAdapter*) = 0; // TODO: void const??? TODO: IMP: prevent same mouse click from being processed by two successive menus
    virtual void resetNext() = 0;
    virtual void draw() = 0;
  };
}