#pragma once

#include "CompanyMap.h"
#include "DefaultLocatedRectangle.h"
#include "DefaultObservableId.h"
#include "I_LocatedInteractiveBitmap.h"
#include "MapFormat.h"

namespace it
{
  class MapBitmap : public I_LocatedInteractiveBitmap, public I_ConstantObserver
  {
    ObservableSet<I_CompanyMapItem *> const & documents_;
    ALLEGRO_BITMAP *                          bitmap_;
    ALLEGRO_BITMAP *                          structureBitmap_;
    ALLEGRO_BITMAP *                          playerBitmap_;
    ALLEGRO_BITMAP *                          documentsBitmap_;
    MapFormat                                 format_;
    bool                                      isLastFetchedBitmapUpToDate_;
    bool                                      isDocumentsBitmapUpToDate_;
    CompanyMap const &                        map_;
    DefaultObservableId                       observableId_;
    PlanarPosition const &                    playerPosition_;
    PlanarPosition                            position_; // TODO: move in rectangle
    DefaultLocatedRectangle                   rectangle_;

    void updateDocumentsBitmap();
    void updateStructureBitmap();
    void updatePlayerBitmap();

  public:
    MapBitmap (MapFormat const &, CompanyMap const &, PlanarPosition const & position);
    ~MapBitmap();

    // Inherited via I_LocatedInteractiveBitmap
    virtual I_ObservableId const & getObservableId() const override;
    virtual void reset() override;
    virtual void processEvent(I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual unsigned int const & getWidth() const override;
    virtual unsigned int const & getHeight() const override;
    virtual bool contains(PlanarPosition const &) const override;
    virtual int const & getX() const override;
    virtual int const & getY() const override;
    virtual PlanarPosition const & getCenter() const override;
    virtual PlanarPosition const & getPosition() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}