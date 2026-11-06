#include <Wire.h>
#include "MAX30105.h"

// Maxim algorithm declaration
void maxim_heart_rate_and_oxygen_saturation(
  uint16_t *irBuffer,
  int32_t bufferLength,
  uint16_t *redBuffer,
  int32_t *spo2,
  int8_t *validSPO2,
  int32_t *heartRate,
  int8_t *validHeartRate
);

MAX30105 particleSensor;

// Configuration
const int SAMPLE_BUFFER_SIZE = 50;
const int NEW_SAMPLES = 25;

const int MIN_SPO2 = 95;
const int MIN_HEART_RATE = 60;
const int MAX_HEART_RATE = 100;

const uint32_t FINGER_THRESHOLD = 50000;

// Smaller sample arrays
uint16_t irBuffer[SAMPLE_BUFFER_SIZE];
uint16_t redBuffer[SAMPLE_BUFFER_SIZE];

// Results
int32_t spo2 = 0;
int8_t validSPO2 = 0;

int32_t heartRate = 0;
int8_t validHeartRate = 0;

void calculateMeasurements() {
  maxim_heart_rate_and_oxygen_saturation(
    irBuffer,
    SAMPLE_BUFFER_SIZE,
    redBuffer,
    &spo2,
    &validSPO2,
    &heartRate,
    &validHeartRate
  );
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("MAX30102 HEALTH MONITOR");

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("ERROR: Sensor not detected!");
    while (1);
  }

  particleSensor.setup(
    60,    // LED brightness
    4,     // Sample averaging
    2,     // Red + IR
    100,   // Sample rate
    411,   // Pulse width
    4096   // ADC range
  );

  Serial.println("Sensor initialized.");
  Serial.println("Place your finger on the sensor.");

  // Initial 50 samples
  for (int i = 0; i < SAMPLE_BUFFER_SIZE; i++) {
    while (!particleSensor.available()) {
      particleSensor.check();
    }

    uint32_t red = particleSensor.getRed();
    uint32_t ir = particleSensor.getIR();

    // Scale readings to fit 16-bit storage
    redBuffer[i] = (uint16_t)(red >> 2);
    irBuffer[i] = (uint16_t)(ir >> 2);

    particleSensor.nextSample();
  }

  calculateMeasurements();
}

void loop() {

  // Shift the newest 25 samples to the beginning
  for (int i = NEW_SAMPLES; i < SAMPLE_BUFFER_SIZE; i++) {
    redBuffer[i - NEW_SAMPLES] = redBuffer[i];
    irBuffer[i - NEW_SAMPLES] = irBuffer[i];
  }

  uint32_t latestIR = 0;

  // Collect 25 new samples
  for (int i = SAMPLE_BUFFER_SIZE - NEW_SAMPLES;
       i < SAMPLE_BUFFER_SIZE;
       i++) {

    while (!particleSensor.available()) {
      particleSensor.check();
    }

    uint32_t red = particleSensor.getRed();
    uint32_t ir = particleSensor.getIR();

    redBuffer[i] = (uint16_t)(red >> 2);
    irBuffer[i] = (uint16_t)(ir >> 2);

    latestIR = ir;

    particleSensor.nextSample();
  }

  // Finger detection
  if (latestIR < FINGER_THRESHOLD) {
    Serial.println("No finger detected.");
    return;
  }

  calculateMeasurements();

  Serial.println();
  Serial.println("----- MEASUREMENTS -----");

  if (validHeartRate && heartRate > 0) {
    Serial.print("Heart Rate: ");
    Serial.print(heartRate);
    Serial.println(" BPM");

    if (heartRate < MIN_HEART_RATE ||
        heartRate > MAX_HEART_RATE) {
      Serial.println("Heart rate outside configured range.");
    }
  } else {
    Serial.println("Heart Rate: Calculating...");
  }

  if (validSPO2 && spo2 > 0 && spo2 <= 100) {
    Serial.print("SpO2: ");
    Serial.print(spo2);
    Serial.println("%");

    if (spo2 < MIN_SPO2) {
      Serial.println("Low SpO2 reading.");
    }
  } else {
    Serial.println("SpO2: Calculating...");
  }

  Serial.println("------------------------");
}