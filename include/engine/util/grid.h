#pragma once
#include "engine/util/math.h"
#include <stddef.h>
#include <stdint.h>

// interp. a square grid to translate screen space to a scalable tile space
typedef struct grid_s {
    uint32_t size; // Size of a grid tile in screen space
    v_vec2_s offset; // Offset of grid in screen space
} grid_s;
/*
const grid_s G1 = {10, (v_vec2_s) {50, 0}};
const grid_s G2 = {16, (v_vec2_s) {0, 200}};
const grid_s G3 = {16, (v_vec2_s) {-30, 0}};

void fnForGrid(grid_s g){
    assert(g.size);
    assert(g.offset.x);
    assert(g.offset.y);
}
*/

/**
 * int, v_vec2_s -> grid_s
 * creates a valid grid, if input is invalid, returns a size of 1 and offset of (0,0)
 */
grid_s grid_create(int size, v_vec2_s offset);

/**
 * grid_s, vec2 -> vec2
 * converts a grid coordinate to a screen coordinate
 */
v_vec2_s grid_to_screen(grid_s grid, v_vec2_s gc);

/**
 * grid_s, v_vec2_s -> v_vec2_s
 * converts a screen coordinate to its grid coordinate floor
 */
v_vec2_s screen_to_grid(grid_s grid, v_vec2_s sc);

/**
 * grid_s, v_vec2_s -> v_vec2_s
 * converts a screen coordinate to its exact grid coordinate
 */
v_vec2_s screen_to_grid_exact(grid_s grid, v_vec2_s sc);
