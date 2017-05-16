#include "PlayerBalance.h"

#include "ObserverListSingleton.h"

namespace it
{
  PlayerBalance::PlayerBalance() :
    money_ (100)
  {
  }



  PlayerBalance::~PlayerBalance()
  {
    ObserverListSingleton::getInstance().removeObservable (observableId_);
  }



  unsigned long long const & PlayerBalance::getMoney() const
  {
    return money_;
  }



  std::string PlayerBalance::getString() const
  {
    return "$" + std::to_string (money_);
  }



  void PlayerBalance::operator-= (unsigned long long const & sum)
  {
    money_ -= sum;
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  void PlayerBalance::operator+= (unsigned long long const & sum)
  {
    money_ += sum;
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  I_ObservableId const & PlayerBalance::getObservableId() const
  {
    return observableId_;
  }



  bool operator>= (PlayerBalance const & balance, unsigned long long const & sum)
  {
    return balance.getMoney() >= sum;
  }



  bool operator< (PlayerBalance const & balance, unsigned long long const & sum)
  {
    return balance.getMoney() < sum;
  }
}