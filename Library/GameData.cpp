#include "GameData.h"

namespace it
{
  GameData::GameData()
  {
  }



  Time & GameData::getTime()
  {
    return time_;
  }



  PlayersMoney & GameData::getPlayersMoney()
  {
    return playersMoney_;
  }
}