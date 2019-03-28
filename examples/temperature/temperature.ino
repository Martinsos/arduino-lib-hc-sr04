#include <HCSR04.h>

//This example uses a DS18B20 1Wire Temperature sensor
//Of course you can use something else like DHT22, LM35 or whatever you have lying around.
#include <OneWire.h>
#include <DallasTemperature.h>

UltraSonicDistanceSensor distanceSensor(13, 12);  // Initialize sensor that uses digital pins 13 and 12.
OneWire oneWire(11);
DallasTemperature sens_temperature(&oneWire);

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 1 second, do a measurement using the sensor and print the distance in centimeters.
    sens_temperature.requestTemperatures();
    float temperature = sens_temperature.getTempCByIndex(0);
    double distance = distanceSensor.measureDistanceCm(temperature);

    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.print(F("°C - Distance: "));
    Serial.print(distance);
    Serial.println(F("cm"));
    delay(1000);
}
