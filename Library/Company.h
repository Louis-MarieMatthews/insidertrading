#pragma once

#include <string>

#include "DefaultObservableId.h"
#include "PlanarPosition.h"
#include "PlayerBalance.h"
#include "I_ConstantObservable.h"
#include "I_ConstantObserver.h"
#include "CompanyMap.h"

namespace it
{
  class Company : public I_ConstantObservable, public I_ConstantObserver
  {
    unsigned long long              dividend_;
    Boolean                         hasInsiders_;
    unsigned long long              insiderCost_;
    unsigned short                  lastSecond_;
    CompanyMap                      map_;
    std::string                     name_;
    DefaultObservableId             observableId_;
    PlayerBalance &                 playerBalance_;
    PlanarPosition                  position_;
    Duration const &                time_;

  public:
    Company (I_GameData &, unsigned long long const &, std::string const &, std::string const &, PlanarPosition const &);
    ~Company();
    CompanyMap & getMap();
    std::string const & getName() const;
    PlanarPosition const & getPosition() const;
    unsigned long long const & getInsiderCost() const;
    Boolean const & hasInsiders() const;

    void addInsiders();
    void removeInsiders();

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}