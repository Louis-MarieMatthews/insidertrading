#include "BitmapCreationException.h"

namespace it
{
  BitmapCreationException::BitmapCreationException()
  {

  }

  BitmapCreationException::~BitmapCreationException()
  {
  }

  const char* BitmapCreationException::what() const throw()
  {
    return "Could not create bitmap.";
  }
}