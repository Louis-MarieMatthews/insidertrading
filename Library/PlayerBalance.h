#pragma once

#include <string>

#include "I_ConstantObservable.h"
#include "DefaultObservableId.h"

namespace it
{
  class PlayerBalance : public I_ConstantObservable
  {
    DefaultObservableId observableId_;
    unsigned long long  money_;

  public:
    PlayerBalance();
    ~PlayerBalance();

    unsigned long long const & getMoney() const;
    std::string getString() const;
    void operator-= (unsigned long long const &);
    void operator+= (unsigned long long const &);

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };

  bool operator>= (PlayerBalance const &, unsigned long long const &);
  bool operator< (PlayerBalance const &, unsigned long long const &);
}