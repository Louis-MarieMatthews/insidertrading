#pragma once

#include "allegro5\allegro_font.h"

#include "DefaultObservableId.h"
#include "I_LocatedInteractiveBitmap.h"
#include "PlanarDimensions.h"
#include "DefaultLocatedRectangle.h"

// TODO: separate interface & implementation
namespace it
{
  enum Style {small, large};

  class FontFormat : public I_LocatedInteractiveBitmap
  {
    ALLEGRO_COLOR           color_;
    ALLEGRO_BITMAP *        bitmap_;
    ALLEGRO_FONT *          font_;
    unsigned short          fontSize_;
    bool                    isLastFetchedBitmapUpToDate_;
    short                   lineHeight_;
    DefaultObservableId     observableId_;
    short                   paddingX_;
    short                   paddingY_;
    PlanarPosition          position_;
    DefaultLocatedRectangle rectangle_;
    std::string             text_;

    static unsigned short getFontSize (PlanarDimensions const &, Style const &);
    static unsigned short getYPadding (PlanarDimensions const &, Style const &);

  public:
    FontFormat (unsigned short const &, short const &, short const &);
    FontFormat (PlanarDimensions const &, unsigned short const &);
    FontFormat (PlanarDimensions const &);
    FontFormat (PlanarDimensions const &, Style const &);
    ~FontFormat();

    ALLEGRO_FONT * getFont() const; // TODO: return const font
    unsigned short const & getFontSize() const;
    short const & getXPadding() const;
    short const & getYPadding() const;
    short const & getLineHeight() const;

    // Inherited via I_LocatedInteractiveBitmap
    virtual I_ObservableId const & getObservableId() const override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual unsigned int const & getWidth() const override;
    virtual unsigned int const & getHeight() const override;
    virtual bool contains (PlanarPosition const &) const override;
    virtual int const & getX() const override;
    virtual int const & getY() const override;
    virtual PlanarPosition const & getCenter() const override;
    virtual PlanarPosition const & getPosition() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
  };
}