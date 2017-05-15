#pragma once

#include <set>

#include "I_CompanyMapItem.h"
#include "PlayerPosition.h"
#include "GameData.h"

namespace it
{
  enum Direction {up, down, left, right};

  class CompanyMap
  {
    static unsigned short const N_ROWS_ {50};
    static unsigned short const N_COLUMNS_ {50};

    I_CompanyMapItem *           items_[N_ROWS_][N_COLUMNS_];
    PlanarPosition               playerEntryPoint_;
    double                       speed_;
    PlanarPosition &             playerPosition_;
    std::set<I_CompanyMapItem *> documents_;

  public:
    CompanyMap (GameData &);
    ~CompanyMap();
    I_CompanyMapItem const * getItem (unsigned short const &, unsigned short const &) const;
    unsigned short const & getNumberOfRows() const;
    unsigned short const & getNumberOfColums() const;
    PlanarPosition const & getPlayerEntryPoint() const;
    void movePlayer (Direction const &) const;
  };
}