#include "model/WasteDisposal.h"

#include "config.h"
#include "devices/Led.h"
#include "devices/TempSensorTPM36.h"
#include "devices/servo_motor_impl.h"
#include "kernel/Logger.h"

WasteDisposal::WasteDisposal() {
}

void WasteDisposal::init() {
    sonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 10000);
    pir = new Pir(PIR_PIN);
    tempSensor = new TempSensorTPM36(TEMP_SENSOR_PIN);
    ledOn = new Led(LED_ON_PIN);
    ledAlarm = new Led(LED_ALARM_PIN);
    doorMotor = new ServoMotorImpl(DOOR_MOTOR_PIN);

    nWashes = 0;
    setAcceptingWaste();
}

void WasteDisposal::openDoor() {
    doorMotor->on();
    doorMotor->setPosition(90);
}

void WasteDisposal::bendDoor() {
    doorMotor->setPosition(180);
}

void WasteDisposal::closeDoor() {
    doorMotor->setPosition(0);
}

bool WasteDisposal::isEmergency() {
    return state == EMERGENCY;
}

void WasteDisposal::setEmergency() {
    state = EMERGENCY;
    ledOn->switchOff();
    ledAlarm->switchOn();
}

bool WasteDisposal::isFull() {
    return state == FULL;
}
void WasteDisposal::setFull() {
    state = FULL;
    ledOn->switchOff();
    ledAlarm->switchOn();
}

bool WasteDisposal::isAcceptingWaste() {
    return state == ACCEPTING_WASTE;
}

void WasteDisposal::setAcceptingWaste() {
    state = ACCEPTING_WASTE;
    ledOn->switchOn();
    ledAlarm->switchOff();
}

bool WasteDisposal::canOpenDoor() {
    return isAcceptingWaste();
}

double WasteDisposal::getCurrentLevel() {
    return sonar->getDistance();
}

double WasteDisposal::getCurrentTemperature() {
    return tempSensor->getTemperature();
}

bool WasteDisposal::isUserDetected() {
    pir->sync();
    return pir->isDetected();
}

void WasteDisposal::prepareToSleep() {
    ledOn->switchOn();
    Logger.log("Going to sleep");
}

void WasteDisposal::resumeFromSleeping() {
    Logger.log("Waking up");
}