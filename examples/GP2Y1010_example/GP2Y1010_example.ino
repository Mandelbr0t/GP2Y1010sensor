#include <printf.h>
#include <GP2Y1010sensor.h>

// Arduino pin numbers.
const int sharpLEDPin = 12;   // Arduino digital pin 7 connect to sensor LED.
const int sharpVoPin = A0;   // Arduino analog pin 5 connect to sensor Vo.
// Set the typical output voltage in Volts when there is zero dust. 
static float Voc = 0.6;
// Use the typical sensitivity in units of V per 100ug/m3.
const float K = 0.5;
// Number of last N raw voltage readings
#define N 200

GP2Y1010sensor GP2;

void printFValue(String text, float value, String units, bool isLast = false) {
  Serial.print(text);
  Serial.print("=");
  Serial.print(value);
  Serial.print(units);
  if (!isLast) {
    Serial.print(", ");
  }
}

void setup() {
  Serial.begin(9600);
  GP2.init(sharpLEDPin, sharpVoPin, K, N);
  Serial.println("Initialized");
  
}

void loop() {
  float mvolt;
  float density;
  GP2.read(&density, &mvolt);
  printFValue("Vo", mvolt * 1000, "mV");
  printFValue("Dust Density", density, "ug/m3", true);
  Serial.println("");
}
