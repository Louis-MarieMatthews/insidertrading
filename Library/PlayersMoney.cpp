#include "PlayersMoney.h"

namespace it
{
  PlayersMoney::PlayersMoney() :
    money_ (0)
  {
  }



  unsigned long long const & PlayersMoney::getMoney() const
  {
    return money_;
  }



  std::string PlayersMoney::getString() const
  {
    return "$" + std::to_string (money_);
  }



  I_ObservableId const & PlayersMoney::getObservableId() const
  {
    return observableId_;
  }
}