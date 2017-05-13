#pragma once

#include "I_BitmapView.h"

namespace it
{
  class ViewData
  {
    I_BitmapView * exit_;
    I_BitmapView * gameMenu_;
    I_BitmapView * mainMenu_;

  public:
    ViewData (PlanarDimensions const &);
    ~ViewData();

    I_BitmapView * & getGameView(); // TODO: const!
    I_BitmapView * & getMainMenu();
    I_BitmapView * & getExit();
  };
}