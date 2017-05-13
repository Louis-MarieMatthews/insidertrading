#include <string>

#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"

#include "AllegroInitializationException.h"
#include "DefaultAllegroEventAdapter.h"
#include "I_AllegroEventAdapter.h"
#include "I_Menu.h"
#include "MainMenu.h"
#include "ViewData.h"

// TODO: refactor in singleton?
// TODO: use dependency injection pattern?
// TODO: refactor: variables initialisation could be moved in subfunctions
namespace it
{
  void startProgram()
  {
    ALLEGRO_DISPLAY*       display (nullptr);
    ALLEGRO_TIMER*         fpsTimer (nullptr);
    ALLEGRO_TIMER*         secondsTimer (nullptr);
    const unsigned int     FPS (60);
    const PlanarDimensions winDimensions (1800, 900);

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
    //display = al_create_display (displayMode.width, displayMode.height); // TODO: check function does not return NULL
    display = al_create_display (winDimensions.getWidth(), winDimensions.getHeight()); // TEMP.
    if (!display) {
      throw AllegroInitializationException ("Could not initialise display."); // TODO: custom ex
    }

    fpsTimer = al_create_timer (1.0 / FPS);
    if (!fpsTimer) {
      al_destroy_display (display);
      throw AllegroInitializationException ("Could not initialise Allegro.");
    }
    al_start_timer (fpsTimer);

    secondsTimer = al_create_timer (1.0);
    if (!secondsTimer) {
      al_destroy_display (display);
      al_destroy_timer (fpsTimer);
      throw AllegroInitializationException ("Could not initialise seconds timer.");
    }
    al_start_timer(secondsTimer);

    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    if (!eventQueue) {
      al_destroy_display (display);
      al_destroy_timer (fpsTimer);
      al_destroy_timer (secondsTimer);
      throw AllegroInitializationException ("Could not initialise event queue.");
    }
    al_register_event_source (eventQueue, al_get_mouse_event_source());
    al_register_event_source (eventQueue, al_get_timer_event_source(fpsTimer));
    al_register_event_source (eventQueue, al_get_keyboard_event_source());
    al_register_event_source (eventQueue, al_get_timer_event_source(secondsTimer));

    ViewData viewData (winDimensions);
    I_BitmapView * currentView (viewData.getMainMenu());
    I_AllegroEventAdapter * eventAdapter (new DefaultAllegroEventAdapter (fpsTimer, secondsTimer));
    while (currentView != nullptr) {
      ALLEGRO_EVENT e;
      al_wait_for_event (eventQueue, &e);
      eventAdapter->update (e);
      currentView->processEvent (*eventAdapter);
      if (al_is_event_queue_empty (eventQueue) && e.timer.source == fpsTimer) {
        al_set_target_backbuffer (display);
        al_draw_bitmap (currentView->fetchBitmap(), 0, 0, 0);
        al_flip_display();
      }
      if (currentView->getNext() != currentView) {
        I_BitmapView * oldView = currentView;
        currentView = currentView->getNext(); // TODO: do this delete the value previously pointed by menu?
        oldView->reset();
      }
    }
    delete eventAdapter;
    delete currentView;
    al_destroy_event_queue (eventQueue);
    al_destroy_timer (secondsTimer);
    al_destroy_timer (fpsTimer);
    al_destroy_display (display);
  }
}