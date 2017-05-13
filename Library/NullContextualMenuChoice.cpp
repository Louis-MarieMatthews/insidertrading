#include "NullContextualMenuChoice.h"
#include "DefaultObservableId.h"

namespace it
{
  NullContextualMenuChoice::NullContextualMenuChoice (const std::string text, bool isDisabled) :
    isDisabled_ (isDisabled),
    text_ (text),
    observableId_ (DefaultObservableId())
  {
  }



  const std::string& NullContextualMenuChoice::getText() const
  {
    return text_;
  }



  void NullContextualMenuChoice::select()
  {
  }



  const bool & NullContextualMenuChoice::isDisabled() const
  {
    return isDisabled_;
  }



  I_ObservableId const & NullContextualMenuChoice::getObservableId() const
  {
    return observableId_;
  }
}