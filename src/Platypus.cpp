#include "Platypus.h"
#include "impl/ControllerSingleton.h"

using namespace platypus;

/** 
 * Creates a single instance of the controller singleton.
 * This instance is used within all instantiated controllers. 
 */
Controller& getController() 
{
  static impl::Controller instance;
  return instance;
}
