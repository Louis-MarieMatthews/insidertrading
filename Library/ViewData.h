#pragma once

#include <memory>

#include "I_BitmapView.h"
#include "I_GameData.h"

namespace it
{
  class ViewData
  {
    std::map<Company *, I_BitmapView *> companyMenus_; // TODO: should be moved in viewOfGame_ (would prevent any ordering problem when destroying viewOfGame_ and companyMenus_'s views
    PlanarDimensions                    dimensions_;
    I_BitmapView *                      exit_;
    ObservablePointer<I_GameData> &     gameData_;
    I_BitmapView *                      mainMenu_;
    Duration const &                    programTime_;
    I_BitmapView *                      viewOfCredits_;
    ObservablePointer<I_BitmapView>     viewOfGame_;
    I_BitmapView *                      viewOfLegalNotice_;

    void destroyGameView();

  public:
    ViewData (ObservablePointer<I_GameData> &, Duration const &, PlanarDimensions const &);
    ~ViewData();

    ObservablePointer<I_GameData> &  getGameData();
    I_BitmapView * getGameView();
    ObservablePointer<I_BitmapView> const & getObservableGameView();
    I_BitmapView * & getMainMenu();
    I_BitmapView * & getExit();
    I_BitmapView * getCompanyMenu (Company &);
    I_BitmapView * getInsiderTradingLegalNoticeView();
    I_BitmapView * getCreditsNoticeView();
    void createNewGame (std::string const &);
  };
}