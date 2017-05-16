#include "MapFormat.h"

namespace it
{
  PlanarDimensions MapFormat::getItemDimensions (CompanyMap const & map, PlanarDimensions const & mapDimensions)
  {
    unsigned int itemWidth (mapDimensions.getWidth() / map.getNumberOfColums());
    unsigned int itemHeight (mapDimensions.getHeight() / map.getNumberOfRows());
    return PlanarDimensions (itemWidth, itemHeight);
  }



  MapFormat::MapFormat (PlanarDimensions const & itemDimensions, PlanarDimensions const & mapDimensions) :
    itemDimensions_ (itemDimensions),
    mapDimensions_ (mapDimensions)
  {
  }



  MapFormat::MapFormat (CompanyMap const & map, PlanarDimensions const & mapDimensions) :
    itemDimensions_ (getItemDimensions (map, mapDimensions)),
    mapDimensions_ (mapDimensions)
  {
  }



  PlanarDimensions const & MapFormat::getItemDimensions()
  {
    return itemDimensions_;
  }



  unsigned const & MapFormat::getItemWidth()
  {
    return itemDimensions_.getWidth();
  }



  unsigned const & MapFormat::getItemHeight()
  {
    return itemDimensions_.getHeight();
  }



  PlanarDimensions const & MapFormat::getMapDimensions()
  {
    return mapDimensions_;
  }



  unsigned const & MapFormat::getMapWidth()
  {
    return mapDimensions_.getWidth();
  }



  unsigned const & MapFormat::getMapHeight()
  {
    return mapDimensions_.getHeight();
  }



  int MapFormat::convertXToPixel (int const & x)
  {
    return x * itemDimensions_.getWidth();
  }



  int MapFormat::convertYToPixel (int const & y)
  {
    int yInPixel (static_cast<int> (y * itemDimensions_.getHeight()));
    return -yInPixel + mapDimensions_.getHeight() - itemDimensions_.getHeight();
  }
}