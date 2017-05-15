#pragma once

#include "Company.h"
#include "GameData.h"
#include "Sec.h"

namespace it
{
  class DefaultGameData : public GameData
  {
    std::set<Company *>        companies_;
    ObservablePointer<Company> companyBeingCleaned_;
    Boolean                    isPlayerInTheGame_;
    PlayerBalance              playersMoney_;
    Duration                   time_;
    Sec                        sec_;
    PlanarPosition             playerPosition_;

  public:
    DefaultGameData();
    ~DefaultGameData();
    virtual Duration & getTime() override;
    virtual PlayerBalance & getPlayersMoney() override;
    virtual std::set<Company *> const & getCompanies() override;
    virtual ObservablePointer<Company> & getCompanyBeingCleaned() override;
    virtual PlanarPosition & getPlayerPosition() override;
    virtual Sec & getSec() override;
    virtual void setCompanyBeingCleaned (Company *) override;
    virtual Boolean & isPlayerInTheGame() override;
  };
}