#include "game_state.h"
#include <avr/sleep.h>
#include "Arduino.h"

#include "config.h"
#include "lcd.h"
#include "button.h"
#include "led.h"

int game_state;
int game_number = 0;
unsigned long change_state_time = 0;
int score = 0;
int time = 10000;
int difficulty = 1;
double scaling = 1.15;

void adjust_difficulty()
{
  int potValue = analogRead(POT_PIN);
  difficulty = map(potValue, 0, 1024, 1, 5);
}


void set_game_state(int state)
{
  change_state_time = millis();
  game_state = state;
  switch (state)
  {
    case STARTING_STATE:
      score = 0;
      reset_button_state();
      reset_leds();
      lcd_display_string("Welcome to GMB!", "Press B1 to Start");
      break;
    case PLAYING_STATE:
      if (score == 0)
      {
        adjust_difficulty();
        time = 10000 - difficulty * 1000;
      }else{
        time = time / scaling;
      }
      set_red_led(LOW);
      reset_button_state();
      reset_leds();
      generate_game_number();
      lcd_display_string("Go!", "", game_number);
      break;
    case WINNING_STATE:
      score++;
      lcd_display_string("GOOD!", "Score: ", score);
      break;
    case LOSING_STATE:
      set_red_led(HIGH);
      lcd_display_string("Game Over", "Final Score: ", score);
      break;
    case SLEEP_STATE:
      delay(500);
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      sleep_disable();
      set_game_state(STARTING_STATE);
      break;
  }
}

bool game_won()
{
  return get_button_value(0) * 1 + get_button_value(1) * 2 + get_button_value(2) * 4 + get_button_value(3) * 8 == game_number;
}

void starting_state()
{
  if (get_button_value(3))
  {
    set_game_state(PLAYING_STATE);
    return;
  }
  if (millis() - change_state_time > 10000)
  {
    set_game_state(SLEEP_STATE);
    return;
  }
  blink_red_led();
}

void playing_state()
{
  bool won = game_won();
  for (int i = 0; i < N; i++)
  {
    if (get_button_value(i))
    {
      set_led(i, HIGH);
    }
    else
    {
      set_led(i, LOW);
    }
  }
  if (won)
  {
    set_game_state(WINNING_STATE);
    return;
  }
  if (millis() - change_state_time > time)
  {
    set_game_state(LOSING_STATE);
  }
}

void winning_state()
{
  if (millis() - change_state_time > 3000)
  {
    set_game_state(PLAYING_STATE);
  }
}

void losing_state()
{

  if (millis() - change_state_time > 1000)
  {
    set_red_led(LOW);
  }
  if (millis() - change_state_time > 10000)
  {
    set_game_state(STARTING_STATE);
  }
}

void generate_game_number()
{
  game_number = random(16);
}