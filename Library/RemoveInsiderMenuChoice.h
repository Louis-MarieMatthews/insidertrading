#pragma once

#include "Company.h"
#include "DefaultObservableId.h"
#include "I_GameData.h"
#include "I_ContextualMenuChoice.h"
#include "PlayerBalance.h"

namespace it
{
  // TODO: rename to RemoveInsiderContextualMenuChoice?
  class RemoveInsiderMenuChoice : public I_ContextualMenuChoice, public I_ConstantObserver
  {
    Company &                          company_;
    I_GameData &                         gameData_;
    bool                               isDisabled_;
    DefaultObservableId                observableId_;
    ObservablePointer<Company const> & secTarget_;
    std::string                        text_;

    void setDisabled (bool const &);

  public:
    RemoveInsiderMenuChoice (Company &, I_GameData &);
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