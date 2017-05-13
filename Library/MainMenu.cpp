#include "AllegroInitializationException.h"
#include "BitmapLoadingException.h"
#include "MainMenu.h"
#include "ObserverListSingleton.h"

#include <stdio.h>

namespace it
{
  // TODO: make constructor take an initiliasor as a parameter 
  MainMenu::MainMenu() :
    isRenderUpToDate_ (false),
    quitButton_ (new MenuLink (PlanarPosition (100, 0), std::string ("quit"), next_, nullptr)),
    next_ (this),
    wasDrawnAtLeastOnce_ (false)
  {
    ObserverListSingleton::getInstance().addObserver (quitButton_->getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (playButton_->getObservableId(), *this);
  }



  MainMenu::~MainMenu()
  { 
    ObserverListSingleton::getInstance().removeObserver (quitButton_->getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (playButton_->getObservableId(), *this);
    delete next_;
    delete quitButton_;
    delete playButton_;
  }



  void MainMenu::processFrame (const I_AllegroEventAdapter* eventAdapter)
  {
    quitButton_->processEvent (eventAdapter);
    playButton_->processEvent (eventAdapter);

    if (!isRenderUpToDate_ || !wasDrawnAtLeastOnce_) {
      if (next_ = this) {
        // draw()
      }
    }
  }



  void MainMenu::notifyObserver (I_ObservableId const & id)
  {
    if (&id == &quitButton_->getObservableId() || &id == &playButton_->getObservableId()) {
      isRenderUpToDate_ = false;
    }
  }



  void MainMenu::resetNext()
  {
    next_ = this;
    wasDrawnAtLeastOnce_ = false;
    quitButton_->reset();
    playButton_->reset();
  }



  I_Menu* const MainMenu::getNext() const
  {
    return next_;
  }



  void MainMenu::setNext (I_Menu* next)
  {
    next_ = next;
  }



  void MainMenu::draw()
  {
    // TODO: optimise (do not redraw the whole screen) TODO: dirty bit?
    al_clear_to_color (al_map_rgb (0, 0, 0));
    al_draw_bitmap (quitButton_->fetchBitmap(), quitButton_->getX(), quitButton_->getY(), 0);
    al_draw_bitmap (playButton_->fetchBitmap(), playButton_->getX(), playButton_->getY(), 0);
    al_flip_display();
    isRenderUpToDate_ = true;
    wasDrawnAtLeastOnce_ = true;
  }
}