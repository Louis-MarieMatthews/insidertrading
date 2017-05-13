#include "DefaultContextualMenu.h"
#include "NullContextualMenuChoice.h"
#include "ObserverListSingleton.h"
#include "DefaultObservableId.h"

namespace it
{
  DefaultContextualMenu::DefaultContextualMenu (const std::vector<I_ContextualMenuChoice*> choices) :
    choices_ (choices),
    observableId_ (DefaultObservableId())
  {
    for (auto c : choices) {
      ObserverListSingleton::getInstance().addObserver (c->getObservableId(), *this);
    }
  }



  DefaultContextualMenu::DefaultContextualMenu()
  {
    for (auto c : choices_) {
      ObserverListSingleton::getInstance().removeObserver (c->getObservableId(), *this);
    }
  }


  
  std::vector<I_ContextualMenuChoice*> DefaultContextualMenu::getChoices() const
  {
    return choices_;
  }



  unsigned int DefaultContextualMenu::getLongestChoiceCharacterCount() const
  {
    unsigned int biggestLength (0);
    for (I_ContextualMenuChoice* cmc : choices_) {
      if (cmc->getText().length() > biggestLength) {
        biggestLength = cmc->getText().length();
      }
    }
    return biggestLength;
  }



  unsigned int DefaultContextualMenu::getNumberOfChoices() const
  {
    return choices_.size();
  }


  void DefaultContextualMenu::notifyObserver (I_ObservableId const &)
  {
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  void DefaultContextualMenu::addChoice (I_ContextualMenuChoice & choice)
  {
    choices_.push_back (&choice);
  }



  I_ObservableId const & DefaultContextualMenu::getObservableId() const
  {
    return observableId_;
  }
}