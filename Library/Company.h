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
  class Company : public I_ConstantObservable
  {
    bool                            hasInsiders_;
    static unsigned long long const insiderCost_ {100};
    CompanyMap                      map_;
    std::string                     name_;
    DefaultObservableId             observableId_;
    PlayerBalance &                 playerBalance_;
    PlanarPosition                  position_;

  public:
    Company (GameData &, std::string const &, PlayerBalance &, PlanarPosition const &);
    ~Company();
    CompanyMap & getMap();
    std::string const & getName() const;
    PlanarPosition const & getPosition() const;
    unsigned long long const & getInsiderCost() const;

    bool const & hasInsiders() const;
    void addInsiders();
    void removeInsiders();

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };

  bool operator< (Company const &, Company const &);
}