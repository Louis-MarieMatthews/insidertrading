#pragma once

#include <set>

#include "allegro5\allegro_font.h"

#include "DefaultLocatedRectangle.h"
#include "I_AllegroEventAdapter.h"
#include "I_EventSensitiveLocatedBitmap.h"
#include "PlanarDimensions.h"
#include "I_ConstantObserver.h"

namespace it
{
  class MenuBar : public I_EventSensitiveLocatedBitmap, public I_ConstantObserver // TODO: separate the shape and visual aspect from its semantic meaning (which would go in the view filter)
  {
  private:
    bool                    undrawnChanges_;
    ALLEGRO_BITMAP*         cachedBitmap_;
    ALLEGRO_COLOR           backgroundColor_;
    ALLEGRO_COLOR           textColor_;
    const ALLEGRO_FONT*     font_;
    DefaultLocatedRectangle rectangle_;
    I_ObservableId          observableId_;

  public:
    MenuBar (const PlanarPosition&, const PlanarDimensions&, const ALLEGRO_FONT*);
    ~MenuBar();
    virtual const unsigned int& getWidth() const override;
    virtual const unsigned int& getHeight() const override;
    virtual const int& getX() const override;
    virtual const int& getY() const override;
    virtual bool contains (const PlanarPosition&) const override;
    virtual ALLEGRO_BITMAP* fetchBitmap() override;
    virtual void processEvent (const I_AllegroEventAdapter*) override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver(I_ObservableId const &) override;

    // Inherited via I_EventSensitiveLocatedBitmap
    virtual I_ObservableId const & getObservableId() const override;
  };
}