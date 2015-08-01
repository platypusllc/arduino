#include "Controller.h"
#include "Board.h"

using platypus::impl::Led;

Led::Led()
: r_(0), g_(0), b_(0)
, isActive_(false)
{
  // Do nothing.
}

Led::~Led()
{
  // Do nothing.
}

void Led::begin()
{
  // Turn on red LED output and set current value.
  pinMode(board::LED.R, OUTPUT);
  digitalWrite(board::LED.R, !r_);

  // Turn on green LED output and set current value.
  pinMode(board::LED.G, OUTPUT);
  digitalWrite(board::LED.G, !g_);

  // Turn on blue LED output and set current value.
  pinMode(board::LED.B, OUTPUT);
  digitalWrite(board::LED.B, !b_);

  // Indicate that the LED I/O is initialized.
  isActive_ = true;
}

void Led::end()
{
  // Turn off all LED outputs.
  pinMode(board::LED.R, INPUT);
  pinMode(board::LED.G, INPUT);
  pinMode(board::LED.B, INPUT);

  // Indicate that the LED I/O is no longer initialized.
  isActive_ = false;
}

void Led::set(int red, int green, int blue)
{
  R(red);
  G(green);
  B(blue);
}

void Led::R(int red)
{
  r_ = red;

  if (isActive_)
    digitalWrite(board::LED.R, !r_);
}

int Led::R()
{
  return r_;
}

void Led::G(int green)
{
  g_ = green;

  if (isActive_)
    digitalWrite(board::LED.G, !g_);
}

int Led::G()
{
  return g_;
}

void Led::B(int blue)
{
  b_ = blue;

  if (isActive_)
    digitalWrite(board::LED.B, !b_);
}

int Led::B()
{
  return b_;
}
