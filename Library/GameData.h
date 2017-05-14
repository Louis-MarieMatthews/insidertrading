#pragma once

#include "Company.h"
#include "PlayerBalance.h"
#include "Sec.h"
#include "Duration.h"
#include "ObservablePointer.h"

namespace it
{
  class GameData
  {
    std::set<Company *>        companies_;
    ObservablePointer<Company> companyBeingCleaned_;
    PlayerBalance              playersMoney_;
    Duration                   time_;
    Sec                        sec_;

  public:
    GameData();
    ~GameData();
    Duration & getTime();
    PlayerBalance & getPlayersMoney();
    std::set<Company *> const & getCompanies();
    ObservablePointer<Company> & getCompanyBeingCleaned();
    Sec & getSec();
    void setCompanyBeingCleaned (Company *);
  };
}