#include "DefaultAllegroEventAdapter.h"

namespace it
{
  DefaultAllegroEventAdapter::DefaultAllegroEventAdapter (ALLEGRO_TIMER const * fpsTimer, ALLEGRO_TIMER const * secondsTimer, ALLEGRO_TIMER const * centisecondsTimer) :
    centisecondsTimer_ (centisecondsTimer),
    currentEvent_ (nullptr),
    currentLeftClickReleased_ (false),
    currentEscapeKeyPressed_ (false),
    fpsTimer_ (fpsTimer),
    secondsTimer_ (secondsTimer),
    previousEscapeKeyPressed_ (false),
    previousLeftClickReleased_ (false),
    currentPosition_ (nullptr),
    previousPosition_ (nullptr),
    isFpsFrame_ (false)
  {
  }



  void DefaultAllegroEventAdapter::update (ALLEGRO_EVENT const & allegroEvent)
  {
    if (currentEvent_ != nullptr) {
      delete currentEvent_;
    }
    currentEvent_ = new ALLEGRO_EVENT (allegroEvent);

    if (currentEvent_->type == ALLEGRO_EVENT_TIMER && currentEvent_->timer.source == fpsTimer_) {
      isFpsFrame_ = true;
    }
    else {
      isFpsFrame_ = false;
    }

    if (currentEvent_->type == ALLEGRO_EVENT_TIMER && currentEvent_->timer.source == secondsTimer_) {
      isNewSecond_ = true;
    }
    else {
      isNewSecond_ = false;
    }

    if (currentEvent_->type == ALLEGRO_EVENT_TIMER && currentEvent_->timer.source == centisecondsTimer_) {
      isNewCentisecond_ = true;
    }
    else {
      isNewCentisecond_ = false;
    }

    if (isCausedByAMouseMove()) {
      if (previousPosition_ != nullptr) {
        delete previousPosition_;
      }
      previousPosition_ = currentPosition_;
      currentPosition_ = new PlanarPosition (allegroEvent.mouse.x, allegroEvent.mouse.y);
    }

    previousLeftClickReleased_ = currentLeftClickReleased_;
    if (allegroEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
      currentLeftClickReleased_ = true;
    }
    else {
      currentLeftClickReleased_ = false;
    }

    previousEscapeKeyPressed_ = currentEscapeKeyPressed_;
    if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP && allegroEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
      currentEscapeKeyPressed_ = true;
    }
    else {
      currentEscapeKeyPressed_ = false;
    }
  }



  bool DefaultAllegroEventAdapter::isCausedByAMouseMove() const
  {
    if (currentEvent_->type == ALLEGRO_EVENT_MOUSE_AXES || currentEvent_->type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
      return true;
    }
    else {
      return false;
    }
  }



  bool DefaultAllegroEventAdapter::didTheMouseEnter (const I_LocatedRectangle& rectangle) const
  {
    if (currentPosition_ == nullptr) {
      return false;
    }
    else {
      if (previousPosition_ == nullptr) {
        if (rectangle.contains(*currentPosition_)) {
          return true;
        }
        else {
          return false;
        }
      }
      else {
        if (!rectangle.contains (*previousPosition_) && rectangle.contains (*currentPosition_)) {
          return true;
        }
        else {
          return false;
        }
      }
    }
  }



  bool DefaultAllegroEventAdapter::didTheMouseLeave (const I_LocatedRectangle& rectangle) const
  {
    if (currentPosition_ == nullptr) {
      if (previousPosition_ == nullptr) {
        return false;
      }
      else if (rectangle.contains (*previousPosition_)) {
        return true;
      }
      else {
        return false;
      }
    }
    else {
      if (rectangle.contains (*currentPosition_)) {
        return false;
      }
      else if (previousPosition_ == nullptr) {
        return true;
      }
      else if (rectangle.contains (*previousPosition_)) {
        return true;
      }
      else {
        return false;
      }
    }
  }



  bool DefaultAllegroEventAdapter::wasTheMouseLeftClicked() const
  {
    if (currentEvent_ != nullptr) {
      if (currentEvent_->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        return true;
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }



  bool DefaultAllegroEventAdapter::wasTheMouseLeftClickReleased() const
  {
    if (currentLeftClickReleased_ && !previousLeftClickReleased_) {
      return true;
    }
    else {
      return false;
    }
  }



  bool DefaultAllegroEventAdapter::isMouseWithin (const I_LocatedRectangle& rectangle) const
  {
    if (currentPosition_ != nullptr) {
      if (rectangle.contains(*currentPosition_)) {
        return true;
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }



  PlanarPosition const & DefaultAllegroEventAdapter::getMousePosition() const
  {
    if (currentPosition_ == nullptr)
      puts ("u");
    return *currentPosition_;
  }



  bool DefaultAllegroEventAdapter::wasEscapeKeyPressed() const
  {
    if (currentEscapeKeyPressed_ && !previousEscapeKeyPressed_) {
      puts ((std::string ("escape key pressed") + std::to_string ( time (nullptr))).c_str());
      return true;
    }
    else {
      return false;
    }
  }



  bool const & DefaultAllegroEventAdapter::isFpsFrame() const
  {
    return isFpsFrame_;
  }



  bool const & DefaultAllegroEventAdapter::isNewSecond() const
  {
    return isNewSecond_;
  }



  bool const & DefaultAllegroEventAdapter::isNewCentisecond() const
  {
    return isNewCentisecond_;
  }
}