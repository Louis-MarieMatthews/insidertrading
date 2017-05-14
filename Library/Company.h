#pragma once

#include <string>

#include "DefaultObservableId.h"
#include "PlanarPosition.h"
#include "I_ConstantObservable.h"

namespace it
{
  class Company : public I_ConstantObservable
  {
    bool                hasInsiders_;
    std::string         name_;
    PlanarPosition      position_;
    DefaultObservableId observableId_;

  public:
    Company (std::string const &, PlanarPosition const &);
    std::string const & getName() const;
    PlanarPosition const & getPosition() const;
    bool const & hasInsiders() const;
    void addInsiders();
    void removeInsiders();

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };

  bool operator< (Company const &, Company const &);
}