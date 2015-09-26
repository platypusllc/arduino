#include "platypus/Board.h"
#include "platypus/impl/Controller.h"
#include "Platypus.h"

using namespace platypus;

/** 
 * Creates a single instance of the controller singleton.
 * This instance is used within all instantiated controllers. 
 */
Controller& getController()
{
  return platypus::impl::Controller::instance();
}
