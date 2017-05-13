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
    position_ (position),
    time_ (time)
  {
    ObserverListSingleton::getInstance().addObserver (time_.getObservableId(), *this);
  }



  PlanarPosition const & Sec::getPosition() const
  {
    return position_;
  }



  I_ObservableId const & Sec::getObservableId() const
  {
    return observableId_;
  }



  void Sec::notifyObserver (I_ObservableId const & observableId)
  {
    float speed (2);
    if (&time_.getObservableId() == &observableId) {
      if (currentTarget_ == nullptr) {
        currentTarget_ = &getRandomCompany();
      }
      else if (position_.isNearby (currentTarget_->getPosition(), speed)) {
        currentTarget_ = &getRandomCompany();
      }
      else if (position_.getX() == currentTarget_->getPosition().getX()) {
        if (position_.getY() > currentTarget_->getPosition().getY()) {
          position_ = PlanarPosition (position_.getX(), position_.getY() - speed);
        }
        else {
          position_ = PlanarPosition (position_.getX(), position_.getY() + speed);
        }
        ObserverListSingleton::getInstance().notifyObservers (observableId_);
      }
      else {
        puts ("calculating positions");
        PlanarPosition const & targetPosition (currentTarget_->getPosition());

        int x = position_.getX() > targetPosition.getX() ? position_.getX() - speed : position_.getX() + speed;
        int y = position_.getY() > targetPosition.getY() ? position_.getY() - speed : position_.getY() + speed;

        //float m ((position_.getY() - targetPosition.getY()) / (position_.getX() - targetPosition.getX()));
        //float x (std::sqrt (std::pow (speed_, 2) / (1 + m)));
        //float y (m * x);

        position_ = PlanarPosition (x, y);
        ObserverListSingleton::getInstance().notifyObservers (observableId_);
      }
    }
  }
}