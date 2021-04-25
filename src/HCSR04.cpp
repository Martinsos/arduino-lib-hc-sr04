/*
  HCSR04 - Library for arduino, for HC-SR04 ultrasonic distance sensor.
  Created by Martin Sosic, June 11, 2016.
*/

#include "Arduino.h"
#include "HCSR04.h"

UltraSonicDistanceSensor::UltraSonicDistanceSensor(
        int triggerPin, int echoPin, int maxDistanceCm, uint32_t timeoutMicroSec) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    this->maxDistanceCm = maxDistanceCm;
    this->timeoutMicroSec = 0;
    this->timeoutMicroSec = timeoutMicroSec;
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double UltraSonicDistanceSensor::measureDistanceCm() {
    //Using the approximate formula 19.307°C results in roughly 343m/s which is the commonly used value for air.
    return measureDistanceCm(19.307);
}

double UltraSonicDistanceSensor::measureDistanceCm(float temperature) {
    uint32_t maxDistanceDurationMicroSec;

    // Make sure that trigger pin is LOW.
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    double speedOfSoundInCmPerMicroSec = 0.03313 + 0.0000606 * temperature; // Cair ≈ (331.3 + 0.606 ⋅ ϑ) m/s

    if (timeoutMicroSec > 0) {
        maxDistanceDurationMicroSec = timeoutMicroSec;
    } else {
        // Compute max delay based on max distance with 25% margin in microseconds
        maxDistanceDurationMicroSec = 2.5 * maxDistanceCm / speedOfSoundInCmPerMicroSec;
    }

    // Measure the length of echo signal, which is equal to the time needed for sound to go there and back.
    unsigned long durationMicroSec = pulseIn(echoPin, HIGH, maxDistanceDurationMicroSec); // can't measure beyond max distance

    double distanceCm = durationMicroSec / 2.0 * speedOfSoundInCmPerMicroSec;
    if (distanceCm == 0 || distanceCm > maxDistanceCm) {
        return -1.0 ;
    } else {
        return distanceCm;
    }
}