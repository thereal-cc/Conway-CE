#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "keypadc.h"
#include "graphx.h"

enum STATE
{
    QUIT,
    PLACE,
    RUN
};

typedef struct game_t
{
    u8 grid_a[SCREEN_ROWS][SCREEN_COLS];
    u8 grid_b[SCREEN_ROWS][SCREEN_COLS];
    u8 state;
    u8 population;
    u16 generation;
    v2 cursor;
} game_t;

void init_game(game_t *game);
void set_initial_state(game_t *game);
u8 count_neighbors(game_t *game, u8 x, u8 y);
void update_game(game_t *game);
void draw_game(game_t *game);

#endif