#include <qlibc/qlibc.h>
#include <engine/interface/input.h>

#define GAME_WIDTH 1024
#define GAME_HEIGHT 1024
#define EDGE_IS_WALL 'w'
#define EDGE_IS_LOOP 'l'

typedef struct game_s{
    bool* screen_board; // The board currently being displayed and read from
    bool* update_board; // The board currently being updated using the currently displayed board
    qvector_t* active_cells; // An actively managed list of cells that might update in the future
    int width, height;
    bool paused; // states whether the board SHOULD be paused or not
    char handle_edges; // decides the function used to handle walls.

    v_input_component_s* input;
} game_s;

typedef struct cell_coord{
    int x;
    int y;
} cell_coord;


/**
 * void -> game_s
 * initializes a default game state
 */
game_s game_new();

/**
 * game_s* -> void
 * basic game deconstructor
 */
void game_delete(game_s*);

/**
 * game_s* -> void
 * swaps the update and screen board, changing their roles as well
 */
void game_board_swap(game_s* game);

/**
 * game_s* -> void
 * progresses the game by 1 frame
 */
void game_update(game_s* game);

bool game_get_cell(game_s*, int, int);
bool game_handle_edge(game_s*, int,int);
/** gets the index based on the size of the board*/
int game_cell_index(game_s*, int, int);

/**
 * game_s* -> void
 * Adds the cell to the active state to be monitored for changes
 * */
void game_set_active(game_s*, int, int);

/**
 * game_s* -> void
 * Adds the cell to the active state to be monitored for changes
 * Also adds neighboring cells to active state
 * */
void game_set_active_with_neighbors(game_s* ,int, int);
