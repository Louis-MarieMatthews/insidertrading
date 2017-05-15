#include "Duration.h"

#include <string>

#include "DefaultObservableId.h"
#include "ObserverListSingleton.h"

namespace it
{
  Duration::Duration() :
    second_ (0),
    minute_ (0),
    hour_ (0),
    observableId_ (DefaultObservableId())
  {
  }



  Duration::~Duration()
  {
  }



  void Duration::tick()
  {
    if (centisecond_ + 1 >= 100) {
      centisecond_ = 0;
      if (second_ + 1 >= 60) {
        second_ = 0;
        if (minute_ + 1 >= 60) {
          minute_ = 0;
          if (hour_ + 1 >= 24) {
            hour_ = 0;
          }
          else {
            hour_++;
          }
        }
        else {
          minute_++;
        }
      }
      else {
        second_++;
      }
    }
    else {
      centisecond_++;
    }
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  void Duration::reset()
  {
    centisecond_ = 0;
    second_ = 0;
    minute_ = 0;
    hour_ = 0;
  }



  unsigned short int const & Duration::getCentisecond() const
  {
    return centisecond_;
  }



  unsigned short int const & Duration::getSecond() const
  {
    return second_;
  }



  unsigned short int const & Duration::getMinute() const
  {
    return minute_;
  }



  unsigned short int const & Duration::getHour() const
  {
    return hour_;
  }



  std::string Duration::getString() const
  {
    return std::to_string (hour_) + ":" + std::to_string (minute_) + ":" + std::to_string (second_) + ":" + std::to_string (centisecond_);
  }



  I_ObservableId const & Duration::getObservableId() const
  {
    return observableId_;
  }
}