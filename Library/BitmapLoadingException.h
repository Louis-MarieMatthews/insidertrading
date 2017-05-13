#pragma once

#include <exception>
#include <string>

namespace it
{
  class BitmapLoadingException : public std::exception
  {
  private :
    const std::string message_;
  public :
    BitmapLoadingException ();
    BitmapLoadingException (std::string const&);
    const char* what() const throw();
  };
}
