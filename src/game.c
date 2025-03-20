#include "game.h"

void init_game(game_t *game)
{
    memset(game, 0, sizeof(game_t));
    game->state = PLACE;
    game->cursor.x = 1;
    game->cursor.y = 1;
    game->population = 0;
    game->generation = 0;
}

void set_initial_state(game_t *game)
{
    if (kb_IsDown(kb_KeyUp) && game->cursor.y > 0) game->cursor.y--;
    else if (kb_IsDown(kb_KeyDown) && game->cursor.y < SCREEN_ROWS - 1) game->cursor.y++;
    else if (kb_IsDown(kb_KeyLeft) && game->cursor.x > 0) game->cursor.x--;
    else if (kb_IsDown(kb_KeyRight) && game->cursor.x < SCREEN_COLS - 1) game->cursor.x++;
    else if (kb_IsDown(kb_KeyEnter)) game->grid_a[game->cursor.y][game->cursor.x] ^= 1;
    else if (kb_IsDown(kb_KeyClear)) memset(game->grid_a, 0, sizeof(game->grid_a));
}

u8 count_neighbors(game_t *game, u8 x, u8 y)
{
    u8 count = 0;

    for (i8 dy = -1; dy <= 1; dy++) {
        for (i8 dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;

            i8 nx = x + dx;
            i8 ny = y + dy;

            if (nx >= 0 && nx < SCREEN_COLS && ny >= 0 && ny < SCREEN_ROWS) {
                if (game->grid_a[ny][nx]) count++; // Corrected indexing
            }
        }
    }
    return count;
}

void update_game(game_t *game)
{
    u8 new_population = 0;

    for (u8 j = 0; j < SCREEN_ROWS; j++) {
        for (u8 i = 0; i < SCREEN_COLS; i++) {
            u8 neighbors = count_neighbors(game, i, j);

            if (game->grid_a[j][i]) game->grid_b[j][i] = (neighbors == 2 || neighbors == 3);
            else game->grid_b[j][i] = (neighbors == 3);

            if (game->grid_b[j][i]) new_population++;
        }
    }

    memcpy(game->grid_a, game->grid_b, sizeof(game->grid_b));
    game->generation++;
    game->population = new_population;
}

void draw_game(game_t *game)
{
    gfx_ZeroScreen();

    // Draw Board
    gfx_SetColor(0xFF);
    for (u8 j = 0; j < SCREEN_ROWS; j++) {
        for (u8 i = 0; i < SCREEN_COLS; i++) {
            gfx_Rectangle(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
    }

    // Draw Live Cells
    gfx_SetColor(0x33);
    for (u8 j = 0; j < SCREEN_ROWS; j++) {
        for (u8 i = 0; i < SCREEN_COLS; i++) {
            if (game->grid_a[j][i]) {
                gfx_FillRectangle(i * TILE_SIZE + 1, j * TILE_SIZE + 1, TILE_SIZE - 1, TILE_SIZE - 1);
            }
        }
    }
    
    // Draw Cursor
    if (game->state == PLACE){
        gfx_SetColor(0xC0);
        gfx_Rectangle(game->cursor.x * TILE_SIZE, game->cursor.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }

    // Draw Text
    gfx_SetTextXY(TILE_SIZE, GFX_LCD_HEIGHT - TILE_SIZE); 
    gfx_PrintString("Generation: ");
    gfx_PrintUInt(game->generation, 2); 

    gfx_SetTextXY(GFX_LCD_WIDTH - (TILE_SIZE * 6), GFX_LCD_HEIGHT - TILE_SIZE); 
    gfx_PrintString("Population: ");
    gfx_PrintUInt(game->population, 2); 

    gfx_SwapDraw();
}
