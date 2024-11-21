#include "game_state.h"
#include "lcd.h"
#include "led.h"
#include "button.h"

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(1));
  buttons_init();
  leds_init();
  lcd_init();
  set_game_state(STARTING_STATE);
}

void loop()
{
  switch (game_state)
  {
    case STARTING_STATE:
      starting_state();
      break;
    case PLAYING_STATE:
      playing_state();
      break;
    case WINNING_STATE:
      winning_state();
      break;
    case LOSING_STATE:
      losing_state();
      break;
    case SLEEP_STATE:
      break;
  }
}