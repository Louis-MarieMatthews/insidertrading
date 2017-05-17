#include "ViewData.h"

#include "CompanyView.h"
#include "DefaultGameData.h"
#include "GameMenu.h"
#include "MainMenu.h"
#include "NoticeView.h"

namespace it
{
  void ViewData::destroyGameView()
  {
    if (viewOfGame_.getPointer() != nullptr) {
      delete viewOfGame_.getPointer();
    }
    for (auto pair : companyMenus_) {
      delete pair.second;
    }
  }



  ViewData::ViewData (ObservablePointer<I_GameData> & gameData, Duration const & time, PlanarDimensions const & dimensions) :
    dimensions_ (dimensions),
    exit_ (nullptr),
    gameData_ (gameData),
    mainMenu_ (new MainMenu (gameData, *this, dimensions)),
    programTime_ (time)
  {


      std::vector<std::string> lines (3);
      lines[0] = "A game made by Louis-Marie Matthews. Good Times RG by Ray Larabie.";
      lines[1] = "Images from Wikimedia and pixabay.com.";
      lines[2] = "2D graphics powered by the C++ Allegro library. JSON for Modern C++ by Niels Lohmann.";
      viewOfCredits_ = new NoticeView (mainMenu_, dimensions_, lines, *this);
  }



  ViewData::~ViewData()
  {
    for (auto cm : companyMenus_) {
      delete cm.second;
    }
    if (viewOfGame_.getPointer() != nullptr) {
      delete viewOfGame_.getPointer();
    }
    delete mainMenu_;

    if (gameData_.getPointer() != nullptr) {
      delete gameData_.getPointer();
      gameData_.setPointer (nullptr);
    }

    if (viewOfLegalNotice_ != nullptr) {
      delete viewOfLegalNotice_;
    }
    if (viewOfCredits_ != nullptr) {
      delete viewOfCredits_;
    }
  }



  ObservablePointer<I_GameData> & ViewData::getGameData()
  {
    return gameData_;
  }



  I_BitmapView * ViewData::getGameView()
  {
    return viewOfGame_.getPointer();
  }



  ObservablePointer<I_BitmapView> const & ViewData::getObservableGameView()
  {
    return viewOfGame_;
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
      viewOfLegalNotice_ = new NoticeView (viewOfCredits_, dimensions_, lines, *this);
    }
    return viewOfLegalNotice_;
  }



  I_BitmapView * ViewData::getCreditsNoticeView()
  {
    return viewOfCredits_;
  }



  void ViewData::createNewGame (std::string const & filename)
  {
    destroyGameView();
    if (gameData_.getPointer() != nullptr) {
      delete gameData_.getPointer();
    }
    gameData_.setPointer (new DefaultGameData (programTime_, filename));
    viewOfGame_.setPointer (new GameMenu (*this, dimensions_));
  }
}