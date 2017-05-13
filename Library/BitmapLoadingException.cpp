#include "BitmapLoadingException.h"

namespace it
{
  BitmapLoadingException::BitmapLoadingException () : message_ ("The bitmap file could not be loaded.")
  {
    
  }



  BitmapLoadingException::BitmapLoadingException (std::string const& message) : message_ (message)
  {

  }



  const char* BitmapLoadingException::what() const
  {
    return message_.c_str();
  }
}