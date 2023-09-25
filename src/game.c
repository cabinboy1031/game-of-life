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
        .active_cells = qvector(0, sizeof(cell_coord), QVECTOR_THREADSAFE | QVECTOR_RESIZE_DOUBLE),
        .paused = true,
        .handle_edges = EDGE_IS_LOOP,
    };

    return game;
}

void game_delete(game_s* game){
    qvector_free(game->active_cells);
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
    // Old version of update
    /*
    for(int x = 0; x < GAME_WIDTH; x++){
        for(int y = 0; y < GAME_HEIGHT; y++){
            int alive = cell_get_num_neighbors(game, x, y);
            // check if a cell meets the conditions to live
            game->update_board[game_cell_index(game, x, y)] = is_cell_alive(game, x, y, alive);
        }
    }
    */
    // Hopefully optimized version of update
    for(int i = 0; i < qvector_size(game->active_cells); i++){
        cell_coord *coord = qvector_getat(game->active_cells, i, false);
        int alive_neighbors = cell_get_num_neighbors(game,
                                           coord->x,
                                           coord->y);

        // check if a cell meets the conditions to live
        bool cell_alive = is_cell_alive(game,
                            coord->x,
                            coord->y,
                            alive_neighbors);

        game->update_board[game_cell_index(game,
                                           coord->x,
                                           coord->y)] = cell_alive;

        if(cell_alive){
            game_set_active_with_neighbors(game, coord->x, coord->y);
        }
    }

    // Check if any active cells do not need to be updated anymore
    for(int i = 0; i < qvector_size(game->active_cells); i++){
        cell_coord *coord = qvector_getat(game->active_cells, i, false);
        int alive_neighbors = cell_get_num_neighbors(game,
                                           coord->x,
                                           coord->y);
        if(!game->update_board[game_cell_index(game, coord->x, coord->y)]
           && alive_neighbors == 0) {
            qvector_removeat(game->active_cells, i);
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

void game_set_active(game_s* game, int x, int y){
    for(int i = 0; i < qvector_size(game->active_cells); i++){
        cell_coord* temp = qvector_getat(game->active_cells, i, false);
        if (temp->x == x && temp->y == y){return;}
    }

    qvector_addlast(game->active_cells, &(cell_coord){x,y});
}

void game_set_active_with_neighbors(game_s* game, int x, int y){
    game_set_active(game, x, y);

    game_set_active(game, x - 1, y - 1);
    game_set_active(game, x - 1, y    );
    game_set_active(game, x - 1, y + 1);
    game_set_active(game, x    , y - 1);
    game_set_active(game, x    , y + 1);
    game_set_active(game, x + 1, y - 1);
    game_set_active(game, x + 1, y    );
    game_set_active(game, x + 1, y + 1);
}
