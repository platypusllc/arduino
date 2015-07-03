#include "Controller.h"
#include "Board.h"
#include <Arduino.h>

using platypus::impl::Controller;

uint32_t swap(uint32_t bytes)
{
  return ((bytes << 24) & 0xFF000000)
         | ((bytes <<  8) & 0x00FF0000)
         | ((bytes >>  8) & 0x0000FF00)
         | ((bytes >> 24) & 0x000000FF);
}

void driveLoop(void *data)
{
  size_t driveIdx = (size_t)data;
  Controller &controller = static_cast<Controller>platypus::getController();
  while (true)
  {
    controller.driveModules_[driveIdx].loop();
  }
}

void multiLoop(void *data)
{
  size_t multiIdx = (size_t)data;
  Controller &controller = static_cast<Controller>platypus::getController();
  while (true)
  {
    controller.multiModules_[multiIdx].loop();
  }
}

Controller::Controller()
{
  for (size_t driveIdx = 0; driveIdx < platypus::board::NUM_DRIVE_PORTS; ++driveIdx)
  {
    Scheduler.start(driveLoop, (void *)driveIdx);
  }
  
  for (size_t multiIdx = 0; multiIdx < platypus::board::NUM_DRIVE_PORTS; ++multiIdx)
  {
    Scheduler.start(multiLoop, (void *)driveIdx);
  }
}
