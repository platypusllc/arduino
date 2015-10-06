/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_MULTIPORT_H
#define PLATYPUS_MULTIPORT_H

#include "Platypus.h"

namespace platypus
{
namespace impl
{

class Controller;

class Led : public ::platypus::Led
{
	void begin();
	void end();

    void rgb(float red, float green, float blue) override;
    void R(float red) override;
    float R() const override;
    void G(float green) override;
    float G() const override;
    void B(float blue) override;
    float B() const override;

protected:
	Led();
	virtual ~Led();

    float r_, g_, b_;
    bool isActive_;

private:
	Led(Led const &) = delete;
	void operator=(Led const &) = delete;

    friend Controller;
};

}
}

#endif // PLATYPUS_MULTIPORT_H