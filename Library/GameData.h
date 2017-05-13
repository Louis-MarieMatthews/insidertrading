#pragma once

#include "Time.h"
#include "PlayersMoney.h"

namespace it
{
  class GameData
  {
    Time         time_;
    PlayersMoney playersMoney_;

  public:
    GameData();
    Time & getTime();
    PlayersMoney & getPlayersMoney();
  };
}