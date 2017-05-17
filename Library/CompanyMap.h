#pragma once

#include "I_CompanyMap.h"

#include "BribedEmployee.h"
#include "I_CompanyMapItem.h"
#include "I_GameData.h"
#include "ObservableSet.h"
#include "PlayerPosition.h"

namespace it
{
  class CompanyMap : public I_CompanyMap
  {
    static unsigned short const       N_ROWS_ {20};
    static unsigned short const       N_COLUMNS_ {50};
    
    PlanarPosition                    bribedEmployeePosition_;
    BribedEmployee *                  bribedEmployee_;
    Company &                         company_;
    I_CompanyMapItem *                items_[N_COLUMNS_][N_ROWS_];
    PlanarPosition                    playerEntryPoint_;
    double                            speed_;
    PlanarPosition                    playerPosition_;
    ObservableSet<I_CompanyMapItem *> documents_;

    PlanarPosition move (Direction const &, PlanarPosition const &);

  public:
    CompanyMap (I_GameData &, Company &, std::string const &);
    ~CompanyMap();
    virtual I_CompanyMapItem const * getItem (unsigned short const &, unsigned short const &) const;
    virtual unsigned short const & getNumberOfRows() const;
    virtual unsigned short const & getNumberOfColums() const;
    virtual PlanarPosition const & getPlayerEntryPoint() const;
    virtual PlanarPosition const & getPlayerPosition() const;
    virtual BribedEmployee * getBribedEmployee();
    virtual ObservableSet<I_CompanyMapItem *> const & getDocuments() const;
    virtual void movePlayer (Direction const &);
    virtual void moveBribedEmployee (Direction const &);

  };
}