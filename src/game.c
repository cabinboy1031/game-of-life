#include "gol/game.h"
#include <stdlib.h>

int cell_get_num_neighbors(game_s*, int, int);
bool is_cell_alive(game_s*, int, int, int);

game_s game_new(){
    game_s game = (game_s){
        .width = GAME_WIDTH,
        .height = GAME_HEIGHT,
        .screen_board = calloc(GAME_WIDTH * GAME_HEIGHT, sizeof(bool)),
        .update_board = calloc(GAME_WIDTH * GAME_HEIGHT, sizeof(bool)),
        .paused = true,
        .handle_edges = EDGE_IS_LOOP,
    };

    return game;
}

void game_delete(game_s* game){
    free(game->screen_board);
    free(game->update_board);
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
            game->update_board[game_cell_index(game, x, y)] = is_cell_alive(game, x, y, alive);
        }
    }
    game_board_swap(game);
}

int cell_get_num_neighbors(game_s* game, int x, int y){
    int alive = 0;

    alive += game_get_cell(game, x - 1, y - 1) ? 1 : 0;
    alive += game_get_cell(game, x - 1, y    ) ? 1 : 0;
    alive += game_get_cell(game, x - 1, y + 1) ? 1 : 0;

    alive += game_get_cell(game, x    , y - 1) ? 1 : 0;
    alive += game_get_cell(game, x    , y + 1) ? 1 : 0;

    alive += game_get_cell(game, x + 1, y - 1) ? 1 : 0;
    alive += game_get_cell(game, x + 1, y    ) ? 1 : 0;
    alive += game_get_cell(game, x + 1, y + 1) ? 1 : 0;

    return alive;
}

bool is_cell_alive(game_s* game, int x, int y, int alive){
    int cell_index = game_cell_index(game, x, y);
    bool cell = game->screen_board[cell_index];
    if(cell && (alive == 2 || alive == 3)){
        return true;
    } 
    if(!cell && alive == 3){
        return true;
    } 
    return false;
}

int game_cell_index(game_s* game, int x, int y){
    return (x * GAME_WIDTH) + y;
}

bool game_get_cell(game_s* game, int x, int y){
    if(x < 0 || y < 0 || x >= game->width || y >= game->height){
        return game_handle_edge(game, x, y);
    }
    return game->screen_board[game_cell_index(game, x, y)];
}

bool game_handle_edge(game_s* game, int x, int y){
    if( game->handle_edges == EDGE_IS_WALL) return false;
    if( game->handle_edges == EDGE_IS_LOOP) return game->screen_board[game_cell_index(game, x % game->width, y % game->height)];
    return false; // default to wall behavior if wrongly defined
}
