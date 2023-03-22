#include "gol/grid.h"

grid_s grid_create(int size, Vector2 offset) { 
    if(size == 0){
        return (grid_s){1,(Vector2){}};
    } else {
        return (grid_s){size, offset};
    }
}

Vector2 grid_to_screen(grid_s grid, Vector2 gc) { return (Vector2){0,0};}

Vector2 screen_to_grid(grid_s grid, Vector2 sc) { return (Vector2){0,0};}

Vector2 screen_to_grid_exact(grid_s grid, Vector2 sc) { return (Vector2){0,0};}