#pragma once

#include "Company.h"
#include "CompanyContextualMenu.h"
#include "ContextualMenuBitmap.h"
#include "DefaultLocatedRectangle.h"
#include "DefaultObservableId.h"
#include "DefaultContextualMenu.h"
#include "I_LocatedInteractiveBitmap.h"
#include "FontFormat.h"

namespace it
{
  class CompanyIcon : public I_LocatedInteractiveBitmap
  {
    static unsigned short const     WIDTH_ {300};
    static unsigned short const     HEIGHT_ {200};

    ALLEGRO_BITMAP *                bitmap_;
    ALLEGRO_BITMAP *                bitmapHovered_;
    ALLEGRO_BITMAP *                bitmapNotHovered_;
    Company const &                 company_;
    CompanyContextualMenu           contextualMenu_;
    FontFormat                      fontFormat_;
    bool                            isHovered_;
    bool                            isLastFetchedBitmapUpToDate_;
    DefaultObservableId             observableId_;
    PlanarPosition                  position_;
    DefaultLocatedRectangle         rectangle_;

    void setHovered (bool const &);

  public:
    CompanyIcon (Company &, I_GameData &, PlanarPosition const &);
    ~CompanyIcon();
    Company const & getCompany();

    // Inherited via I_LocatedInteractiveBitmap
    virtual I_ObservableId const & getObservableId() const override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual unsigned int const & getWidth() const override;
    virtual unsigned int const & getHeight() const override;
    virtual bool contains (PlanarPosition const &) const override;
    virtual int const & getX() const override;
    virtual int const & getY() const override;
    virtual PlanarPosition const & getCenter() const override;
    virtual PlanarPosition const & getPosition() const override;
  };
}