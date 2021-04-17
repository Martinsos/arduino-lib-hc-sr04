/*
  HCSR04 - Library for arduino, for HC-SR04 ultrasonic distance sensor.
  Created by Martin Sosic, June 11, 2016.
*/

#ifndef HCSR04_H
#define HCSR04_H

#include "Arduino.h"

class UltraSonicDistanceSensor {
 public:
    /**
     * @param triggerPin  Digital pin that is used for controlling sensor (output).
     * @param echoPin  Digital pin that is used to get information from sensor (input).
     * @param maxDistanceCm  Maximum distance sensor can measure, defaults to 4m for HC-SR04.
     */
    UltraSonicDistanceSensor(int triggerPin, int echoPin, int maxDistanceCm = 400);

    /**
     * Defines an absolute timeout value for all measurements, overrides automatic calculation
     * based on max distance.
     * @param timeoutMicroSec  Set absolute measurement timeout.
                               0 to get back to automatic calculation.
     */
    void setTimeoutMicroSec(uint32_t timeoutMicroSec);

    /**
     * Measures distance by sending ultrasonic waves and measuring time it takes them
     * to return.
     * @returns Distance in centimeters, or negative value if distance is greater than 400cm.
     */
    double measureDistanceCm();

    /**
     * Measures distance by sending ultrasonic waves and measuring time it takes them
     * to return.
     * @param temperature  Temperature in degrees celsius
     * @returns Distance in centimeters, or negative value if distance is greater than 400cm.
     */
    double measureDistanceCm(float temperature);
 private:
    int triggerPin, echoPin, maxDistanceCm;
    uint32_t timeoutMicroSec;
};

#endif // HCSR04_H
