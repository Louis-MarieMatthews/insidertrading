#pragma once

#include "I_CompanyMapItem.h"
#include "PlayerPosition.h"
#include "I_GameData.h"
#include "ObservableSet.h"

namespace it
{
  enum Direction {up, down, left, right};

  class CompanyMap
  {
    static unsigned short const       N_ROWS_ {50};
    static unsigned short const       N_COLUMNS_ {50};
    
    Company &                         company_;
    I_CompanyMapItem *                items_[N_ROWS_][N_COLUMNS_];
    PlanarPosition                    playerEntryPoint_;
    double                            speed_;
    PlanarPosition                    playerPosition_;
    ObservableSet<I_CompanyMapItem *> documents_;

  public:
    CompanyMap (I_GameData &, Company &, std::string const &);
    ~CompanyMap();
    I_CompanyMapItem const * getItem (unsigned short const &, unsigned short const &) const;
    unsigned short const & getNumberOfRows() const;
    unsigned short const & getNumberOfColums() const;
    PlanarPosition const & getPlayerEntryPoint() const;
    PlanarPosition const & getPlayerPosition() const;
    ObservableSet<I_CompanyMapItem *> const & getDocuments() const;
    void movePlayer (Direction const &);
  };
}