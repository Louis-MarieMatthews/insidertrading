#include <string>

#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"

#include "AllegroInitializationException.h"
#include "DefaultAllegroEventAdapter.h"
#include "I_AllegroEventAdapter.h"
#include "MainMenu.h"
#include "ViewData.h"
#include "DefaultGameData.h"

// TODO: refactor in singleton?
// TODO: use dependency injection pattern?
// TODO: refactor: variables initialisation could be moved in subfunctions
// TODO: separate allegro initialisation, loop and view / game logic?
namespace it
{
  class Controller
  {
    const unsigned int            FPS_ {60};
                                  
    I_BitmapView *                currentView_;
    I_AllegroEventAdapter *       eventAdapter_;
    ALLEGRO_EVENT_QUEUE*          eventQueue_;
    ALLEGRO_TIMER *               timerCentiseconds_;
    ALLEGRO_TIMER *               timerFps_;
    ALLEGRO_DISPLAY *             window_;
    PlanarDimensions              windowDimensions_;

    Controller();
    Controller (Controller const &) = delete;
    Controller & operator= (Controller const &) = delete;

  public:
    static Controller & getInstance();

    ~Controller();
    void startProgram();
  };
}