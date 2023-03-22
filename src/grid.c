#include "gol/grid.h"

grid_s grid_create(int size, Vector2 offset) { 
    if(size == 0){
        return (grid_s){1,(Vector2){}};
    } else {
        return (grid_s){size, offset};
    }
}