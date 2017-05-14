#pragma once

#include <set>

#include "I_ContextualMenu.h"
#include "I_ConstantObserver.h"

namespace it
{
  class DefaultContextualMenu : public I_ContextualMenu, public I_ConstantObserver
  {
    std::vector<I_ContextualMenuChoice*> choices_; // TODO: why pointer?

    I_ObservableId                       observableId_;

  public:
    DefaultContextualMenu (const std::vector<I_ContextualMenuChoice*> choices);
    DefaultContextualMenu();
    virtual std::vector<I_ContextualMenuChoice*> getChoices() const override;
    virtual unsigned int getLongestChoiceCharacterCount() const override;
    virtual unsigned int getNumberOfChoices() const override;

    virtual void notifyObserver (I_ObservableId const &) override;

    // Inherited via I_ContextualMenu
    virtual void addChoice (I_ContextualMenuChoice &) override;

    // Inherited via I_ContextualMenu
    virtual I_ObservableId const & getObservableId() const override;
  };
}