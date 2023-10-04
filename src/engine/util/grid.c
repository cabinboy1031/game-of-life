#include "gol/grid.h"
#include "math.h"

grid_s grid_create(int size, v_vec2_s offset) {
    if(size == 0){
        return (grid_s){1,(v_vec2_s){}};
    } else {
        return (grid_s){size, offset};
    }
}

v_vec2_s grid_to_screen(grid_s grid, v_vec2_s gc) {
    return (v_vec2_s){
        grid.offset.x + (grid.size * gc.x),
        grid.offset.y + (grid.size * gc.y),
        };
    }

v_vec2_s screen_to_grid(grid_s grid, v_vec2_s sc) {
    v_vec2_s result = screen_to_grid_exact(grid, sc);

    return (v_vec2_s){
        floor(result.x),
        floor(result.y)
        };
}

v_vec2_s screen_to_grid_exact(grid_s grid, v_vec2_s sc) {
    return (v_vec2_s){
            (sc.x - grid.offset.x) / grid.size,
            (sc.y - grid.offset.y) / grid.size
        };
    }
