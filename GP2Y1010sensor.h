#include <Arduino.h>


class GP2Y1010sensor {
  public:
    GP2Y1010sensor();
    void init(int LEDpin, int sensorPin, float K, int nAvg);
    void read(float* density, float* mvolt);
    float val;
    float dens;
    int rawData;

  private:
    int _LEDpin;
    int _sensorPin;
    float _nAvg;
    long _v0total;
    int _v0count;
    float _v0c;
    float _k;
    float _dV;
};
