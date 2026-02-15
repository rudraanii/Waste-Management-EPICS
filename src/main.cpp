#include <Arduino.h>
#include <HCSR04.h>

// Member 1: Sensor Logic
const byte triggerPin = 5;
const byte echoPin = 18;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT); // Built-in LED on ESP32
}

void loop() {
    float distance = distanceSensor.measureDistanceCm();

    Serial.print("Current Trash Level: ");
    Serial.print(distance);
    Serial.println(" cm");

    // If something is closer than 10cm, turn on the indicator LED
    if (distance > 0 && distance < 10) {
        digitalWrite(2, HIGH);
    } else {
        digitalWrite(2, LOW);
    }

    delay(500); 
}