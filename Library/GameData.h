#pragma once

#include "Company.h"
#include "PlayersMoney.h"
#include "Sec.h"
#include "Time.h"

namespace it
{
  class GameData
  {
    std::set<Company> companies_;
    PlayersMoney      playersMoney_;
    Time              time_;
    Sec               sec_;

  public:
    GameData();
    Time & getTime();
    PlayersMoney & getPlayersMoney();
    std::set<Company> const & getCompanies();
    Sec & getSec();
  };
}