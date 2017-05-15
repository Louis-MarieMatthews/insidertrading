#pragma once

#include "PlanarDimensions.h"
#include "CompanyMap.h"

// dimensions are expressed in pixel
namespace it
{
  class MapFormat
  {
    PlanarDimensions itemDimensions_;
    PlanarDimensions mapDimensions_;

    static PlanarDimensions getItemDimensions (CompanyMap const &, PlanarDimensions const &);

  public:
    MapFormat (PlanarDimensions const &, PlanarDimensions const &);
    MapFormat (CompanyMap const &, PlanarDimensions const &);

    PlanarDimensions const & getItemDimensions();
    unsigned const & getItemWidth();
    unsigned const & getItemHeight();
    PlanarDimensions const & getMapDimensions();
    unsigned const & getMapWidth();
    unsigned const & getMapHeight();
    int convertXToPixel (int const &);
    int convertYToPixel (int const &);
  };
}