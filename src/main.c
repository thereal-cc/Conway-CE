#include "game.h"

int main() 
{
    game_t game;
    kb_key_t key;

    init_game(&game);
    gfx_Begin();
    gfx_SetDrawBuffer();

    // Set Up Text
    gfx_SetTextScale(1, 1);
    gfx_SetTextTransparentColor(0);
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(0xFF);

    while (game.state != QUIT)
    {
        // Keyboard State
        kb_Scan();
        
        if (kb_IsDown(kb_KeyDel)) {
            game.state = QUIT;
            break;
        } else if (kb_IsDown(kb_KeyAlpha)) {
            game.state = (game.state == PLACE) ? RUN : PLACE;
        }

        // Update
        if (game.state == PLACE) {
            set_initial_state(&game);
        } else {
            update_game(&game);
        }

        // Draw Game
        draw_game(&game);
        delay(100);
    }

    gfx_End();
    
    return 0;
}