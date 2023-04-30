#include "gol/game.h"
#include <memory.h>

game_s game_new(){
    game_s game = (game_s){
        .paused = false,
        .handle_edges = EDGE_IS_WALL
    };
    game.update_board = calloc(GAME_WIDTH * GAME_HEIGHT, sizeof(bool));
    game.screen_board = calloc(GAME_WIDTH * GAME_HEIGHT, sizeof(bool));

    return game;
}

void game_board_swap(game_s* game){ 
    bool *temp;
    temp = game->screen_board;
    game->screen_board = game->update_board;
    game->update_board = temp;
}

void game_update(game_s* game){
    for(int x = 0; x < GAME_WIDTH; x++){
        for(int y = 0; y < GAME_HEIGHT; y++){
            int alive = 0;
            int cur_cell = ((x * GAME_WIDTH) + y);
            // check if a cell meets the conditions to live
            alive += game->screen_board[((x - 1) * GAME_WIDTH) + y - 1  ] ? 1 : 0;
            alive += game->screen_board[((x - 1) * GAME_WIDTH) + y      ] ? 1 : 0;
            alive += game->screen_board[((x - 1) * GAME_WIDTH) + y + 1  ] ? 1 : 0;

            alive += game->screen_board[((x) * GAME_WIDTH) + y - 1      ] ? 1 : 0;

            alive += game->screen_board[((x) * GAME_WIDTH) + y + 1      ] ? 1 : 0;

            alive += game->screen_board[((x + 1) * GAME_WIDTH) + y - 1  ] ? 1 : 0;
            alive += game->screen_board[((x + 1) * GAME_WIDTH) + y      ] ? 1 : 0;
            alive += game->screen_board[((x + 1) * GAME_WIDTH) + y + 1  ] ? 1 : 0;
            if(game->screen_board[((x) * GAME_WIDTH) + y] && (alive == 2 || alive == 3)){
                game->update_board[((x) * GAME_WIDTH) + y] = true; 
            } else if(!game->screen_board[((x) * GAME_WIDTH) + y] && alive == 3){
                game->update_board[((x) * GAME_WIDTH) + y] = true;
            } else {
                game->update_board[((x) * GAME_WIDTH) + y] = false;
            }
            
        }
    }
    game_board_swap(game);
}