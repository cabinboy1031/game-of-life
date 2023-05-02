#include <raylib.h>

#define GAME_WIDTH 2048
#define GAME_HEIGHT 2048
#define EDGE_IS_WALL 'w'
#define EDGE_IS_LOOP 'l'

typedef struct game_s{
    bool* screen_board; // The board currently being displayed and read from
    bool* update_board; // The board currently being updated using the currently displayed board
    int width, height;
    bool paused; // states whether the board SHOULD be paused or not
    char handle_edges; // decides the function used to handle walls.
} game_s;

/**
 * void -> game_s
 * initializes a default game state
 */
game_s game_new();

void game_delete(game_s*);
/**
 * game_s* -> void
 * swaps the update and screen board, changing their roles as well
 */
void game_board_swap(game_s* game);

/**
 *
 */
void game_update(game_s* game);

bool game_get_cell(game_s*, int, int);
bool game_handle_edge(game_s*, int,int);
/** gets the index based on the size of the board*/
int game_cell_index(game_s*, int, int);