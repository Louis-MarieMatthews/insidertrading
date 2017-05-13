#pragma once

#include "DefaultObservableId.h"
#include "DefaultLocatedRectangle.h"
#include "FontFormat.h"
#include "I_LocatedInteractiveBitmap.h"

namespace it
{
  class MenuButton : public I_LocatedInteractiveBitmap
  {
    static unsigned short const TEXT_PADDING_ {20};
    ALLEGRO_BITMAP *            bitmap_;
    PlanarDimensions            dimensions_;
    FontFormat                  fontFormat_;
    bool                        isHovered_;
    bool                        isLastFetchedBitmapUpToDate_;
    DefaultObservableId         observableId_;
    PlanarPosition              position_;
    DefaultLocatedRectangle     rectangle_;
    std::string                 text_;

    static unsigned const       WIDTH_ {300}; // TODO: this and HEIGHT_ should be merged into a PlanarDimensions object
    static unsigned const       HEIGHT_ {70};

    void setHovered (const bool &);

  public:
    MenuButton (PlanarPosition const &, std::string const &);
    ~MenuButton();

    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual PlanarPosition const & getPosition() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual void reset() override;

    // Inherited via I_LocatedInteractiveBitmap
    virtual I_ObservableId const & getObservableId() const override;

    // Inherited via I_LocatedInteractiveBitmap
    virtual unsigned int const & getWidth() const override;
    virtual unsigned int const & getHeight() const override;
    virtual bool contains(PlanarPosition const &) const override;
    virtual int const & getX() const override;
    virtual int const & getY() const override;
  };
}