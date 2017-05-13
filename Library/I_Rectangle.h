#pragma once
namespace it
{
  class I_Rectangle
  {
  public:
    virtual ~I_Rectangle() {};
    virtual unsigned int const & getWidth() const = 0;
    virtual unsigned int const & getHeight() const = 0;
  };
}