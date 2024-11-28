#include "model/WasteDisposal.h"

#include "config.h"
#include "devices/Led.h"
#include "devices/LightSensorImpl.h"
#include "devices/TempSensorLM35.h"
#include "devices/servo_motor_impl.h"
#include "kernel/Logger.h"

WasteDisposal::WasteDisposal() {
}

void WasteDisposal::init() {
    sonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 10000);
    pir = new Pir(PIR_PIN);
    tempSensor = new TempSensorLM35(TEMP_SENSOR_PIN);
    ledOn = new Led(LED_ON_PIN);
    ledAlarm = new Led(LED_ALARM_PIN);
    doorMotor = new ServoMotorImpl(DOOR_MOTOR_PIN);

    Logger.log("Calibrating sensors in plant...");
    pir->calibrate();

    nWashes = 0;
    state = IDLE;
}

void WasteDisposal::openDoor() {
    doorMotor->on();
    doorMotor->setPosition(90);
}

void WasteDisposal::closeDoor() {
    doorMotor->setPosition(0);
}

bool WasteDisposal::isEmergency() {
    return state == EMERGENCY;
}