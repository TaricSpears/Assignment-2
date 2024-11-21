#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#define STARTING_STATE 0
#define PLAYING_STATE 1
#define WINNING_STATE 2
#define LOSING_STATE 3
#define SLEEP_STATE 4

extern int game_state;

void generate_game_number();

void starting_state();

void playing_state();

void winning_state();

void losing_state();

void set_game_state(int state);

#endif