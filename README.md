# Arduino library for HC-SR04 ultrasonic distance sensor.

HC-SR04 is an ultrasonic sensor that measures distances from 2 to 400cm.

![HC-SR04](/hcsr04.jpg)

This is a simple library for it!

## Usage
Sensor is initialized by creating instance of class UltraSonicDistanceSensor and providing trigger and echo pins.
```c
UltraSonicDistanceSensor sensor(triggerPin, echoPin);
```

Then, to measure the distance, you just call `measureDistanceCm()`, which will return distance in centimeters (double). If distance is larger than 400cm, it will return negative value.

The calculation assumes a temperature of around 20°C. For improved accuracy you may also provide a temperature yourself, either an average for your location or directly measured from another sensor. The call for a temperature of 3.5°C would as such look like this: `measureDistanceCm(3.5)`.

## Example

In this simple example, we need to connect sensors pins like this:

- vcc to 5V
- trig to digital pin 13
- echo to digital pin 12
- gnd to gnd

```c
#include <HCSR04.h>

// Initialize sensor that uses digital pins 13 and 12.
int triggerPin = 13;
int echoPin = 12;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    double distance = distanceSensor.measureDistanceCm();
    Serial.println(distance);
    delay(500);
}
```
