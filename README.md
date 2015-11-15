Platypus Arduino Library
========================
[![Build Status](https://travis-ci.org/platypusllc/arduino.svg)](https://travis-ci.org/platypusllc/arduino)

> :warning: This library is still in development.  Please do not use this yet for any active projects.

The Platypus Arduino Library provides a standard library for interacting with Platypus Arduino-based hardware, such as the Platypus Controller.

### Installation ###

Download [this repository](https://github.com/PlatypusLLC/Arduino/archive/master.zip) and extract it into a folder named `Platypus` in the `libraries` sub-directory of your sketchbook directory.  You may need to create the `libraries` directory if this is your first library.

After restarting the Arduino IDE, you should now see **Platypus** under **Sketch > Import > Library**  directory inside of the libraries sub-directory of your sketchbook directory.

For *Arduino IDE <=1.6.4*, C++11 needs to be enabled for this library to work. To enable this, find and edit the `/arduino/hardware/sam/x.x.x/platform.txt` file on your Arduino IDE installation.  Add the `-std=c++11` to the end of the `compiler.cpp.flags=[...]` line.

> :warning: TODO: Add dependencies on `Scheduler` and `USBHost` libraries, and add `#if defined()` checks to print useful error messages.

### Usage ###

You can use this library to configure your own Platypus Controller firmware.  Take a look at the [examples](examples) directory for some basic configurations.

### Resources ###

Adafruit offers a more detailed guide to Arduino library installation at:
* http://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use
