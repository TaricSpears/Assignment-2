#include "button.h"
#include <EnableInterrupt.h>
#include "config.h"
int button_pin[] {BUT_PIN1, BUT_PIN2, BUT_PIN3, BUT_PIN4};
bool button_state[] {false, false, false, false};


void reset_button_state()
{
  for (int i = 0; i < N; i++)
  {
    noInterrupts();
    button_state[i] = false;
    interrupts();
  }
}

bool get_button_value(int index) {
  bool value;
  noInterrupts();
  value = button_state[index];
  interrupts();
  return value;
}

void button_pressed(int index)
{
  static unsigned long last_interrupt_time[N] = {0};
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time[index] < 200)
    return;
  last_interrupt_time[index] = interrupt_time;
  button_state[index] = !button_state[index];
}

void button_pressed0()
{
  button_pressed(0);
}

void button_pressed1()
{
  button_pressed(1);
}

void button_pressed2()
{
  button_pressed(2);
}

void button_pressed3()
{
  button_pressed(3);
}

void buttons_init()
{
  for (int i = 0; i < N; i++)
  {
    pinMode(button_pin[i], INPUT);
  }
  pinMode(POT_PIN, INPUT);
  enableInterrupt(button_pin[0], button_pressed0, RISING);
  enableInterrupt(button_pin[1], button_pressed1, RISING);
  enableInterrupt(button_pin[2], button_pressed2, RISING);
  enableInterrupt(button_pin[3], button_pressed3, RISING);
}