#pragma once

#include <string>

#include "I_ConstantObservable.h"
#include "DefaultObservableId.h"

namespace it
{
  // TODO: rename to BankAccountBalance?
  class PlayersMoney : public I_ConstantObservable
  {
    DefaultObservableId observableId_;
    unsigned long long  money_;

  public:
    PlayersMoney();

    unsigned long long const & getMoney() const;
    std::string getString() const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };
}