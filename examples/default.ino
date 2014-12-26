/**
 * Example firmware that starts up the Platypus Controller with default settings.
 *
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#include <Platypus.h>

// Create an instance of the Platypus Controller.
platypus::Controller controller;

// Set up the devices that we want to use on the DrivePort.
// For this example, we configure two servos.
platypus::ServoMotor motor0;
platypus::ServoMotor motor1;
platypus::DrivePort motors[2] = { motor0, motor1 }; 

// Set up the devices that we want to use on the MultiPorts.
// For this example, we configure four analog sensors.
int sampleRate = 100; // Sampling rate in Hz

// Analog sensors return (voltage - offset) * scale.
float offset = 2.5;
float scale = 1.0;

platypus::AnalogSensor sensor0(sampleRate, offset, scale);
platypus::AnalogSensor sensor1(sampleRate, offset, scale);
platypus::AnalogSensor sensor2(sampleRate, offset, scale);
platypus::AnalogSensor sensor3(sampleRate, offset, scale);
platypus::DrivePort sensors[4] = { sensor0, sensor1, sensor2, sensor3 };

// Create some references that will hold stream descriptors for JSON commands
// and the text debugging console.
Stream command;
Stream console;

void setup()
{
    // Initialize the Platypus Controller.
    controller.begin();

    // You can configure drive ports individually:
    controller.setDrivePort(0, motor0);
    controller.setDrivePort(1, motor1);
    
    // Or you can set them all at once:
    controller.setDrivePorts(motors);

    // You can configure multi ports individually:
    controller.setMultiPort(0, sensor0);
    controller.setMultiPort(1, sensor1);
    controller.setMultiPort(2, sensor2);
    controller.setMultiPort(3, sensor3);

    // Or you can set them all at once:
    controller.setMultiPorts(sensors);

    // Get a reference to the JSON command/response stream.
    command = controller.command();

    // Get a reference to the string debugging stream.
    console = controller.console();
}

void loop()
{
    // You don't have to do anything in here, but you can create your own
    // logic such as manipulating LEDs or printing status regularly.
    
    // Blink the LED every second, with the color indicating whether we are
    // connected to Android.
    controller.led.rgb(0,0,0);
    delay(500);
    if (controller.isConnected()) 
    {
        controller.led.rgb(255,0,0);
    }
    else
    {
        controller.led.rgb(0,255,0);
    }
    delay(500);
    
    // Send a JSON status command to Android.
    // All commands must be newline terminated JSON strings.
    printf(command, "{\"status\": \"OK\"}\n");

    // Print the same status to the debugging console.
    printf(console, "STATUS: OK\n");
}