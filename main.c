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

    VGE_LOG_INFO("Creating test buffer...");
    /* a vertex buffer */
    const float vertices[] = {
        // positions            // colors
         0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
    };
    sg_buffer vbuf = sg_make_buffer(&(sg_buffer_desc){
        .data = SG_RANGE(vertices)
    });

    VGE_LOG_INFO("Creating test shader...");
    /* a shader */
    sg_shader shd = sg_make_shader(&(sg_shader_desc){
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
    });

    VGE_LOG_INFO("Initializing pipeline...");
    /* a pipeline state object (default render states are fine for triangle) */
    sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc){
        .shader = shd,
        .layout = {
            .attrs = {
                [0].format=SG_VERTEXFORMAT_FLOAT3,
                [1].format=SG_VERTEXFORMAT_FLOAT4
            }
        }
    });

    VGE_LOG_INFO("Binding resources...");
    /* resource bindings */
    sg_bindings bind = {
        .vertex_buffers[0] = vbuf
    };

    /* default pass action (clear to grey) */
    sg_pass_action pass_action = {0};
    /*
    Camera2D camera = { 0 };
    camera.zoom = 0.2f;

    SetTargetFPS(TARGET_FPS);                   // Set our game to run at 60 frames-per-second
    
    key_input_s lmb_input = (key_input_s){
        .key = MOUSE_LEFT_BUTTON,
        .ignore_hold = true,
        .mode = INPUT_MOUSE,
        };

    key_input_s rmb_input = (key_input_s){
        .key = MOUSE_RIGHT_BUTTON,
        .ignore_hold = false,
        .mode = INPUT_MOUSE,
        };

    key_input_s space_input = (key_input_s){
        .key = KEY_SPACE,
        .ignore_hold = true,
        .mode = INPUT_KEY,
    };
    */

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
                /*
            if (input_run(&rmb_input)){
                Vector2 delta = GetMouseDelta();
                // TODO change to cglm implementation
                delta = Vector2Scale(delta, -1.0f/camera.zoom);

                camera.target = Vector2Add(camera.target, delta);
            }
                */

            /*
        if(input_run(&lmb_input)){
            // get the mouse position
            // TODO change to cglm implementation
            Vector2 mouse = Vector2Transform(
                GetMousePosition(), 
                MatrixInvert(GetCameraMatrix2D(camera)));



            // find what cell that mouse position corresponds to
            Vector2 cell = screen_to_grid(display_data, mouse);
            // Flip the state of the current cell at the mouse position
            game.screen_board[game_cell_index(&game, (int)cell.x, (int)cell.y)] = !game.screen_board[game_cell_index(&game, (int)cell.x, (int)cell.y)];

            // Add cell and neighbors to active state
            game_set_active_with_neighbors(&game, (int)cell.x, (int)cell.y);
        }
            */

        /*
        if(input_run(&space_input)){
            game.paused = !game.paused;
        }
        */

        // Zoom based on mouse wheel
        /*
        float wheel = GetMouseWheelMove();
        if (wheel != 0){
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            
            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.125f;

            camera.zoom += (wheel*zoomIncrement);
            if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
        }
        */

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
                    .delta_time = 0.1,
                });
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
