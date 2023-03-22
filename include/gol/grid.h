#include <raylib.h>
#include <stddef.h>
#include <stdint.h>

// interp. a square grid to translate screen space to a scalable tile space
typedef struct grid_s {
    uint32_t size; // Size of a grid tile in screen space
    Vector2 offset; // Offset of grid in screen space
} grid_s;
/*
const grid_s G1 = {10, (Vector2) {50, 0}};
const grid_s G2 = {16, (Vector2) {0, 200}};
const grid_s G3 = {16, (Vector2) {-30, 0}};

void fnForGrid(grid_s g){
    assert(g.size);
    assert(g.offset.x);
    assert(g.offset.y);
}*/

typedef struct limited_grid_s {
    grid_s grid; // fully defined grid dimensions
    size_t row;  // maximum rows in the grid(max y)
    size_t col;  // maximum columns in the grid(max x)
} limited_grid_s;
/*
const limited_grid_s LG1 = {
    {10, (Vector2) {50, 0}}, 20, 10
    };

void fnForLimitedGrid(limited_grid_s lg){
    for(size_t x = 0; x < lg.row; x++){
        for(size_t y = 0; y < lg.col; y++){
            assert(lg.grid);
            assert(lg.row);
            assert(lg.col);
            assert(x);
            assert(y);
        }
    }
}*/

/**
 * int, Vector2 -> grid_s
 * creates a valid grid, if input is invalid, returns a size of 1 and offset of (0,0) 
 */
grid_s grid_create(int size, Vector2 offset);

/**
 * grid_s, Vector2 -> Vector2 
 * converts a grid coordinate to a screen coordinate
 */
Vector2 grid_to_screen(grid_s grid, Vector2 gc) { return (Vector2){0,0};}

/**
 * grid_s, Vector2 -> Vector2 
 * converts a screen coordinate to its grid coordinate floor
 */
Vector2 screen_to_grid(grid_s grid, Vector2 sc) { return (Vector2){0,0};}

/**
 * grid_s, Vector2 -> Vector2 
 * converts a screen coordinate to its exact grid coordinate
 */
Vector2 screen_to_grid_exact(grid_s grid, Vector2 sc) { return (Vector2){0,0};}