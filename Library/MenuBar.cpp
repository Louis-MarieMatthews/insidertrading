#include "AllegroInitializationException.h"
#include "BitmapCreationException.h"
#include "MenuBar.h"
#include "NullContextualMenuChoice.h"
#include "ObserverListSingleton.h"
#include "DefaultObservableId.h"

namespace it
{
  MenuBar::MenuBar (const PlanarPosition& position, const PlanarDimensions& dimensions, const ALLEGRO_FONT* font) :
    backgroundColor_ (al_map_rgb (0, 0, 0)),
    cachedBitmap_ (nullptr),
    font_ (font),
    rectangle_ (position, dimensions),
    textColor_ (al_map_rgb (255, 255, 255)),
    undrawnChanges_ (true),
    observableId_ (DefaultObservableId())
  {
    if (!font_)
      throw AllegroInitializationException ("The font could not be initialised.");

    // TODO: ObserverListSingleton::getInstance().addObserver (world_.getPlayer().getBankAccount()->getObservableId(), *this);
  }


  MenuBar::~MenuBar()
  {
    // TODO: ObserverListSingleton::getInstance().removeObserver (world_.getPlayer().getBankAccount()->getObservableId(), *this);
    if (cachedBitmap_ != nullptr)
      al_destroy_bitmap (cachedBitmap_);
  }



  const unsigned int& MenuBar::getWidth() const
  {
    return rectangle_.getWidth();
  }



  const unsigned int& MenuBar::getHeight() const
  {
    return rectangle_.getHeight();
  }



  ALLEGRO_BITMAP* MenuBar::fetchBitmap()
  {
    if (undrawnChanges_) {
      ALLEGRO_BITMAP* bitmap = al_create_bitmap (rectangle_.getWidth(), rectangle_.getHeight());

      if (!bitmap)
        throw BitmapCreationException();

      ALLEGRO_BITMAP* previousTargetBitmap = al_get_target_bitmap();

      al_set_target_bitmap (bitmap);
      al_clear_to_color (backgroundColor_);

      if (cachedBitmap_ != nullptr) // TODO: is it necessary?
        al_destroy_bitmap (cachedBitmap_);
      cachedBitmap_ = bitmap;

      undrawnChanges_ = false;

      al_set_target_bitmap (previousTargetBitmap);
    }
    return cachedBitmap_;
  }



  void MenuBar::processEvent (const I_AllegroEventAdapter *)
  {
  }



  void MenuBar::notifyObserver (I_ObservableId const & id)
  {
    /* // TODO: else if (&id == &world_.getPlayer().getBankAccount()->getObservableId()) {
      undrawnChanges_ = true;
    }*/
  }



  I_ObservableId const & MenuBar::getObservableId() const
  {
    return observableId_;
  }



  const int& MenuBar::getX() const
  {
    return rectangle_.getX();
  }



  const int & MenuBar::getY() const
  {
    return rectangle_.getY();
  }



  bool MenuBar::contains (const PlanarPosition& position) const
  {
    return rectangle_.contains (position);
  }
}
