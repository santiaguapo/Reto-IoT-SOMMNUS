#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

void setup() {

  Serial.begin(115200);
  Wire.begin();

  Serial.println("MAX30102 SENSOR TEST");

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("Sensor not detected!");
    while (1);
  }

  particleSensor.setup(
    60,  // LED brightness
    4,   // Sample average
    2,   // Red + IR mode
    100, // Sample rate
    411, // Pulse width
    4096 // ADC range
  );

  Serial.println("Sensor initialized.");
  Serial.println("Place your finger on the sensor.");
}

void loop() {

  particleSensor.check();

  while (particleSensor.available()) {

    uint32_t red = particleSensor.getRed();
    uint32_t ir = particleSensor.getIR();

    Serial.print("RED: ");
    Serial.print(red);

    Serial.print(" | IR: ");
    Serial.println(ir);

    particleSensor.nextSample();
  }
}