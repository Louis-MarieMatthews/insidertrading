#pragma once

#include <set>

#include "Company.h"
#include "DefaultObservableId.h"
#include "I_ConstantObservable.h"
#include "I_ConstantObserver.h"
#include "PlanarPosition.h"
#include "Duration.h"

namespace it
{
  class GameData;

  class Sec : public I_ConstantObservable, public I_ConstantObserver
  {
    std::set<Company *> const &      companies_;
    ObservablePointer<Company const> currentTarget_;
    GameData &                       gameData_;
    PlanarPosition                   initialPosition_;
    bool                             inspecting_;
    DefaultObservableId              observableId_;
    PlanarPosition                   position_;
    int                              radius_;
    Duration &                       time_;
    Duration                         inspectingDuration_;

    Company const & getRandomCompany();

  public:
    Sec (GameData &, PlanarPosition const &, std::set<Company *> const &, Duration &);
    ~Sec();

    PlanarPosition const & getPosition() const;
    Company const * getTarget();
    Duration const & getInspectingDuration();

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}