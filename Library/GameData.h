#pragma once

#include "Company.h"
#include "PlayerBalance.h"
#include "Sec.h"
#include "Duration.h"

namespace it
{
  class GameData
  {
    std::set<Company *> companies_;
    PlayerBalance        playersMoney_;
    Duration            time_;
    Sec                 sec_;

  public:
    GameData();
    ~GameData();
    Duration & getTime();
    PlayerBalance & getPlayersMoney();
    std::set<Company *> const & getCompanies();
    Sec & getSec();
  };
}