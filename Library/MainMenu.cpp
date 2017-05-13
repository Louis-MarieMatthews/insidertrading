#include "MainMenu.h"

#include "ObserverListSingleton.h"

namespace it
{
  PlanarPosition MainMenu::getButtonPosition (PlanarDimensions const & menuDimensions, unsigned short const & buttonNo)
  {
    PlanarPosition position ((menuDimensions.getWidth() - BUTTON_WIDTH_) / 2, TOP_MARGIN_ + (buttonNo * BUTTON_BOTTOM_MARGIN_));
    return position;
  }



  MainMenu::MainMenu (PlanarDimensions const & dimensions) :
    bitmap_ (nullptr),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    menuButton_ (getButtonPosition (dimensions, 0), "Quit")
  {
    ObserverListSingleton::getInstance().addObserver (menuButton_.getObservableId(), *this);
  }



  MainMenu::~MainMenu()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
    ObserverListSingleton::getInstance().removeObserver (menuButton_.getObservableId(), *this);
  }



  I_BitmapView * MainMenu::getNext()
  {
    return this;
  }



  void MainMenu::reset()
  {
    
  }



  void MainMenu::processEvent (I_AllegroEventAdapter const & e)
  {
    menuButton_.processEvent (e);
  }



  bool const & MainMenu::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * MainMenu::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getHeight());
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (0, 0, 0));
      al_draw_bitmap (menuButton_.fetchBitmap(), menuButton_.getPosition().getX(), menuButton_.getPosition().getY(), 0);
      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_ObservableId const & MainMenu::getObservableId() const
  {
    return observableId_;
  }



  void MainMenu::notifyObserver (I_ObservableId const & observableId_)
  {
    if (!menuButton_.isLastFetchedBitmapUpToDate()) {
      isLastFetchedBitmapUpToDate_ = false;
    }
  }
}