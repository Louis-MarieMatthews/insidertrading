#pragma once

#include <set>

#include "DefaultLocatedRectangle.h"
#include "I_ContextualMenu.h"
#include "I_EventSensitiveLocatedBitmap.h"
#include "I_ConstantObservable.h"

namespace it
{
  class ContextualMenuBitmapSingleton : public I_ConstantObservable
  {
    unsigned short int const             padding_;
    unsigned short int const             margin_;
    unsigned short int const             lineHeight_;
                                         
    I_EventSensitiveLocatedBitmap*       contextualMenuBitmap_;
                                         
    I_ObservableId                       observableId_;

    ContextualMenuBitmapSingleton();
    ContextualMenuBitmapSingleton (const ContextualMenuBitmapSingleton &) = delete;
    ContextualMenuBitmapSingleton & operator= (const ContextualMenuBitmapSingleton &) = delete;

  public:
    static ContextualMenuBitmapSingleton & getInstance();

    void setContextualMenuBitmap (I_EventSensitiveLocatedBitmap*);
    void setContextualMenu (I_ContextualMenu *, PlanarPosition const &);
    I_EventSensitiveLocatedBitmap* getContextualMenuBitmap() const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };
}