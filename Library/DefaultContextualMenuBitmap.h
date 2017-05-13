#pragma once

#include <set>

#include "DefaultAllegroEventAdapter.h"
#include "DefaultLocatedRectangle.h"
#include "I_EventSensitiveLocatedBitmap.h"
#include "I_ConstantObserver.h"
#include "allegro5\allegro_font.h"

namespace it
{
  class DefaultContextualMenuBitmap : public I_EventSensitiveLocatedBitmap, public I_ConstantObserver
  {
    const static unsigned short int fontSize_ {20};
    const static unsigned short int lineHeight_ {30};
    const static unsigned short int padding_ {10};

    bool                            isCachedBitmapUpToDate_;
    short int                       hoveredChoiceNo_;
    bool                            beingClicked_;
    ALLEGRO_BITMAP *                cachedBitmap_;
    ALLEGRO_FONT *                  fontFormat_;
    I_ContextualMenu *              menu_;
    DefaultLocatedRectangle *       rectangle_;

    I_ObservableId                  observableId_;

    int getHoveredChoice (const PlanarPosition&) const;
    DefaultLocatedRectangle getLocatedRectangleForChoice (const int&) const; // TODO: how could a function return an interface?

  public:
    static PlanarDimensions getDimensions (I_ContextualMenu const *);

    DefaultContextualMenuBitmap (I_ContextualMenu *, PlanarPosition const &);
    ~DefaultContextualMenuBitmap();

    virtual const unsigned int& getWidth() const override;
    virtual const unsigned int& getHeight() const override;
    virtual bool contains (PlanarPosition const &) const override;
    virtual const int& getX() const override;
    virtual const int& getY() const override;
    virtual ALLEGRO_BITMAP* fetchBitmap() override; // TODO: space before *
    virtual void processEvent (I_AllegroEventAdapter const *) override;

    // Inherited via I_Observer
    virtual void notifyObserver (I_ObservableId const &) override;

    // Inherited via I_EventSensitiveLocatedBitmap
    virtual I_ObservableId const & getObservableId() const override;
  };
}