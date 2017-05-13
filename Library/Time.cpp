#include "Time.h"

#include <string>

#include "DefaultObservableId.h"
#include "ObserverListSingleton.h"

namespace it
{
  Time::Time() :
    second_ (0),
    minute_ (0),
    hour_ (0),
    day_ (1),
    month_ (1),
    year_ (2017),
    observableId_ (DefaultObservableId())
  {
  }



  Time::~Time()
  {
  }



  void Time::tick()
  {
    if (second_ + 1 >= 60) {
      second_ = 0;
      if (minute_ + 1 >= 60) {
        minute_ = 0;
        if (hour_ + 1 >= 24) {
          hour_ = 0;
          if (day_ + 1 >= 30) { // TODO: to make more accurate
            day_ = 1;
            if (month_ + 1 >= 12) {
              month_ = 1;
              year_++;
            }
            else {
              month_++;
            }
          }
          else {
            day_++;
          }
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
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  unsigned short int const & Time::getSecond() const
  {
    return second_;
  }



  unsigned short int const & Time::getMinute() const
  {
    return minute_;
  }



  unsigned short int const & Time::getHour() const
  {
    return hour_;
  }



  unsigned short int const & Time::getDay() const
  {
    return day_;
  }



  unsigned short int const & Time::getMonth() const
  {
    return month_;
  }

  unsigned short int const & Time::getYear() const
  {
    return year_;
  }



  std::string Time::getString() const
  {
    return std::to_string (year_) + "/" + std::to_string (month_) + "/" + std::to_string (day_) + " " + std::to_string (hour_) + ":" + std::to_string (minute_) + ":" + std::to_string (second_);
  }



  I_ObservableId const & Time::getObservableId() const
  {
    return observableId_;
  }
}