#include "MainMenu.h"

#include "ObserverListSingleton.h"

namespace it
{
  PlanarPosition MainMenu::getButtonPosition (PlanarDimensions const & menuDimensions, unsigned short const & buttonNo)
  {
    PlanarPosition position ((menuDimensions.getWidth() - BUTTON_WIDTH_) / 2, TOP_MARGIN_ + (buttonNo * BUTTON_BOTTOM_MARGIN_));
    return position;
  }



  MainMenu::MainMenu (ViewData & viewData, PlanarDimensions const & dimensions) :
    bitmap_ (nullptr),
    buttonPlay_ (getButtonPosition (dimensions, 0), "Play", next_, viewData.getGameView()),
    buttonQuit_ (getButtonPosition (dimensions, 1), "Quit", next_, viewData.getExit()),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    next_ (this)
  {
    ObserverListSingleton::getInstance().addObserver (buttonPlay_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (buttonQuit_.getObservableId(), *this);
  }



  MainMenu::~MainMenu()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
    ObserverListSingleton::getInstance().removeObserver (buttonPlay_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (buttonQuit_.getObservableId(), *this);
  }



  I_BitmapView * MainMenu::getNext()
  {
    return next_;
  }



  void MainMenu::reset()
  {
    next_ = this;
  }



  void MainMenu::processEvent (I_AllegroEventAdapter const & e)
  {
    buttonQuit_.processEvent (e);
    buttonPlay_.processEvent (e);
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
      al_draw_bitmap (buttonPlay_.fetchBitmap(), buttonPlay_.getPosition().getX(), buttonPlay_.getPosition().getY(), 0);
      al_draw_bitmap (buttonQuit_.fetchBitmap(), buttonQuit_.getPosition().getX(), buttonQuit_.getPosition().getY(), 0);
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
    if (!buttonQuit_.isLastFetchedBitmapUpToDate() || !buttonPlay_.isLastFetchedBitmapUpToDate()) {
      isLastFetchedBitmapUpToDate_ = false;
    }
  }
}