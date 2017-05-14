#include "PlayerBalance.h"

namespace it
{
  PlayerBalance::PlayerBalance() :
    money_ (0)
  {
  }



  unsigned long long const & PlayerBalance::getMoney() const
  {
    return money_;
  }



  std::string PlayerBalance::getString() const
  {
    return "$" + std::to_string (money_);
  }



  I_ObservableId const & PlayerBalance::getObservableId() const
  {
    return observableId_;
  }
}