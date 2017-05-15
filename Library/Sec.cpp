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

    if (lastSecond_ == timeSinceInState_.getSecond()) {
      return;
    }

    lastSecond_ = timeSinceInState_.getSecond();

    if (currentTarget_.getPointer() == nullptr) {
      if (timeSinceInState_.getSecond() == maxSecondsOfIdleness_) {
        currentTarget_.setPointer (&getRandomCompany());
        ObserverListSingleton::getInstance().notifyObservers (observableId_);
      }
    }
    else if (currentTarget_.getPointer()->hasInsiders()) {
      if (timeSinceInState_.getSecond() >= maxSecondsOfInspectingInsidedCompany_) {
        if (currentTarget_.getPointer()->hasInsiders()) {
          gameData_.isPlayerInTheGame().setValue (false);
          timeSinceInState_.reset();
          currentTarget_.setPointer (nullptr);
          ObserverListSingleton::getInstance().notifyObservers (observableId_);
        }
      }
    }
    else if (timeSinceInState_.getSecond() >= maxSecondsOfInspectingGenuineCompany_) {
      timeSinceInState_.reset();
      currentTarget_.setPointer (nullptr);
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }



  Sec::Sec (I_GameData & gameData, PlanarPosition const & position, std::set<Company *> const & companies, Duration & time) :
    companies_ (companies),
    currentTarget_ (nullptr),
    gameData_ (gameData),
    initialPosition_ (position),
    inspecting_ (false),
    lastSecond_ (-1),
    maxSecondsOfIdleness_ (5),
    maxSecondsOfInspectingInsidedCompany_ (15),
    maxSecondsOfInspectingGenuineCompany_ (5),
    position_ (position),
    radius_ (300),
    time_ (time)
  {
    ObserverListSingleton::getInstance().addObserver (time_.getObservableId(), *this);
  }



  Sec::~Sec()
  {
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