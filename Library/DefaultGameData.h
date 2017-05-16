#pragma once

#include "Company.h"
#include "I_GameData.h"
#include "Sec.h"

namespace it
{
  class DefaultGameData : public I_GameData
  {
    std::set<Company *>        companies_;
    ObservablePointer<Company> companyBeingCleaned_;
    Boolean                    isPlayerInTheGame_;
    PlayerBalance              playersMoney_;
    Sec                        sec_;
    PlanarPosition             playerPosition_;
    Duration const &           time_;

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
  };
}