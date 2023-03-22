#include "gol/grid.h"
#include "math.h"

grid_s grid_create(int size, Vector2 offset) { 
    if(size == 0){
        return (grid_s){1,(Vector2){}};
    } else {
        return (grid_s){size, offset};
    }
}

Vector2 grid_to_screen(grid_s grid, Vector2 gc) { 
    return (Vector2){
        grid.offset.x + (grid.size * gc.x),
        grid.offset.y + (grid.size * gc.y),
        };
    }

Vector2 screen_to_grid(grid_s grid, Vector2 sc) { 
    Vector2 result = screen_to_grid_exact(grid, sc);
    
    return (Vector2){
        floor(result.x), 
        floor(result.y)
        };
}

Vector2 screen_to_grid_exact(grid_s grid, Vector2 sc) { 
    return (Vector2){
            (sc.x - grid.offset.x) / grid.size,
            (sc.y - grid.offset.y) / grid.size
        };
    }