#pragma once

#include "Company.h"
#include "CompanyContextualMenu.h"
#include "DefaultContextualMenuBitmap.h"
#include "DefaultLocatedRectangle.h"
#include "DefaultObservableId.h"
#include "DefaultContextualMenu.h"
#include "I_LocatedInteractiveBitmap.h"

namespace it
{
  class CompanyIcon : public I_LocatedInteractiveBitmap
  {
    ALLEGRO_BITMAP *                bitmapHovered_;
    ALLEGRO_BITMAP *                bitmapNotHovered_;
    bool                            isLastFetchedBitmapUpToDate_;
    DefaultObservableId             observableId_;
    PlanarPosition                  position_;
    DefaultLocatedRectangle         rectangle_;
    bool                            isHovered_;
    CompanyContextualMenu           contextualMenu_;
    Company const &                 company_;

    void setHovered (bool const &);

  public:
    CompanyIcon (Company const &, PlanarPosition const &);
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

  bool operator< (CompanyIcon const &, CompanyIcon const &);
}