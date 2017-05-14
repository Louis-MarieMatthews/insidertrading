#pragma once

#include "I_ContextualMenuChoice.h"
#include "DefaultObservableId.h"
#include "PlayerBalance.h"
#include "Company.h"

namespace it
{
  class RemoveInsiderMenuChoice : public I_ContextualMenuChoice, public I_ConstantObserver
  {
    DefaultObservableId   observableId_;
    std::string           text_;
    bool                  isDisabled_;
    Company &             company_;

    void setDisabled (bool const &);

  public:
    RemoveInsiderMenuChoice (Company &);
    ~RemoveInsiderMenuChoice();

    // Inherited via I_ContextualMenuChoice
    virtual I_ObservableId const & getObservableId() const override;
    virtual std::string const & getText() const override;
    virtual bool const & isDisabled() const override;
    virtual void select() override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}