#pragma once

#include "I_CompanyMapItem.h"
#include "ObservableSet.h"

namespace it
{
  enum Direction {up, down, left, right};
  class BribedEmployee;

  class I_CompanyMap
  {
  public:
    virtual ~I_CompanyMap() {};
    virtual I_CompanyMapItem const * getItem (unsigned short const &, unsigned short const &) const = 0;
    virtual unsigned short const & getNumberOfRows() const = 0;
    virtual unsigned short const & getNumberOfColums() const = 0;
    virtual PlanarPosition const & getPlayerEntryPoint() const = 0;
    virtual PlanarPosition const & getPlayerPosition() const = 0;
    virtual BribedEmployee * getBribedEmployee() = 0;
    virtual ObservableSet<I_CompanyMapItem *> const & getDocuments() const = 0;
    virtual void movePlayer (Direction const &) = 0;
    virtual void moveBribedEmployee (Direction const &) = 0;
    virtual void reset() = 0;
  };
}