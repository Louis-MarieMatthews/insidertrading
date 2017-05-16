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



  AddInsiderMenuChoice::AddInsiderMenuChoice (Company & company, PlayerBalance & playerBalance) :
    company_ (company),
    isDisabled_ (false),
    playerBalance_ (playerBalance),
    text_ (std::string ("Add insider ($" + std::to_string (company.getInsiderCost()) + ")"))
  {
    setDisabled (company_.hasInsiders() || playerBalance_ < company_.getInsiderCost());
    ObserverListSingleton::getInstance().addObserver (company_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (playerBalance_.getObservableId(), *this);
  }



  AddInsiderMenuChoice::~AddInsiderMenuChoice()
  {
    ObserverListSingleton::getInstance().removeObserver (company_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (playerBalance_.getObservableId(), *this);
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
    if (&company_.getObservableId() == &observableId ||
        &playerBalance_.getObservableId() == &observableId) {
      setDisabled (company_.hasInsiders() || playerBalance_ < company_.getInsiderCost());
    }
  }
}