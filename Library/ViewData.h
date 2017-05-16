#pragma once

#include <memory>

#include "I_BitmapView.h"
#include "I_GameData.h"

namespace it
{
  class ViewData
  {
    I_BitmapView *                      exit_;
    I_GameData &                        gameData_;
    I_BitmapView *                      gameMenu_;
    I_BitmapView *                      mainMenu_;
    std::map<Company *, I_BitmapView *> companyMenus_;
    PlanarDimensions                    dimensions_;
    I_BitmapView *                      viewOfLegalNotice_;
    I_BitmapView *                      creditsNoticeView_;

  public:
    ViewData (I_GameData &, PlanarDimensions const &);
    ~ViewData();

    I_GameData & getGameData();
    I_BitmapView * & getGameView(); // TODO: const!
    I_BitmapView * & getMainMenu();
    I_BitmapView * & getExit();
    I_BitmapView * getCompanyMenu (Company &);
    I_BitmapView * getInsiderTradingLegalNoticeView();
    I_BitmapView * getCreditsNoticeView();
  };
}