#pragma once

#include <set>

#include "I_ContextualMenu.h"
#include "DefaultObservableId.h"

namespace it
{

  class CompanyContextualMenu : public I_ContextualMenu
  {
    DefaultObservableId observableId_;
    std::vector<I_ContextualMenuChoice *> choices_;

  public:
    CompanyContextualMenu();
    ~CompanyContextualMenu();

    // Inherited via I_ContextualMenu
    virtual I_ObservableId const & getObservableId() const override;
    virtual std::vector<I_ContextualMenuChoice*> getChoices() const override;
    virtual unsigned int getLongestChoiceCharacterCount() const override;
    virtual unsigned int getNumberOfChoices() const override;
    virtual void addChoice (I_ContextualMenuChoice &) override;
  };
}