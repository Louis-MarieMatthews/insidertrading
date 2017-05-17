#include "MapBitmap.h"

#include "ObserverListSingleton.h"

namespace it
{
  void MapBitmap::updateDocumentsBitmap()
  {
    ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


    if (bitmapDocuments_ != nullptr) {
      al_destroy_bitmap (bitmapDocuments_);
    }

    bitmapDocuments_ = al_create_bitmap (format_.getMapWidth(), format_.getMapHeight());
    al_set_target_bitmap (bitmapDocuments_);
    std::set<I_CompanyMapItem *> const documents (documents_.getSet());
    for (auto d : documents) {
      ALLEGRO_BITMAP * document (al_load_bitmap ("../gamefiles/images/document.tga"));
      al_draw_scaled_bitmap (document, 0, 0, 200, 200, format_.convertXToPixel (d->getPosition().getX()), format_.convertYToPixel (d->getPosition().getY()), format_.getItemWidth(), format_.getItemHeight(), 0);
      al_destroy_bitmap (document);
    }
    isDocumentsBitmapUpToDate_ = true;


    al_set_target_bitmap (targetBitmap);
  }



  void MapBitmap::updateStructureBitmap()
  {
    ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


    if (bitmapStructure_ != nullptr) {
      al_destroy_bitmap (bitmapStructure_);
    }
    bitmapStructure_ = al_create_bitmap (format_.getMapWidth(), format_.getMapHeight());
    al_set_target_bitmap (bitmapStructure_);
    ALLEGRO_BITMAP * floor (al_load_bitmap ("../gamefiles/images/floor.bmp"));
    al_draw_bitmap (floor, 0, 0, 0);
    al_destroy_bitmap (floor);
    ALLEGRO_BITMAP * metal (al_load_bitmap ("../gamefiles/images/metal.bmp"));
    for (unsigned short c (0); c < map_.getNumberOfColums(); c++) {
      for (unsigned short r (0); r < map_.getNumberOfRows(); r++) {
        if (map_.getItem (c, r) == nullptr) {
          continue;
        }
        if (!map_.getItem (c, r)->isTraversable()) {
          al_set_target_bitmap (bitmapStructure_);
          al_draw_scaled_bitmap (metal, 0, 0, 200, 200, format_.convertXToPixel (c), format_.convertYToPixel (r), format_.getItemWidth(), format_.getItemHeight(), 0); // TODO: hard-coded values
        }
      }
    }
    al_destroy_bitmap (metal);


    al_set_target_bitmap (targetBitmap);
  }



  void MapBitmap::updatePlayerBitmap()
  {
    if (bitmapPlayer_ != nullptr) {
      al_destroy_bitmap (bitmapPlayer_);
    }
    bitmapPlayer_ = al_load_bitmap ("../gamefiles/images/player.tga");
  }



  void MapBitmap::updateBribedEmployeeBitmap()
  {
    if (bitmapBribedEmployee_ != nullptr) {
      al_destroy_bitmap (bitmapBribedEmployee_);
    }

    bitmapBribedEmployee_ = al_load_bitmap ("../gamefiles/images/employee.tga");
  }



  MapBitmap::MapBitmap (MapFormat const & format, CompanyMap & map, PlanarPosition const & position) :
    bitmapDocuments_ (nullptr),
    bribedEmployee_ (map.getBribedEmployee()),
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
    ObserverListSingleton::getInstance().addObserver (bribedEmployee_->getObservableId(), *this);
  }



  MapBitmap::~MapBitmap()
  {
    ObserverListSingleton::getInstance().removeObserver (playerPosition_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (documents_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (bribedEmployee_->getObservableId(), *this);
    if (bitmapDocuments_ != nullptr) {
      al_destroy_bitmap (bitmapDocuments_);
    }
    if (bitmapStructure_ != nullptr) {
      al_destroy_bitmap (bitmapStructure_);
    }
    if (bitmapMap_ != nullptr) {
      al_destroy_bitmap (bitmapMap_);
    }
    if (bitmapBribedEmployee_ != nullptr) {
      al_destroy_bitmap (bitmapBribedEmployee_);
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


      if (bitmapMap_ != nullptr) {
        al_destroy_bitmap (bitmapMap_);
      }
      bitmapMap_ = al_create_bitmap (format_.getMapWidth(), format_.getMapHeight());
      al_set_target_bitmap (bitmapMap_);
      al_clear_to_color (al_map_rgb (255, 0, 0));

      if (bitmapStructure_ == nullptr) {
        updateStructureBitmap();
      }
      al_draw_bitmap (bitmapStructure_, 0, 0, 0);

      if (!isDocumentsBitmapUpToDate_) {
        updateDocumentsBitmap();
      }
      al_draw_bitmap (bitmapDocuments_, 0, 0, 0);

      if (bitmapPlayer_ == nullptr) {
        updatePlayerBitmap();
      }
      al_draw_scaled_bitmap (bitmapPlayer_, 0, 0, 200, 200, format_.convertXToPixel (playerPosition_.getX()), format_.convertYToPixel (playerPosition_.getY()), format_.getItemWidth(), format_.getItemHeight(), 0);


      isLastFetchedBitmapUpToDate_ = true;
      al_set_target_bitmap (targetBitmap);
    }
    return bitmapMap_;
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
    if (&playerPosition_.getObservableId() == &observableId ||
        &bribedEmployee_->getObservableId() == &observableId) {
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