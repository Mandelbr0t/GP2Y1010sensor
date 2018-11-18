#include "GP2Y1010sensor.h"

GP2Y1010sensor::GP2Y1010sensor() {
}

void GP2Y1010sensor::init(int LEDpin, int sensorPin, float K, int nAvg) {
  _LEDpin = LEDpin;
  _sensorPin = sensorPin;
  _nAvg = nAvg;
  _v0c = 0.6;
  _k = K;
  pinMode(_LEDpin, OUTPUT);
}


void GP2Y1010sensor::read(float* density, float* mvolt) {
  _v0total = 0;
  _v0count = 0;
  for (int _v0count = 0; _v0count < _nAvg; _v0count++)
  {
    digitalWrite(_LEDpin, LOW);
    delayMicroseconds(280);

    rawData = analogRead(_sensorPin);

    digitalWrite(_LEDpin, HIGH);
    delayMicroseconds(9620);
    _v0total += rawData;
    
  }
  
  // average volt value of _nAvg measurements
  val = 1.0 * _v0total / _nAvg;
  
  // output voltage (precision: 1/1024):
  val = val / 1024.0 * 5.0;
  _dV = val - _v0c;
  
  // if lower voltage than _v0c detected -> set val as new
  if (_dV < 0)
  {
    _dV = 0;
    _v0c = val;
  }
  
  // convert to dust density (ug/m3) and return mvolt value
  
  *mvolt = val;
  dens = _dV / _k * 100.0;
  *density = dens;
}

