#pragma once

#include "PlayerBalance.h"
#include "Duration.h"
#include "ObservablePointer.h"
#include "PlayerPosition.h"
#include "Boolean.h"

namespace it
{
  class Company;
  class Sec;

  class I_GameData
  {
  public:
    virtual virtual ~I_GameData() {};
    virtual Duration const & getTime() = 0; // TODO: could be const
    virtual PlayerBalance & getPlayersMoney() = 0; // TODO: rename to getPlayerBalance
    virtual std::set<Company *> const & getCompanies() = 0;
    virtual ObservablePointer<Company> & getCompanyBeingCleaned() = 0;
    virtual PlanarPosition & getPlayerPosition() = 0; // TODO: const method?
    virtual Sec & getSec() = 0;
    virtual void setCompanyBeingCleaned (Company *) = 0;
    virtual Boolean & isPlayerInTheGame() = 0;
  };
}