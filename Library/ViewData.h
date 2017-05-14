#pragma once

#include <memory>

#include "I_BitmapView.h"
#include "GameData.h"

namespace it
{
  class ViewData
  {
    I_BitmapView *                      exit_;
    GameData &                          gameData_;
    I_BitmapView *                      gameMenu_;
    I_BitmapView *                      mainMenu_;
    std::map<Company *, I_BitmapView *> companyMenus_;
    PlanarDimensions                    dimensions_;

  public:
    ViewData (GameData &, PlanarDimensions const &);
    ~ViewData();

    GameData & getGameData();
    I_BitmapView * & getGameView(); // TODO: const!
    I_BitmapView * & getMainMenu();
    I_BitmapView * & getExit();
    I_BitmapView * getCompanyMenu (Company &);
  };
}