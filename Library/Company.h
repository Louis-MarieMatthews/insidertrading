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
    Boolean                         hasInsiders_;
    static unsigned long long const insiderCost_ {100};
    CompanyMap                      map_;
    std::string                     name_;
    DefaultObservableId             observableId_;
    PlayerBalance &                 playerBalance_;
    PlanarPosition                  position_;
    Duration &                      time_;
    unsigned long long              dividende_;
    unsigned short                  lastSecond_;

  public:
    Company (I_GameData &, std::string const &, PlayerBalance &, PlanarPosition const &);
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

  bool operator< (Company const &, Company const &);
}