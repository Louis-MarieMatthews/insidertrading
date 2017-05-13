#pragma once

#include "Company.h"
#include "PlayersMoney.h"
#include "Sec.h"
#include "Duration.h"

namespace it
{
  class GameData
  {
    std::set<Company> companies_;
    PlayersMoney      playersMoney_;
    Duration              time_;
    Sec               sec_;

  public:
    GameData();
    Duration & getTime();
    PlayersMoney & getPlayersMoney();
    std::set<Company> const & getCompanies();
    Sec & getSec();
  };
}