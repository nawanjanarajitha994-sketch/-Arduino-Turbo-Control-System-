#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define RELAY_PIN 8
#define RPM_SENSOR_PIN 2

Adafruit_BMP280 bmp;

volatile int pulseCount = 0;
unsigned long lastTime = 0;

int rpm = 0;
float pressure = 0;

const int slots = 20;


const int rpmLimit = 1000;
const float pressureLimit = 1150.0;

void countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  pinMode(RPM_SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RPM_SENSOR_PIN), countPulse, FALLING);

  
  if (!bmp.begin(0x76)) {
    if (!bmp.begin(0x77)) {
      Serial.println("BMP280 not found!");
      while (1);
    }
  }

  Serial.println("System Started...");
}

void loop() {

  //  Calculate RPM every 1 second
  if (millis() - lastTime >= 1000) {
    rpm = (pulseCount * 60) / slots;
    pulseCount = 0;
    lastTime = millis();
  }

  //  Read pressure (Pa → hPa)
  pressure = bmp.readPressure() / 100.0;

  //  Serial output
  Serial.print("RPM: ");
  Serial.print(rpm);
  Serial.print(" | Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa | Relay: ");

  //  LOGIC
  if (rpm > rpmLimit && pressure < pressureLimit) {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("OFF");
  }

  delay(200);
}