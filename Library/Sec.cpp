#include "Sec.h"

#include "I_GameData.h"
#include "ObserverListSingleton.h"

namespace it
{
  Company const & Sec::getRandomCompany()
  {
    size_t nCompanies (companies_.size());
    unsigned short randomIndex (rand() % nCompanies);

    unsigned short i (0);
    for (auto & c : companies_) {
      if (i == randomIndex) {
        return *c;
      }
      else {
        i++;
      }
    }
    throw std::exception(); // TODO: better exception
  }



  void Sec::updateInspection()
  {
    timeSinceInState_.tick();
    stateCountDown_.untick();

    if (lastSecond_ == timeSinceInState_.getSecond()) {
      return;
    }

    lastSecond_ = timeSinceInState_.getSecond();

    if (stateCountDown_ == 0) {
      if (currentTarget_.getPointer() == nullptr) {
        timeSinceInState_.reset();
        currentTarget_.setPointer (&getRandomCompany());
        if (currentTarget_.getPointer()->hasInsiders()) {
          stateCountDown_ = Duration (0, 0, INSPECTING_COMPANY_WITH_INSIDERS_, 0);
        }
        else {
          stateCountDown_ = Duration (0, 0, maxSecondsOfInspectingGenuineCompany_, 0);
        }
        ObserverListSingleton::getInstance().notifyObservers (observableId_);
      }
      else if (currentTarget_.getPointer()->hasInsiders()) {
        gameData_.isPlayerInTheGame().setValue (false);
        timeSinceInState_.reset();
        currentTarget_.setPointer (nullptr);
        stateCountDown_ = Duration (0, 0, IDLENESS_S_, 0);
        ObserverListSingleton::getInstance().notifyObservers (observableId_);
      }
      else {
        timeSinceInState_.reset();
        currentTarget_.setPointer (nullptr);
        stateCountDown_ = Duration (0, 0, IDLENESS_S_, 0);
        ObserverListSingleton::getInstance().notifyObservers (observableId_);
      }
    }

  }



  Sec::Sec (I_GameData & gameData, PlanarPosition const & position, std::set<Company *> const & companies, Duration const & time) :
    companies_ (companies),
    gameData_ (gameData),
    initialPosition_ (position),
    inspecting_ (false),
    lastSecond_ (-1),
    maxSecondsOfInspectingGenuineCompany_ (5),
    position_ (position),
    radius_ (300),
    stateCountDown_ (0, 0, IDLENESS_S_, 0),
    time_ (time)
  {
    ObserverListSingleton::getInstance().addObserver (time_.getObservableId(), *this);
  }



  Sec::~Sec()
  {
    ObserverListSingleton::getInstance().removeObserver (time_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObservable (observableId_);
  }



  PlanarPosition const & Sec::getPosition() const
  {
    return position_;
  }



  Company const * Sec::getTarget()
  {
    if (currentTarget_.getPointer() == nullptr) {
      return nullptr;
    }
    else {
      return currentTarget_.getPointer();
    }
  }



  ObservablePointer<Company const> & Sec::getObservableTarget()
  {
    return currentTarget_;
  }



  Duration const & Sec::getInspectingDuration()
  {
    return timeSinceInState_;
  }



  Duration const & Sec::getInspectingCountDown()
  {
    return stateCountDown_;
  }



  I_ObservableId const & Sec::getObservableId() const
  {
    return observableId_;
  }



  void Sec::notifyObserver (I_ObservableId const & observableId)
  {
    if (&time_.getObservableId() == &observableId) {
      updateInspection();
    }
  }
}