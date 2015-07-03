#ifndef PLATYPUS_BOARD_H
#define PLATYPUS_BOARD_H

#include <Arduino.h>

namespace platypus
{
namespace board
{

// Version structure.
struct Version
{ 
  int major;
  int minor;
  int patch;
};

// Board type definitions
struct LED
{ 
  int r;
  int g;
  int b;
};

struct Motor
{ 
  int enable;
  int servo;
  int current;
};

struct Sensor
{
  int rx_disable;
  int tx_enable;
  int rs485_te;
  int rs485_232;
  int gpio[4];
  int pwr_enable;
  int pwr_current;
  int analog;
};

enum GPIO
{
  RX_POS = 0,
  RX_NEG = 1,
  TX_POS = 2,
  TX_NEG = 3
};

// TODO: move this to an external CPP class.

// Board version definition.
const Version VERSION = {4, 0, 1}

// Pin definitions.
const LED LED = { 54, 55, 56 };

const size_t NUM_MOTORS = 2;

const Motor MOTOR[NUM_MOTORS] = {
  { 50, 11, A8 }, // Motor 0 
  { 48, 12, A9 }  // Motor 1
};

const size_t NUM_SENSORS = 4;

const Sensor SENSOR[NUM_SENSORS] = {
  { 32, 30, 36, 34, { 21, 2, 20, 3 }, 66,  A8, A7 }, // Sensor 0
  { 33, 31, 37, 35, { 19, 4, 18, 5 }, 67,  A9, A6 }, // Sensor 1
  { 24, 22, 28, 26, { 17, 6, 16, 7 }, 68, A10, A5 }, // Sensor 2
  { 25, 23, 29, 27, { 15, 8, 14, 9 }, 69, A11, A4 }  // Sensor 3
};

const int V_BATT = A3;
const int CHG_CTRL = 51;

const int HALF_DUPLEX01 = 38;
const int HALF_DUPLEX23 = 39;
const int LOOPBACK = 40;

const int PWR_INT = 44;
const int PWR_KILL = 46;

}
}

#endif // PLATYPUS_BOARD_H
