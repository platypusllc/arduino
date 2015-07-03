#include "Controller.h"
#include "Board.h"

using platypus::impl::Led;

Led::Led()
  : r_(0), g_(0), b_(0)
{
  pinMode(board::LED.R, OUTPUT);
  digitalWrite(board::LED.R, HIGH);

  pinMode(board::LED.G, OUTPUT);
  digitalWrite(board::LED.G, HIGH);

  pinMode(board::LED.B, OUTPUT);
  digitalWrite(board::LED.B, HIGH);
}

Led::~Led()
{
  pinMode(board::LED.R, INPUT);
  pinMode(board::LED.G, INPUT);
  pinMode(board::LED.B, INPUT);
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
  digitalWrite(board::LED.R, !r_);
}

int Led::R()
{
  return r_;
}

void Led::G(int green)
{
  g_ = green;
  digitalWrite(board::LED.G, !g_);
}

int Led::G()
{
  return g_;
}

void Led::B(int blue)
{
  b_ = blue;
  digitalWrite(board::LED.B, !b_);
}

int Led::B()
{
  return b_;
}
