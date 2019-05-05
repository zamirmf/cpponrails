#include "type.hpp"

class Exception{
  private:
    typed_string message;

  public:
    Exception(typed_string message);
};