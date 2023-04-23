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
