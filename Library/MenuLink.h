#pragma once

#include <set>

#include "DefaultLocatedRectangle.h"
#include "I_EventSensitiveLocatedBitmap.h"
#include "I_Menu.h"

namespace it
{
  class MenuLink : public I_EventSensitiveLocatedBitmap
  {
    ALLEGRO_BITMAP *              bitmapHovered_;
    ALLEGRO_BITMAP *              bitmapNotHovered_;
    ALLEGRO_BITMAP *              cachedBitmap_;
    const static PlanarDimensions dimensions_;
    bool                          firstFrame_;
    bool                          hovered_;
    bool                          isLastFetchedBitmapUpToDate_;
    I_Menu * &                    menuNext_;
    I_ObservableId                observableId_;
    DefaultLocatedRectangle       rectangle_;
    I_Menu *                      targetMenu_;

  public:
    MenuLink (const PlanarPosition&, const std::string&, I_Menu*&, I_Menu*);
    ~MenuLink();
    void reset();

    virtual const unsigned int& getWidth() const override;
    virtual const unsigned int& getHeight() const override;
    virtual bool contains (const PlanarPosition&) const override;
    virtual const int &getX() const override;
    virtual const int &getY() const override;
    virtual ALLEGRO_BITMAP* fetchBitmap() override;
    virtual void processEvent (const I_AllegroEventAdapter*) override;

    // Inherited via I_EventSensitiveLocatedBitmap
    virtual I_ObservableId const & getObservableId() const override;
  };
}