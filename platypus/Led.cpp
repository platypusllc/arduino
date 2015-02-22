#include "Controller.h"
#include "Board.h"

class LedImpl : public platypus::Led {
private:
	int r_, g_, b_;
};

LedImpl::LedImpl()
  : r_(0), g_(0), b_(0)
{
  pinMode(board::LED.R, OUTPUT);
  digitalWrite(board::LED.R, HIGH);

  pinMode(board::LED.G, OUTPUT);
  digitalWrite(board::LED.G, HIGH);

  pinMode(board::LED.B, OUTPUT);
  digitalWrite(board::LED.B, HIGH);
}

LedImpl::~LedImpl()
{
  pinMode(board::LED.R, INPUT);
  pinMode(board::LED.G, INPUT);
  pinMode(board::LED.B, INPUT);
}

void LedImpl::set(int red, int green, int blue)
{
  R(red);
  G(green);
  B(blue);
}

void LedImpl::R(int red)
{
  r_ = red;
  digitalWrite(board::LED.R, !r_);
}

int LedImpl::R()
{
  return r_;
}

void LedImpl::G(int green)
{
  g_ = green;
  digitalWrite(board::LED.G, !g_);
}

int LedImpl::G()
{
  return g_;
}

void LedImpl::B(int blue)
{
  b_ = blue;
  digitalWrite(board::LED.B, !b_);
}

int LedImpl::B()
{
  return b_;
}