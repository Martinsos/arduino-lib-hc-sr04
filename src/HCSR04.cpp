/*
  HCSR04 - Library for arduino, for HC-SR04 ultrasonic distance sensor.
  Created by Martin Sosic, June 11, 2016.
*/

#include "Arduino.h"
#include "HCSR04.h"

UltraSonicDistanceSensor::UltraSonicDistanceSensor(
        byte triggerPin, byte echoPin, unsigned short maxDistanceCm, unsigned long maxTimeoutMicroSec) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    this->maxDistanceCm = maxDistanceCm;
    this->maxTimeoutMicroSec = maxTimeoutMicroSec;
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float UltraSonicDistanceSensor::measureDistanceCm() {
    //Using the approximate formula 19.307°C results in roughly 343m/s which is the commonly used value for air.
    return measureDistanceCm(19.307);
}

float UltraSonicDistanceSensor::measureDistanceCm(float temperature) {
    unsigned long maxDistanceDurationMicroSec;

    // Make sure that trigger pin is LOW.
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    float speedOfSoundInCmPerMicroSec = 0.03313 + 0.0000606 * temperature; // Cair ≈ (331.3 + 0.606 ⋅ ϑ) m/s

    // Compute max delay based on max distance with 25% margin in microseconds
    maxDistanceDurationMicroSec = 2.5 * maxDistanceCm / speedOfSoundInCmPerMicroSec;
    if (maxTimeoutMicroSec > 0) {
    	maxDistanceDurationMicroSec = min(maxDistanceDurationMicroSec, maxTimeoutMicroSec);
    }

    // Measure the length of echo signal, which is equal to the time needed for sound to go there and back.
    unsigned long durationMicroSec = pulseIn(echoPin, HIGH, maxDistanceDurationMicroSec); // can't measure beyond max distance

    float distanceCm = durationMicroSec / 2.0 * speedOfSoundInCmPerMicroSec;
    if (distanceCm == 0 || distanceCm > maxDistanceCm) {
        return -1.0 ;
    } else {
        return distanceCm;
    }
}