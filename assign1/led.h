#ifndef _LED_H_
#define _LED_H_

void leds_init();

void set_led(int index, int value);

void blink_red_led();

void reset_leds();

void set_red_led(int value);
#endif