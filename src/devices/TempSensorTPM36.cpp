#include "TempSensorTPM36.h"

#include "Arduino.h"

#define VCC ((float)5)

TempSensorTPM36::TempSensorTPM36(int p) : pin(p) {
}

float TempSensorTPM36::getTemperature() {
    int value = analogRead(pin);
    float valueInVolt = value * VCC / 1023 / 4;
    float valueInCelsius = valueInVolt / 0.01;
    return valueInCelsius;
}
