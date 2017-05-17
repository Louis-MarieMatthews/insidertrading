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
  class I_GameData;

  class Sec : public I_ConstantObservable, public I_ConstantObserver
  {
    static unsigned short const      IDLENESS_S_ {5};
    static unsigned short const      INSPECTING_COMPANY_WITH_INSIDERS_ {20};

    std::set<Company *> const &      companies_;
    ObservablePointer<Company const> currentTarget_;
    I_GameData &                     gameData_;
    PlanarPosition                   initialPosition_;
    bool                             inspecting_;
    unsigned short                   lastSecond_;
    unsigned short                   maxSecondsOfInspectingGenuineCompany_;
    DefaultObservableId              observableId_;
    PlanarPosition                   position_;
    int                              radius_;
    Duration const &                 time_;
    Duration                         timeSinceInState_;
    Duration                         stateCountDown_;

    Company const & getRandomCompany();
    void updateInspection();

  public:
    Sec (I_GameData &, PlanarPosition const &, std::set<Company *> const &, Duration const &);
    ~Sec();
    void startInspecting();
    void stopInspecting();
    PlanarPosition const & getPosition() const;
    Company const * getTarget();
    ObservablePointer<Company const> & getObservableTarget();
    Duration const & getInspectingDuration();
    Duration const & getInspectingCountDown();

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}