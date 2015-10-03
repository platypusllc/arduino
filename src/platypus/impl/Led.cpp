#include "Led.h"
#include "platypus/Board.h"

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
  pinMode(board::LED.r, OUTPUT);
  digitalWrite(board::LED.r, !r_);

  // Turn on green LED output and set current value.
  pinMode(board::LED.g, OUTPUT);
  digitalWrite(board::LED.g, !g_);

  // Turn on blue LED output and set current value.
  pinMode(board::LED.b, OUTPUT);
  digitalWrite(board::LED.b, !b_);

  // Indicate that the LED I/O is initialized.
  isActive_ = true;
}

void Led::end()
{
  // Turn off all LED outputs.
  pinMode(board::LED.r, INPUT);
  digitalWrite(board::LED.r, LOW);
  pinMode(board::LED.g, INPUT);
  digitalWrite(board::LED.g, LOW);
  pinMode(board::LED.b, INPUT);
  digitalWrite(board::LED.b, LOW);

  // Indicate that the LED I/O is no longer initialized.
  isActive_ = false;
}

void Led::rgb(float red, float green, float blue)
{
  R(red);
  G(green);
  B(blue);
}

void Led::R(float red)
{
  r_ = platypus::clip(red, 0.0f, 1.0f);

  if (isActive_)
    digitalWrite(board::LED.r, !r_);
}

float Led::R() const
{
  return r_;
}

void Led::G(float green)
{
  g_ = platypus::clip(green, 0.0f, 1.0f);;

  if (isActive_)
    digitalWrite(board::LED.g, !g_);
}

float Led::G() const
{
  return g_;
}

void Led::B(float blue)
{
  b_ = platypus::clip(blue, 0.0f, 1.0f);;

  if (isActive_)
    digitalWrite(board::LED.b, !b_);
}

float Led::B() const
{
  return b_;
}
