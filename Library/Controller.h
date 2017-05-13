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

// TODO: refactor in singleton?
// TODO: use dependency injection pattern?
namespace it
{
  void startProgram()
  {
    ALLEGRO_DISPLAY*   display (nullptr);
    ALLEGRO_TIMER*     timer (nullptr);
    ALLEGRO_TIMER*     seconds (nullptr);
    const unsigned int FPS (60);

    if (!al_init()) {
      throw AllegroInitializationException ("Could not initialise Allegro.");
    }
    
    if (!al_init_image_addon()) {
      fprintf(stderr, "Could not initialise image addon.");
      throw std::exception(); // TODO: custom ex
    }

    if (!al_init_primitives_addon()) {
      fprintf(stderr, "Could not initialise primitives addon.");
      throw std::exception(); // TODO: custom ex
    }

    if (!al_install_mouse()) {
      fprintf(stderr, "Could not initialise mouse.");
      throw std::exception(); // TODO: custom ex
    }

    if (!al_install_keyboard()) {
      fprintf(stderr, "Could not initialise keyboard.");
      throw std::exception(); // TODO: custom ex
    }

    if (!al_init_font_addon()) {
      fprintf(stderr, "Could not initialise fonts addon.");
      throw std::exception(); // TODO: custom ex
    }

    if (!al_init_ttf_addon()) {
      fprintf(stderr, "Could not initialise ttf addon.");
      throw std::exception(); // TODO: custom ex
    }
    

    //al_get_display_mode (al_get_num_display_modes() -1, &displayMode); // TODO: check function does not return NULL
    //al_set_new_display_flags (ALLEGRO_FULLSCREEN);
    //display = al_create_display (displayMode.width, displayMode.height); // TODO: check function does not return NULL
    display = al_create_display(1800, 900);
    if (!display) {
      fprintf(stderr, "Could not create display.");
      throw std::exception(); // TODO: custom ex
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
      fprintf(stderr, "Could not create timer.");
      al_destroy_display(display);
      throw std::exception(); // TODO: custom ex
    }
    al_start_timer(timer);

    seconds = al_create_timer(1.0);
    if (!seconds) {
      fprintf(stderr, "Could not create timer.");
      al_destroy_display(display);
      al_destroy_timer(timer);
      throw std::exception(); // TODO: custom ex
    }
    al_start_timer(seconds);

    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    if (!eventQueue)
      throw std::exception(); // TODO: custom ex
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(seconds));

    I_Menu * menu = new MainMenu(); //TODO: use factory pattern?
    I_AllegroEventAdapter * eventAdapter(new DefaultAllegroEventAdapter(timer, seconds));
    while (menu != nullptr) {
      while (!al_is_event_queue_empty(eventQueue)) {
        ALLEGRO_EVENT e;
        al_wait_for_event(eventQueue, &e);
        eventAdapter->update(e);
        menu->processFrame(eventAdapter);
        if (al_is_event_queue_empty(eventQueue)) {
          menu->draw();
        }
      }
      if (menu->getNext() != menu) {
        I_Menu* oldMenu = menu;
        menu = menu->getNext(); // TODO: do this delete the value previously pointed by menu?
        oldMenu->resetNext();
      }
    }
    delete eventAdapter;
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_timer(seconds);
    delete menu;
  }
}