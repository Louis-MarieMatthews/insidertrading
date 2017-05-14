#include "RemoveInsiderMenuChoice.h"

#include "ObserverListSingleton.h"

namespace it
{
  void RemoveInsiderMenuChoice::setDisabled (bool const & isDisabled)
  {
    if (isDisabled_ != isDisabled) {
      isDisabled_ = isDisabled;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }



  RemoveInsiderMenuChoice::RemoveInsiderMenuChoice (Company & company) :
    company_ (company),
    isDisabled_ (!company.hasInsiders()),
    text_ ("Remove insiders")
  {
    ObserverListSingleton::getInstance().addObserver (company_.getObservableId(), *this);
  }



  RemoveInsiderMenuChoice::~RemoveInsiderMenuChoice()
  {
    ObserverListSingleton::getInstance().removeObserver (company_.getObservableId(), *this);
  }



  I_ObservableId const & RemoveInsiderMenuChoice::getObservableId() const
  {
    return observableId_;
  }
  


  std::string const & RemoveInsiderMenuChoice::getText() const
  {
    return text_;
  }



  bool const & RemoveInsiderMenuChoice::isDisabled() const
  {
    return isDisabled_;
  }



  void RemoveInsiderMenuChoice::select()
  {
    if (!isDisabled_) {
      company_.removeInsiders();
    }
  }



  void RemoveInsiderMenuChoice::notifyObserver (I_ObservableId const & observableId)
  {
    if (&company_.getObservableId() == &observableId) {
      setDisabled (!company_.hasInsiders());
    }
  }
}