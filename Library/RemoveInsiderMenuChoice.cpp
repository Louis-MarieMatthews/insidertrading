#include "RemoveInsiderMenuChoice.h"

#include "Sec.h"
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



  RemoveInsiderMenuChoice::RemoveInsiderMenuChoice (Company & company, I_GameData & gameData) :
    company_ (company),
    gameData_ (gameData),
    isDisabled_ (!company.hasInsiders()),
    secTarget_ (gameData.getSec().getObservableTarget()),
    text_ ("Remove insiders")
  {
    ObserverListSingleton::getInstance().addObserver (company_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (secTarget_.getObservableId(), *this);
  }



  RemoveInsiderMenuChoice::~RemoveInsiderMenuChoice()
  {
    ObserverListSingleton::getInstance().removeObserver (company_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (secTarget_.getObservableId(), *this);
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
      gameData_.setCompanyBeingCleaned (&company_);
    }
  }



  void RemoveInsiderMenuChoice::notifyObserver (I_ObservableId const & observableId)
  {
    if (&company_.getObservableId() == &observableId ||
        &secTarget_.getObservableId() == &observableId) {
      setDisabled (!company_.hasInsiders() || secTarget_.getPointer() != &company_);
    }
  }
}