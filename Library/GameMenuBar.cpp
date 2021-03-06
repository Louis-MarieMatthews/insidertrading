#include "GameMenuBar.h"

#include "ObserverListSingleton.h"
#include "allegro5\allegro_ttf.h"
#include "Sec.h"

namespace it
{
  GameMenuBar::GameMenuBar (I_GameData & gameData, PlanarDimensions const & dimensions, PlanarPosition const & position) :
    fontFormat_ (dimensions),
    gameData_ (gameData),
    secCountDown_ (gameData.getSec().getInspectingCountDown()),
    isLastFetchedBitmapUpToDate_ (false),
    position_ (position),
    rectangle_ (position, dimensions),
    secTarget_ (gameData.getSec().getObservableTarget())
  {
    ObserverListSingleton::getInstance().addObserver (gameData.getPlayersMoney().getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (secCountDown_.getObservableId(), *this);
  }



  GameMenuBar::~GameMenuBar()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
    ObserverListSingleton::getInstance().removeObserver (gameData_.getPlayersMoney().getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (secCountDown_.getObservableId(), *this);
  }



  I_ObservableId const & GameMenuBar::getObservableId() const
  {
    return observableId_;
  }



  void GameMenuBar::reset()
  {
  }



  void GameMenuBar::processEvent (I_AllegroEventAdapter const &)
  {
  }



  bool const & GameMenuBar::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * GameMenuBar::fetchBitmap()
  {
    // fetchBitmap could be moved in an abstract class this class would inherit. It would call a function implement by this class to initialise the bitmap.
    if (!isLastFetchedBitmapUpToDate_) {
      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (rectangle_.getWidth(), rectangle_.getHeight());
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (0, 0, 0));
      al_draw_text (fontFormat_.getFont(), al_map_rgb (255, 255, 255), rectangle_.getWidth() - fontFormat_.getXPadding(), fontFormat_.getYPadding(), ALLEGRO_ALIGN_RIGHT, gameData_.getPlayersMoney().getString().c_str());

      if (secTarget_.getPointer() != nullptr && secTarget_.getPointer()->hasInsiders()) {
        al_draw_text (fontFormat_.getFont(), al_map_rgb (255, 255, 255), rectangle_.getWidth() / 2, fontFormat_.getYPadding(), ALLEGRO_ALIGN_CENTER, secCountDown_.getString().c_str());
      }


      //ALLEGRO_FONT * font (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", 20, 0));
      //al_draw_text (font, al_map_rgb (255, 255, 255), 5, 5, ALLEGRO_ALIGN_CENTER, "prout");
      //al_destroy_font (font);
      al_set_target_bitmap (targetBitmap);
      isLastFetchedBitmapUpToDate_ = true;
    }
    return bitmap_;
  }



  unsigned int const & GameMenuBar::getWidth() const
  {
    return rectangle_.getWidth();
  }



  unsigned int const & GameMenuBar::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool GameMenuBar::contains (PlanarPosition const & position) const
  {
    return rectangle_.contains (position);
  }



  int const & GameMenuBar::getX() const
  {
    return rectangle_.getX();
  }



  int const & GameMenuBar::getY() const
  {
    return rectangle_.getY();
  }



  PlanarPosition const & GameMenuBar::getCenter() const
  {
    return rectangle_.getCenter();
  }



  PlanarPosition const & GameMenuBar::getPosition() const
  {
    return position_;
  }



  void GameMenuBar::notifyObserver (I_ObservableId const & observableId)
  {
    if (&gameData_.getPlayersMoney().getObservableId() == &observableId ||
        &secCountDown_.getObservableId() == &observableId) {
      isLastFetchedBitmapUpToDate_ = false;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }
}