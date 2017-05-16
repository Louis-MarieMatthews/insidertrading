#include "MainMenu.h"

#include "NewGameViewTransition.h"
#include "ObserverListSingleton.h"
#include "SimpleViewTransition.h"

namespace it
{
  PlanarPosition MainMenu::getButtonPosition (PlanarDimensions const & menuDimensions, unsigned short const & buttonNo)
  {
    PlanarPosition position ((menuDimensions.getWidth() - BUTTON_WIDTH_) / 2, TOP_MARGIN_ + (buttonNo * BUTTON_BOTTOM_MARGIN_));
    return position;
  }



  MainMenu::MainMenu (ViewData & viewData, PlanarDimensions const & dimensions) :
    mapBitmap_ (nullptr),
    buttonNewGame_ (getButtonPosition (dimensions, 1), "New Game", next_, new NewGameViewTransition (viewData)),
    buttonResumeGame_ (getButtonPosition (dimensions, 0), "Resume", next_, new SimpleViewTransition (nullptr)),
    buttonQuit_ (getButtonPosition (dimensions, 2), "Quit", next_, new SimpleViewTransition (nullptr)),
    dimensions_ (dimensions),
    gameData_ (viewData.getGameData()),
    isLastFetchedBitmapUpToDate_ (false),
    next_ (this),
    viewData_ (viewData)
  {
    ObserverListSingleton::getInstance().addObserver (buttonQuit_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (buttonNewGame_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (buttonResumeGame_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (viewData_.getObservableGameView().getObservableId(), *this);
  }



  MainMenu::~MainMenu()
  {
    if (mapBitmap_ != nullptr) {
      al_destroy_bitmap (mapBitmap_);
    }
    ObserverListSingleton::getInstance().removeObserver (buttonQuit_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (buttonResumeGame_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (buttonNewGame_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (viewData_.getObservableGameView().getObservableId(), *this);
  }



  I_BitmapView * MainMenu::getNext()
  {
    return next_;
  }



  void MainMenu::reset()
  {
    next_ = this;
    buttonResumeGame_.reset();
  }



  void MainMenu::processEvent (I_AllegroEventAdapter const & e)
  {
    buttonQuit_.processEvent (e);
    buttonNewGame_.processEvent (e);
    buttonResumeGame_.processEvent (e);
  }



  bool const & MainMenu::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * MainMenu::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      if (mapBitmap_ != nullptr) {
        al_destroy_bitmap (mapBitmap_);
      }
      mapBitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getHeight());
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());
      al_set_target_bitmap (mapBitmap_);
      al_clear_to_color (al_map_rgb (0, 0, 0));

      if (gameData_.getPointer() != nullptr) {
        al_draw_bitmap (buttonResumeGame_.fetchBitmap(), buttonResumeGame_.getPosition().getX(), buttonResumeGame_.getPosition().getY(), 0);
      }

      al_draw_bitmap (buttonNewGame_.fetchBitmap(), buttonNewGame_.getPosition().getX(), buttonNewGame_.getPosition().getY(), 0);
      al_draw_bitmap (buttonQuit_.fetchBitmap(), buttonQuit_.getPosition().getX(), buttonQuit_.getPosition().getY(), 0);
      al_set_target_bitmap (targetBitmap);
    }
    return mapBitmap_;
  }



  I_ObservableId const & MainMenu::getObservableId() const
  {
    return observableId_;
  }



  void MainMenu::notifyObserver (I_ObservableId const & observableId)
  {
    if (!buttonQuit_.isLastFetchedBitmapUpToDate() ||
        !buttonNewGame_.isLastFetchedBitmapUpToDate() ||
        !buttonResumeGame_.isLastFetchedBitmapUpToDate()) {
      isLastFetchedBitmapUpToDate_ = false;
    }
    if (&viewData_.getObservableGameView().getObservableId() == &observableId) {
      buttonResumeGame_.getViewTransition()->setTarget (viewData_.getGameView());
      isLastFetchedBitmapUpToDate_ = false;
    }
  }
}