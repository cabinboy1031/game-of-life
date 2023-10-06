#include <stdbool.h>
#include <engine/core.h>
#include <engine/util/timer.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include "gol/game.h"

int main(){
    // Initialization
    //--------------------------------------------------------------------------------------
    VGE_LOG_INFO("Initializing engine...");
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    game_s game = game_new();
    grid_s display_data = grid_create(20, (v_vec2_s){0, 0});
    v_renderer_s *renderer = v_renderer_init("SOKOL test",800, 800);
    v_input_init(renderer->window);

    sg_setup(&(sg_desc){
            .logger.func = slog_func
        });

    simgui_setup(&(simgui_desc_t){
        .logger = slog_func
    });

    VGE_LOG_INFO("Creating test data...");
    /* a vertex buffer */
    const float vertices[] = {
        // positions            // colors
         0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
    };

    VGE_LOG_INFO("Initializing test pipeline...");
    /* a pipeline state object (default render states are fine for triangle) */
    sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc){
        .shader =
            sg_make_shader(&(sg_shader_desc){
                .vs.source =
                    "#version 330\n"
                    "layout(location=0) in vec4 position;\n"
                    "layout(location=1) in vec4 color0;\n"
                    "out vec4 color;\n"
                    "void main() {\n"
                    "  gl_Position = position;\n"
                    "  color = color0;\n"
                    "}\n",
                .fs.source =
                    "#version 330\n"
                    "in vec4 color;\n"
                    "out vec4 frag_color;\n"
                    "void main() {\n"
                    "  frag_color = color;\n"
                    "}\n"
            }),
        .layout = {
            .attrs = {
                [0].format=SG_VERTEXFORMAT_FLOAT3,
                [1].format=SG_VERTEXFORMAT_FLOAT4
            }
        }
    });


    VGE_LOG_INFO("Creating resources...");
    /* resource bindings */
    sg_bindings bind = {
        .vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
            .data = SG_RANGE(vertices)
        }),
    };

    /* default pass action (clear to grey) */
    sg_pass_action pass_action = {0};

    timer_s timer;
    timer_start(&timer, .25);
    //--------------------------------------------------------------------------------------

    // Main game loop

    while (!glfwWindowShouldClose(renderer->window)){       // Detect window close button or ESC key
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        // Input
        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------
        // Game Update 
        //----------------------------------------------------------------------------------
        if(!game.paused && timer_done(timer)){
            game_update(&game);
            timer_start(&timer, 0.25);
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        int cur_width, cur_height;
        glfwGetFramebufferSize(renderer->window, &cur_width, &cur_height);

        sg_begin_default_pass(&pass_action, cur_width, cur_height);
            sg_apply_pipeline(pip);
            sg_apply_bindings(&bind);
            sg_draw(0, 3, 1);

            simgui_new_frame(&(simgui_frame_desc_t){
                    .width = cur_width,
                    .height = cur_height,
                    .delta_time = 0.1,});
                bool showDemo = true;
                igShowDemoWindow(&showDemo);

            simgui_render();
        sg_end_pass();
        sg_commit();
        glfwSwapBuffers(renderer->window);
        glfwPollEvents();
}

// De-Initialization
//--------------------------------------------------------------------------------------
game_delete(&game);
//v_renderer_delete(renderer);
simgui_shutdown();
//--------------------------------------------------------------------------------------
return 0;
}
