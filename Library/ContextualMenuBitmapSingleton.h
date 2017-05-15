#pragma once

#include <set>

#include "DefaultLocatedRectangle.h"
#include "I_ConstantObservable.h"
#include "I_ContextualMenu.h"
#include "I_LocatedInteractiveBitmap.h"

namespace it
{
  class ContextualMenuBitmapSingleton : public I_ConstantObservable
  {
    unsigned short int const        padding_;
    unsigned short int const        margin_;
    unsigned short int const        lineHeight_;
                                    
    I_LocatedInteractiveBitmap *    contextualMenuBitmap_;
    I_ObservableId                  observableId_;

    ContextualMenuBitmapSingleton();
    ContextualMenuBitmapSingleton (const ContextualMenuBitmapSingleton &) = delete;
    ContextualMenuBitmapSingleton & operator= (const ContextualMenuBitmapSingleton &) = delete;

  public:
    static ContextualMenuBitmapSingleton & getInstance();

    void setContextualMenuBitmap (I_LocatedInteractiveBitmap *);
    void setContextualMenu (I_ContextualMenu *, PlanarPosition const &);
    I_LocatedInteractiveBitmap * getContextualMenuBitmap() const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };
}