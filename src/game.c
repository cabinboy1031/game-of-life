#include "gol/game.h"
#include <stdlib.h>

int cell_get_num_neighbors(game_s*, int, int);
bool is_cell_alive(game_s*, int, int, int);

game_s game_new(){
    game_s game = (game_s){
        .paused = true,
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
            int alive = cell_get_num_neighbors(game, x, y);
            // check if a cell meets the conditions to live
            game->update_board[(x) * GAME_WIDTH + y] = is_cell_alive(game, x, y, alive);
        }
    }
    game_board_swap(game);
}

int cell_get_num_neighbors(game_s* game, int x, int y){
    int alive = 0;

    alive += game->screen_board[((x - 1) * GAME_WIDTH) + y - 1  ] ? 1 : 0;
    alive += game->screen_board[((x - 1) * GAME_WIDTH) + y      ] ? 1 : 0;
    alive += game->screen_board[((x - 1) * GAME_WIDTH) + y + 1  ] ? 1 : 0;

    alive += game->screen_board[((x    ) * GAME_WIDTH) + y - 1      ] ? 1 : 0;
    alive += game->screen_board[((x    ) * GAME_WIDTH) + y + 1      ] ? 1 : 0;

    alive += game->screen_board[((x + 1) * GAME_WIDTH) + y - 1  ] ? 1 : 0;
    alive += game->screen_board[((x + 1) * GAME_WIDTH) + y      ] ? 1 : 0;
    alive += game->screen_board[((x + 1) * GAME_WIDTH) + y + 1  ] ? 1 : 0;
    
    return alive;
}

bool is_cell_alive(game_s* game, int x, int y, int alive){
    if(game->screen_board[((x) * GAME_WIDTH) + y] && (alive == 2 || alive == 3)){
        return true;
    } 
    if(!game->screen_board[((x) * GAME_WIDTH) + y] && alive == 3){
        return true;
    } 
    return false;
}