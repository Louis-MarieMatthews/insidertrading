#include "ViewData.h"

#include "CompanyView.h"
#include "GameMenu.h"
#include "MainMenu.h"
#include "NoticeView.h"

namespace it
{
  ViewData::ViewData (I_GameData & gameData, PlanarDimensions const & dimensions) :
    dimensions_ (dimensions),
    exit_ (nullptr),
    gameData_ (gameData),
    gameMenu_ (new GameMenu (*this, dimensions)),
    mainMenu_ (new MainMenu (*this, dimensions))
  {


      std::vector<std::string> lines (3);
      lines[0] = "A game made by Louis-Marie Matthews. The font used in the game";
      lines[1] = "is named Good Times RG and it is used and licensed by Ray Larabie.";
      lines[2] = "2D graphics are powered by the C++ Allegro library. JSON for Modern C++ by Niels Lohmann.";
      creditsNoticeView_ = new NoticeView (mainMenu_, dimensions_, lines, *this);
  }



  ViewData::~ViewData()
  {
    for (auto cm : companyMenus_) {
      delete cm.second;
    }
    delete gameMenu_;
    delete mainMenu_;

    if (viewOfLegalNotice_ != nullptr) {
      delete viewOfLegalNotice_;
    }
    if (creditsNoticeView_ != nullptr) {
      delete creditsNoticeView_;
    }
  }



  I_GameData & ViewData::getGameData()
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



  I_BitmapView * ViewData::getInsiderTradingLegalNoticeView()
  {
    if (viewOfLegalNotice_ == nullptr) {
      std::vector<std::string> lines (1);
      lines[0] = "Insider trading is illegal and is severely punished in most countries.";
      viewOfLegalNotice_ = new NoticeView (creditsNoticeView_, dimensions_, lines, *this);
    }
    return viewOfLegalNotice_;
  }



  I_BitmapView * ViewData::getCreditsNoticeView()
  {
    return creditsNoticeView_;
  }
}