#pragma once

#include <set>

#include "Company.h"
#include "DefaultObservableId.h"
#include "I_ConstantObservable.h"
#include "I_ConstantObserver.h"
#include "PlanarPosition.h"
#include "Time.h"

namespace it
{
  class GameData;

  class Sec : public I_ConstantObservable, public I_ConstantObserver
  {
    PlanarPosition      position_;
    Time &              time_;
    DefaultObservableId observableId_;
    Company const *     currentTarget_;
    std::set<Company> const & companies_;
    static int const speed_{70};

    Company const & getRandomCompany();

  public:
    Sec (PlanarPosition const &, std::set<Company> const &, Time &);

    PlanarPosition const & getPosition() const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}