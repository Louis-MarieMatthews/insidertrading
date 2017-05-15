#pragma once

#include <set>

#include "DefaultAllegroEventAdapter.h"
#include "DefaultLocatedRectangle.h"
#include "I_ConstantObserver.h"
#include "allegro5\allegro_font.h"
#include "ContextualMenuBitmapSingleton.h"

// TODO: classes used are inconsistent with the rest of the system. The system should be made more consistent.
namespace it
{
  class ContextualMenuBitmap : public I_LocatedInteractiveBitmap, public I_ConstantObserver
  {
    const static unsigned short int fontSize_ {20};
    const static unsigned short int lineHeight_ {30};
    const static unsigned short int padding_ {10};

    bool                            isLastFetchedBitmapUpToDate_;
    short int                       hoveredChoiceNo_;
    bool                            beingClicked_;
    ALLEGRO_BITMAP *                cachedBitmap_;
    ALLEGRO_FONT *                  fontFormat_;
    I_ContextualMenu *              menu_;
    DefaultLocatedRectangle *       rectangle_;
    PlanarPosition                  position_;

    I_ObservableId                  observableId_;

    int getHoveredChoice (const PlanarPosition&) const;
    DefaultLocatedRectangle getLocatedRectangleForChoice (const int&) const; // TODO: how could a function return an interface?

  public:
    static PlanarDimensions getDimensions (I_ContextualMenu const *);

    ContextualMenuBitmap (I_ContextualMenu *, PlanarPosition const &);
    ~ContextualMenuBitmap();

    virtual const unsigned int& getWidth() const override;
    virtual const unsigned int& getHeight() const override;
    virtual bool contains (PlanarPosition const &) const override;
    virtual const int& getX() const override;
    virtual const int& getY() const override;
    virtual PlanarPosition const & getCenter() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual void reset() override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual PlanarPosition const & getPosition() const override;

    virtual I_ObservableId const & getObservableId() const override;

    // Inherited via I_Observer
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}