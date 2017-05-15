#include "Controller.h"

namespace it
{
  Controller::Controller () :
    windowDimensions_ (1800, 900)
  {
    srand (time (nullptr));

    if (!al_init()) {
      throw AllegroInitializationException ("Could not initialise Allegro.");
    }
    
    if (!al_init_image_addon()) {
      throw AllegroInitializationException ("Could not initialise Allegro Image Addon.");
    }

    if (!al_init_primitives_addon()) {
      throw AllegroInitializationException ("Could not initialise Allegro Primitives Addon.");
    }

    if (!al_install_mouse()) {
      throw AllegroInitializationException ("Could not initialise Allegro Mouse Addon.");
    }

    if (!al_install_keyboard()) {
      throw AllegroInitializationException ("Could not initialise Allegro Keyboard Addon.");
    }

    if (!al_init_font_addon()) {
      throw AllegroInitializationException ("Could not initialise Allegro Font Addon.");
    }

    if (!al_init_ttf_addon()) {
      throw AllegroInitializationException ("Could not initialise Allegro TTF Addon.");
    }

    //al_get_display_mode (al_get_num_display_modes() -1, &displayMode); // TODO: check function does not return NULL
    //al_set_new_display_flags (ALLEGRO_FULLSCREEN);
    //window_ = al_create_display (displayMode.width, displayMode.height); // TODO: check function does not return NULL

    window_ = al_create_display (windowDimensions_.getWidth(), windowDimensions_.getHeight()); // TEMP.

    if (!window_) {
      throw AllegroInitializationException ("Could not initialise window_.");
    }

    timerFps_ = al_create_timer (1.0 / FPS_);
    if (!timerFps_) {
      throw AllegroInitializationException ("Could not initialise Allegro.");
    }

    timerCentiseconds_ = al_create_timer (0.01);
    if (!timerCentiseconds_) {
      throw AllegroInitializationException ("Could not initialise centiseconds timer.");
    }

    eventQueue_ = al_create_event_queue();
    if (!eventQueue_) {
      throw AllegroInitializationException ("Could not initialise event queue.");
    }
    al_register_event_source (eventQueue_, al_get_mouse_event_source());
    al_register_event_source (eventQueue_, al_get_timer_event_source(timerFps_));
    al_register_event_source (eventQueue_, al_get_keyboard_event_source());
    al_register_event_source (eventQueue_, al_get_timer_event_source(timerCentiseconds_));
  }



  Controller::~Controller()
  {
    delete currentView_;
    delete eventAdapter_;
    al_destroy_event_queue (eventQueue_);
    al_destroy_timer (timerFps_);
    al_destroy_timer (timerCentiseconds_);
    al_destroy_display (window_);
  }



  void Controller::startProgram()
  {
    // TODO: those variables could maybe be initialised in the constructor of a class (this one or a new one)
    DefaultGameData gameData;
    ViewData viewData (gameData, windowDimensions_);
    currentView_ = viewData.getMainMenu();
    eventAdapter_ = new DefaultAllegroEventAdapter (timerFps_, timerCentiseconds_);

    al_start_timer (timerCentiseconds_);
    al_start_timer (timerFps_);

    while (currentView_ != nullptr) {
      ALLEGRO_EVENT e;
      al_wait_for_event (eventQueue_, &e);
      eventAdapter_->update (e);
      if (eventAdapter_->isNewCentisecond()) {
        gameData.getTime().tick();
      }
      if (!eventAdapter_->isFpsFrame()) {
        currentView_->processEvent (*eventAdapter_);
      }
      if (al_is_event_queue_empty (eventQueue_) && e.timer.source == timerFps_) {
        al_set_target_backbuffer (window_);
        al_draw_bitmap (currentView_->fetchBitmap(), 0, 0, 0);
        al_flip_display();
      }
      if (currentView_->getNext() != currentView_) {
        I_BitmapView * oldView = currentView_;
        currentView_ = currentView_->getNext();
        oldView->reset();
      }
    }

    al_stop_timer (timerCentiseconds_);
    al_stop_timer (timerFps_);
  }
}