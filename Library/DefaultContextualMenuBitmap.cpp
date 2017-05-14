#include "DefaultContextualMenuBitmap.h"

#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"

#include "AllegroInitializationException.h"
#include "BitmapCreationException.h"
#include "ObserverListSingleton.h"
#include "DefaultObservableId.h"

namespace it
{
  // TODO: make a class ContextualMenuChoice bitmap?
  int DefaultContextualMenuBitmap::getHoveredChoice (PlanarPosition const & position) const
  {
    int hoveredChoice (-1);
    if (contains (position)) {
      for (unsigned int i = 0; i < menu_->getNumberOfChoices(); i++) {
        bool hoveringCurrentLine = position.getY() > getY() + padding_ + i * lineHeight_ && position.getY() < getY() + padding_ + (i + 1) * lineHeight_;
        if (hoveringCurrentLine) {
          hoveredChoice = i;
        }
      }
    }
    else {
      hoveredChoice = -1;
    }

    return hoveredChoice;
  }



  DefaultLocatedRectangle DefaultContextualMenuBitmap::getLocatedRectangleForChoice (int const & choiceNo) const
  {
    if (choiceNo > menu_->getNumberOfChoices() || choiceNo < 0) {
      throw std::exception(); // TODO: more precise exception
    }
    DefaultLocatedRectangle r (PlanarPosition (getX(), getY() + lineHeight_ * choiceNo), PlanarDimensions (rectangle_->getWidth(), lineHeight_));
  }



  PlanarDimensions DefaultContextualMenuBitmap::getDimensions (I_ContextualMenu const * menu)
  {
    return PlanarDimensions (padding_ + menu->getLongestChoiceCharacterCount() * fontSize_ + padding_, padding_ + menu->getNumberOfChoices() * lineHeight_ + padding_);
  }



  DefaultContextualMenuBitmap::DefaultContextualMenuBitmap (I_ContextualMenu * menu, PlanarPosition const & position) :
    beingClicked_ (false),
    cachedBitmap_ (nullptr),
    fontFormat_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", 20, 0)), // TODO: should be initialised from outside
    hoveredChoiceNo_ (-1),
    isCachedBitmapUpToDate_ (false),
    menu_ (menu),
    rectangle_ (nullptr),
    observableId_ (DefaultObservableId())
  {
    if (!fontFormat_)
      throw AllegroInitializationException ("Could not initialise the font of the contextual menu.");

    const PlanarDimensions dimensions (getDimensions (menu_));
    rectangle_ = new DefaultLocatedRectangle (position, dimensions);

    ObserverListSingleton::getInstance().addObserver (menu_->getObservableId(), *this);
  }



  DefaultContextualMenuBitmap::~DefaultContextualMenuBitmap()
  {
    ObserverListSingleton::getInstance().removeObserver (menu_->getObservableId(), *this);
    al_destroy_bitmap (cachedBitmap_);
    delete rectangle_;
  }



  const unsigned int& DefaultContextualMenuBitmap::getWidth() const
  {
    return rectangle_->getWidth();
  }



  const unsigned int& DefaultContextualMenuBitmap::getHeight() const
  {
    return rectangle_->getHeight();
  }



  bool DefaultContextualMenuBitmap::contains (PlanarPosition const & position) const
  {
    return rectangle_->contains (position);
  }



  const int& DefaultContextualMenuBitmap::getX() const
  {
    return rectangle_->getX();
  }



  const int& DefaultContextualMenuBitmap::getY() const
  {
    return rectangle_->getY();
  }



  PlanarPosition const & DefaultContextualMenuBitmap::getCenter() const
  {
    return rectangle_->getCenter();
  }



