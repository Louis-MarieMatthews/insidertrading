#include "ViewData.h"

#include "CompanyView.h"
#include "GameMenu.h"
#include "MainMenu.h"

namespace it
{
  ViewData::ViewData (GameData & gameData, PlanarDimensions const & dimensions) :
    dimensions_ (dimensions),
    exit_ (nullptr),
    gameData_ (gameData),
    gameMenu_ (new GameMenu (*this, dimensions)),
    mainMenu_ (new MainMenu (*this, dimensions))
  {
  }



  ViewData::~ViewData()
  {
    for (auto cm : companyMenus_) {
      delete cm.second;
    }
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



  I_BitmapView * ViewData::getCompanyMenu (Company & company)
  {
    if (companyMenus_.find (&company) == companyMenus_.end()) {
      companyMenus_[&company] = new CompanyView (company, *this, dimensions_);
    }
    return companyMenus_.at (&company);
  }
}