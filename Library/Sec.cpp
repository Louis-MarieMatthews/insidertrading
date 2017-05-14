#include "Sec.h"

#include "GameData.h"
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
        return c;
      }
      else {
        i++;
      }
    }
    throw std::exception(); // TODO: better exception
  }



  Sec::Sec (PlanarPosition const & position, std::set<Company> const & companies, Duration & time) :
    companies_ (companies),
    currentTarget_ (nullptr),
    initialPosition_ (position),
    inspecting_ (false),
    position_ (position),
    radius_ (300),
    time_ (time)
  {
    ObserverListSingleton::getInstance().addObserver (time_.getObservableId(), *this);
  }



  PlanarPosition const & Sec::getPosition() const
  {
    return position_;
  }



  Company const * Sec::getTarget()
  {
    if (currentTarget_ == nullptr) {
      return nullptr;
    }
    else {
      return currentTarget_;
    }
  }



  I_ObservableId const & Sec::getObservableId() const
  {
    return observableId_;
  }



  void Sec::notifyObserver (I_ObservableId const & observableId)
  {
    static unsigned short lastSecond_ (-1); // makes sure that the first time notifyObserver is called, lastSecond_ will be different from the second count
    static unsigned short secondCount_ (0);

    if (&time_.getObservableId() == &observableId) {
      if (time_.getSecond() != lastSecond_) {
        secondCount_++;
      }
      lastSecond_ = time_.getSecond();

      if (currentTarget_ == nullptr) {
        if (secondCount_ == 5) {
          secondCount_ = 0;
          currentTarget_ = &getRandomCompany();
          ObserverListSingleton::getInstance().notifyObservers (observableId_);
        }
      }
      else {
        if (secondCount_ == 5) {
          secondCount_ = 0;
          currentTarget_ = nullptr;
          ObserverListSingleton::getInstance().notifyObservers (observableId_);
        }
      }
    }
  }
}