  ALLEGRO_BITMAP * DefaultContextualMenuBitmap::fetchBitmap()
  {
    if (!isCachedBitmapUpToDate_) {
      ALLEGRO_BITMAP* previousTargetBitmap = al_get_target_bitmap();

      ALLEGRO_BITMAP* wipBitmap = al_create_bitmap (rectangle_->getWidth(), rectangle_->getHeight()); // TODO: method to init & throw exception in the same time?
      if (!wipBitmap)
        throw BitmapCreationException();
      al_set_target_bitmap (wipBitmap);
      al_clear_to_color (al_map_rgb (255, 255, 255));

      std::vector<I_ContextualMenuChoice*> choices = menu_->getChoices();
      for (unsigned int i = 0; i < choices.size(); i++) {
        ALLEGRO_COLOR* textColor {nullptr};

        if (choices[i]->isDisabled()) {
          textColor = &al_map_rgb (100, 100, 100);
        }
        else {
          textColor = &al_map_rgb (0, 0, 0);
        }

        if (i == hoveredChoiceNo_ && !choices[i]->isDisabled()) {
          ALLEGRO_BITMAP* choiceBackground (al_create_bitmap (getWidth(), lineHeight_));
          if (!choiceBackground) {
            throw BitmapCreationException();
          }
          al_set_target_bitmap (choiceBackground);
          al_clear_to_color (al_map_rgb (200, 200, 200));
          if (beingClicked_) {
            ALLEGRO_BITMAP* line (al_create_bitmap (getWidth() - 2 * padding_, 3)); // TODO: hard-coded value
            if (!line) {
              throw BitmapCreationException();
            }
            al_set_target_bitmap (line);
            al_clear_to_color (*textColor);
            al_set_target_bitmap (choiceBackground);
            al_draw_bitmap (line, padding_, lineHeight_ - 5, 0);
            al_destroy_bitmap (line);
          }
          al_set_target_bitmap (wipBitmap);
          al_draw_bitmap (choiceBackground, 0, padding_ + lineHeight_ * i, 0);
          al_destroy_bitmap (choiceBackground);
        }
        al_draw_text (fontFormat_, *textColor, padding_, padding_ + lineHeight_ * i, ALLEGRO_ALIGN_LEFT, choices[i]->getText().c_str() );
      }

      al_set_target_bitmap (previousTargetBitmap);

      if (cachedBitmap_ != nullptr) {
        ALLEGRO_BITMAP * previousCachedBitmap = cachedBitmap_;
        cachedBitmap_ = wipBitmap;
        al_destroy_bitmap (previousCachedBitmap);
      }
      else {
        cachedBitmap_ = wipBitmap;
      }
    }
    return cachedBitmap_;
  }


  
  void DefaultContextualMenuBitmap::processEvent (I_AllegroEventAdapter const * allegroEvent)
  {
    const PlanarPosition mousePosition (allegroEvent->getMousePosition());
    if (allegroEvent->isCausedByAMouseMove()) {
      if (allegroEvent->isMouseWithin (*this)) {
        int hoveredChoiceNo (getHoveredChoice (mousePosition));
        if (hoveredChoiceNo != hoveredChoiceNo_ ) {
          hoveredChoiceNo_ = hoveredChoiceNo;
          isCachedBitmapUpToDate_ = false;
        }
      }

      if (allegroEvent->didTheMouseLeave (*this)) {
        hoveredChoiceNo_ = -1;
        isCachedBitmapUpToDate_ = false;
      }
    }
    else if (allegroEvent->wasTheMouseLeftClicked()) {
      if (allegroEvent->isMouseWithin (*this)) {
        beingClicked_ = true;
        if (hoveredChoiceNo_ != -1) {
          isCachedBitmapUpToDate_ = false;
        }
      }
    }
    else if (allegroEvent->wasTheMouseLeftClickReleased()) {
      beingClicked_ = false;
      if (allegroEvent->isMouseWithin (*this)) {
        if (hoveredChoiceNo_ != -1) {
          I_ContextualMenuChoice * selectedChoice = menu_->getChoices()[hoveredChoiceNo_];
          if (!selectedChoice->isDisabled()) { // TODO: remove. select method already checks.
            menu_->getChoices()[hoveredChoiceNo_]->select();
            isCachedBitmapUpToDate_ = false;
          }
        }
      }
      else {
        // TODO: (assume this is the current contextual menu bitmap), probably a bad thing
        ContextualMenuBitmapSingleton::getInstance().setContextualMenuBitmap (nullptr);
        isCachedBitmapUpToDate_ = false;
      }
    }

    if (!isCachedBitmapUpToDate_) {
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }



  void DefaultContextualMenuBitmap::notifyObserver (I_ObservableId const & id)
  {
    isCachedBitmapUpToDate_ = false;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  I_ObservableId const & DefaultContextualMenuBitmap::getObservableId() const
  {
    return observableId_;
  }
}