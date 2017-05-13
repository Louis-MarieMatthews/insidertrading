#pragma once
#include "I_ContextualMenuChoice.h"

namespace it
{
  class NullContextualMenuChoice : public I_ContextualMenuChoice
  {
    const std::string text_;
    bool              isDisabled_;
    I_ObservableId    observableId_;

  public:
    NullContextualMenuChoice (const std::string, bool);
    virtual const std::string& getText() const override;
    virtual void select() override;
    virtual const bool& isDisabled() const override;

    // Inherited via I_ContextualMenuChoice
    virtual I_ObservableId const & getObservableId() const override;
  };
}