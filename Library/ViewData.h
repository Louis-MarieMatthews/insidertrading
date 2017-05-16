#pragma once

#include <memory>

#include "I_BitmapView.h"
#include "I_GameData.h"

namespace it
{
  class ViewData
  {
    I_BitmapView *                      exit_;
    ObservablePointer<I_GameData>       gameData_;
    ObservablePointer<I_BitmapView>     gameMenu_;
    I_BitmapView *                      mainMenu_;
    std::map<Company *, I_BitmapView *> companyMenus_;
    PlanarDimensions                    dimensions_;
    I_BitmapView *                      viewOfLegalNotice_;
    I_BitmapView *                      creditsNoticeView_;
    Duration const &                    time_;

  public:
    ViewData (Duration const &, PlanarDimensions const &);
    ~ViewData();

    ObservablePointer<I_GameData> &  getGameData();
    I_BitmapView * getGameView(); // TODO: const!
    ObservablePointer<I_BitmapView> & getObservableGameView();
    I_BitmapView * & getMainMenu();
    I_BitmapView * & getExit();
    I_BitmapView * getCompanyMenu (Company &);
    I_BitmapView * getInsiderTradingLegalNoticeView();
    I_BitmapView * getCreditsNoticeView();
    void createNewGame();
  };
}