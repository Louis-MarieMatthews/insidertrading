#pragma once

#include "Time.h"

namespace it
{
  class GameData
  {
    Time time_;

  public:
    GameData();
    Time & getTime();
  };
}