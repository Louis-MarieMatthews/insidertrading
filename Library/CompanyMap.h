#pragma once

#include "I_CompanyMapItem.h"

namespace it
{
  class CompanyMap
  {
    static unsigned short const N_ROWS_ {50};
    static unsigned short const N_COLUMNS_ {50};

    I_CompanyMapItem * items_[N_ROWS_][N_COLUMNS_];

  public:
    CompanyMap();
    ~CompanyMap();
  };
}