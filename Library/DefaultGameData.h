#pragma once

#include "Company.h"
#include "I_GameData.h"
#include "Sec.h"

namespace it
{
  class DefaultGameData : public I_GameData, public I_ConstantObserver
  {
    std::set<Company *>        companies_;
    ObservablePointer<Company> companyBeingCleaned_;
    Boolean                    isPlayerInTheGame_;
    PlayerBalance              playersMoney_;
    Sec                        sec_;
    PlanarPosition             playerPosition_;
    Duration const &           programTime_;
    Duration                   gameTime_;

  public:
    DefaultGameData (Duration const &, std::string const &);
    ~DefaultGameData();
    virtual Duration const & getTime() override;
    virtual PlayerBalance & getPlayersMoney() override;
    virtual std::set<Company *> const & getCompanies() override;
    virtual ObservablePointer<Company> & getCompanyBeingCleaned() override;
    virtual PlanarPosition & getPlayerPosition() override;
    virtual Sec & getSec() override;
    virtual void setCompanyBeingCleaned (Company *) override;
    virtual Boolean & isPlayerInTheGame() override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}