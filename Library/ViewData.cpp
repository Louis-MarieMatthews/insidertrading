#include "ViewData.h"

#include "GameMenu.h"
#include "MainMenu.h"

namespace it
{
  ViewData::ViewData (GameData & gameData, PlanarDimensions const & dimensions) :
    exit_ (nullptr),
    gameData_ (gameData),
    gameMenu_ (new GameMenu (*this, dimensions)),
    mainMenu_ (new MainMenu (*this, dimensions))
  {
  }



  ViewData::~ViewData()
  {
    delete gameMenu_;
    delete mainMenu_;
  }



  GameData & ViewData::getGameData()
  {
    return gameData_;
  }



  I_BitmapView * & ViewData::getGameView()
  {
    return gameMenu_;
  }



  I_BitmapView * & ViewData::getMainMenu()
  {
    return mainMenu_;
  }



  I_BitmapView *& ViewData::getExit()
  {
    return exit_;
  }
}