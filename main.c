#include <stdbool.h>
#include <engine/core.h>
#include <engine/util/asset.h>
#include <engine/util/timer.h>
#include <stdio.h>
#include "gol/game.h"
#include "engine/graphics/sprite.h"

int main(){
    // Initialization
    //-------------------------------------------------------------------------------
    VGE_LOG_INFO("Initializing engine...");
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    v_assetmanager_init();

    v_renderer_s* renderer = renderer_init();
    v_input_init(renderer->window);
    // Post engine init functions
    game_s game = game_new();
    grid_s display_data = grid_create(20, (v_vec2_s){0, 0});

    v_sprite_s *cell_sprite = v_sprite_create(renderer);

    while(!glfwWindowShouldClose(renderer->window)){
        renderer_update(renderer);
    }


    game_delete(&game);
    renderer_delete(renderer);
//--------------------------------------------------------
return 0;
}
