#include <raylib.h>

#define GAME_WIDTH 1024
#define GAME_HEIGHT 1024
#define EDGE_IS_WALL 'w'
#define EDGE_IS_LOOP 'l'

typedef struct game_s{
    bool* screen_board; // The board currently being displayed and read from
    bool* update_board; // The board currently being updated using the currently displayed board
    bool paused; // states whether the board SHOULD be paused or not
    char handle_edges; // decides the function used to handle walls.
} game_s;

/**
 * void -> game_s
 * initializes a default game state
 */
game_s game_new();

/**
 * game_s* -> void
 * swaps the update and screen board, changing their roles as well
 */
void game_board_swap(game_s* game);

/**
 *
 
 */
