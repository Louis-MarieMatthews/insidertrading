#pragma once

#include "Company.h"
#include "DefaultObservableId.h"
#include "I_ContextualMenuChoice.h"
#include "I_ConstantObserver.h"

namespace it
{
  // TODO: rename to AddInsiderContextualMenuChoice
  class AddInsiderMenuChoice : public I_ContextualMenuChoice, public I_ConstantObserver
  {
    Company &           company_;
    bool                isDisabled_;
    DefaultObservableId observableId_;
    PlayerBalance &     playerBalance_;
    std::string         text_;

    void setDisabled (bool const &);
  public:
    AddInsiderMenuChoice (Company &, PlayerBalance &);
    ~AddInsiderMenuChoice();

    // Inherited via I_ContextualMenuChoice
    virtual I_ObservableId const & getObservableId() const override;
    virtual std::string const & getText() const override;
    virtual bool const & isDisabled() const override;
    virtual void select() override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver(I_ObservableId const &) override;
  };
}