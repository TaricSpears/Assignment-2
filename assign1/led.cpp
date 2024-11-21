#include "led.h"

#include "config.h"
#include "Arduino.h"

int led_pin[]{LED_PIN1, LED_PIN2, LED_PIN3, LED_PIN4};

void leds_init() {
    for (int i = 0; i < N; i++) {
        pinMode(led_pin[i], OUTPUT);
    }
    pinMode(LED_RED_PIN, OUTPUT);
}

void set_led(int index, int value) {
    digitalWrite(led_pin[index], value);
}

void set_red_led(int value) {
    digitalWrite(LED_RED_PIN, value);
}

void reset_leds() {
    for (int i = 0; i < N; i++) {
        set_led(i, LOW);
    }
}

void blink_red_led() {
    static int current_intensity = 0;
    static int delta_intensity = 5;
    current_intensity += delta_intensity;
    if (current_intensity == 0 || current_intensity == 255) {
        delta_intensity = -delta_intensity;
    }
    analogWrite(LED_RED_PIN, current_intensity);
    delay(15);
}