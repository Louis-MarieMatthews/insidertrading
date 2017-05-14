#include "AddInsiderMenuChoice.h"

#include "ObserverListSingleton.h"

namespace it
{
  void AddInsiderMenuChoice::setDisabled (bool const & isDisabled)
  {
    if (isDisabled_ != isDisabled) {
      isDisabled_ = isDisabled;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }



  AddInsiderMenuChoice::AddInsiderMenuChoice (Company & company) :
    company_ (company),
    isDisabled_ (false),
    text_ ("Add insider")
  {
    setDisabled (company_.hasInsiders());
    ObserverListSingleton::getInstance().addObserver (company_.getObservableId(), *this);
  }



  AddInsiderMenuChoice::~AddInsiderMenuChoice()
  {
    ObserverListSingleton::getInstance().removeObserver (company_.getObservableId(), *this);
  }



  I_ObservableId const & AddInsiderMenuChoice::getObservableId() const
  {
    return observableId_;
  }



  std::string const & AddInsiderMenuChoice::getText() const
  {
    return text_;
  }



  bool const & AddInsiderMenuChoice::isDisabled() const
  {
    return isDisabled_;
  }



  void AddInsiderMenuChoice::select()
  {
    if (!isDisabled_) {
      company_.addInsiders();
    }
  }



  void AddInsiderMenuChoice::notifyObserver (I_ObservableId const & observableId)
  {
    if (&company_.getObservableId() == &observableId) {
      setDisabled (company_.hasInsiders());
    }
  }
}