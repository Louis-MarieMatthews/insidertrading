#include "Boolean.h"

#include "ObserverListSingleton.h"

namespace it
{
  Boolean::Boolean (bool const & value) :
    value_ (value)
  {
  }



  bool const & Boolean::getValue() const
  {
    return value_;
  }



  void Boolean::setValue (bool const & value)
  {
    if (value_ != value) {
      value_ = value;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }



  void Boolean::operator= (bool const & value)
  {
    setValue (value);
  }



  Boolean::operator bool() const
  {
    return value_;
  }



  I_ObservableId const & Boolean::getObservableId() const
  {
    return observableId_;
  }
}