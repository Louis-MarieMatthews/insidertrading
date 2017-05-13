#pragma once

#include "Time.h"
#include "PlayersMoney.h"
#include "Company.h"

namespace it
{
  class GameData
  {
    Time              time_;
    PlayersMoney      playersMoney_;
    std::set<Company> companies_;

  public:
    GameData();
    Time & getTime();
    PlayersMoney & getPlayersMoney();
    std::set<Company> const & getCompanies();
  };
}