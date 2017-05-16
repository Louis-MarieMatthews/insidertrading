#include "CompanyContextualMenu.h"

#include "RemoveInsiderMenuChoice.h"
#include "AddInsiderMenuChoice.h"

namespace it
{
  CompanyContextualMenu::CompanyContextualMenu (Company & company, I_GameData & gameData) :
    gameData_ (gameData)
  {
    choices_.push_back (new RemoveInsiderMenuChoice (company, gameData));
    choices_.push_back (new AddInsiderMenuChoice (company, gameData.getPlayersMoney()));
  }



  CompanyContextualMenu::~CompanyContextualMenu()
  {
    for (auto c : choices_) {
      delete c;
    }
  }



  I_ObservableId const & CompanyContextualMenu::getObservableId() const
  {
    return observableId_;
  }



  std::vector<I_ContextualMenuChoice*> CompanyContextualMenu::getChoices() const
  {
    return choices_;
  }



  unsigned int CompanyContextualMenu::getLongestChoiceCharacterCount() const
  {
    unsigned int biggestLength (0);
    for (I_ContextualMenuChoice* cmc : choices_) {
      if (cmc->getText().length() > biggestLength) {
        biggestLength = cmc->getText().length();
      }
    }
    return biggestLength;
  }



  unsigned int CompanyContextualMenu::getNumberOfChoices() const
  {
    return choices_.size();
  }



  void CompanyContextualMenu::addChoice (I_ContextualMenuChoice & contextualMenuChoice)
  {

  }
}