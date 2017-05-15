#include "MapBitmap.h"

#include "ObserverListSingleton.h"

namespace it
{
  void MapBitmap::updateDocumentsBitmap()
  {
    ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


    if (documentsBitmap_ != nullptr) {
      al_destroy_bitmap (documentsBitmap_);
    }

    documentsBitmap_ = al_create_bitmap (format_.getMapWidth(), format_.getMapHeight());
    al_set_target_bitmap (documentsBitmap_);
    std::set<I_CompanyMapItem *> const documents (documents_.getSet());
    for (auto d : documents) {
      ALLEGRO_BITMAP * document (al_load_bitmap ("../gamefiles/images/document.bmp"));
      al_draw_bitmap (document, format_.convertXToPixel (d->getPosition().getX()), format_.convertYToPixel (d->getPosition().getY()), 0);
      al_destroy_bitmap (document);
    }
    isDocumentsBitmapUpToDate_ = true;


    al_set_target_bitmap (targetBitmap);
  }



  void MapBitmap::updateStructureBitmap()
  {
    ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


    if (structureBitmap_ != nullptr) {
      al_destroy_bitmap (structureBitmap_);
    }
    structureBitmap_ = al_create_bitmap (format_.getMapWidth(), format_.getMapHeight());
    al_set_target_bitmap (structureBitmap_);
    al_clear_to_color (al_map_rgb (24, 124, 150));
    for (unsigned short r (0); r < map_.getNumberOfRows(); r++) {
      for (unsigned short c (0); c < map_.getNumberOfColums(); c++) {
        if (map_.getItem (r, c) == nullptr) {
          continue;
        }
        ALLEGRO_BITMAP * item (nullptr); // TODO: hard-coded values
        if (!map_.getItem (r, c)->isTraversable()) {
          item = al_create_bitmap (format_.getItemWidth(), format_.getItemHeight());
          al_set_target_bitmap (item);
          al_clear_to_color (al_map_rgb (0, 0, 0));
          al_set_target_bitmap (structureBitmap_);
          al_draw_bitmap (item, format_.convertXToPixel (r), format_.convertYToPixel (c), 0); // TODO: hard-coded values
          al_destroy_bitmap (item);
        }
      }
    }


    al_set_target_bitmap (targetBitmap);
  }



  void MapBitmap::updatePlayerBitmap()
  {
    playerBitmap_ = al_load_bitmap ("../gamefiles/images/player.bmp");
  }



  MapBitmap::MapBitmap (MapFormat const & format, CompanyMap const & map, PlanarPosition const & position) :
    documentsBitmap_ (nullptr),
    documents_ (map.getDocuments()),
    format_ (format),
    isLastFetchedBitmapUpToDate_ (false),
    isDocumentsBitmapUpToDate_ (false),
    map_ (map),
    playerPosition_ (map.getPlayerPosition()),
    position_ (position),
    rectangle_ (position, format_.getMapDimensions())
  {
    ObserverListSingleton::getInstance().addObserver (documents_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (playerPosition_.getObservableId(), *this);
  }



  MapBitmap::~MapBitmap()
  {
    ObserverListSingleton::getInstance().removeObserver (playerPosition_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (documents_.getObservableId(), *this);
    if (documentsBitmap_ != nullptr) {
      al_destroy_bitmap (documentsBitmap_);
    }
    if (structureBitmap_ != nullptr) {
      al_destroy_bitmap (structureBitmap_);
    }
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  I_ObservableId const & MapBitmap::getObservableId() const
  {
    return observableId_;
  }



  void MapBitmap::reset()
  {
  }



  void MapBitmap::processEvent (I_AllegroEventAdapter const & e)
  {
  }



  bool const & MapBitmap::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * MapBitmap::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (format_.getMapWidth(), format_.getMapHeight());
      al_set_target_bitmap (bitmap_);

      if (structureBitmap_ == nullptr) {
        updateStructureBitmap();
      }
      al_draw_bitmap (structureBitmap_, 0, 0, 0);

      if (!isDocumentsBitmapUpToDate_) {
        updateDocumentsBitmap();
      }
      al_draw_bitmap (documentsBitmap_, 0, 0, 0);

      if (playerBitmap_ == nullptr) {
        updatePlayerBitmap();
      }
      al_draw_bitmap (playerBitmap_, format_.convertXToPixel (playerPosition_.getX()), format_.convertYToPixel (playerPosition_.getY()), 0);

      isLastFetchedBitmapUpToDate_ = true;


      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  unsigned int const & MapBitmap::getWidth() const
  {
    return rectangle_.getWidth();
  }



  unsigned int const & MapBitmap::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool MapBitmap::contains (PlanarPosition const & position) const
  {
    return rectangle_.contains (position);
  }



  int const & MapBitmap::getX() const
  {
    return rectangle_.getX();
  }



  int const & MapBitmap::getY() const
  {
    return rectangle_.getY();
  }



  PlanarPosition const & MapBitmap::getCenter() const
  {
    return rectangle_.getCenter();
  }



  PlanarPosition const & MapBitmap::getPosition() const
  {
    return position_;
  }



  void MapBitmap::notifyObserver (I_ObservableId const & observableId)
  {
    if (&playerPosition_.getObservableId() == &observableId) {
      isLastFetchedBitmapUpToDate_ = false;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
    else if (&documents_.getObservableId() == &observableId) {
      isDocumentsBitmapUpToDate_ = false;
      isLastFetchedBitmapUpToDate_ = false;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }
}