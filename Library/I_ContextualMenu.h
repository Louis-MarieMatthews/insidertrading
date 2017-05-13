#pragma once

#include <vector>

#include "I_ContextualMenuChoice.h"
#include "I_ConstantObservable.h"

namespace it
{
  class I_ContextualMenu : public I_ConstantObservable
  {
  public:
    virtual ~I_ContextualMenu() {};
    virtual std::vector<I_ContextualMenuChoice*> getChoices() const = 0;
    virtual unsigned int getLongestChoiceCharacterCount() const = 0;
    virtual unsigned int getNumberOfChoices() const = 0;
    virtual void addChoice (I_ContextualMenuChoice &) = 0;
  };
}