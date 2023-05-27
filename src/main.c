#include <stdio.h>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>

#include "raygui.h"
#include "gol/game.h"
#include "gol/grid.h"
#include "gol/input.h"
#include "gol/timer.h"


int main(){
    // Initialization
    //--------------------------------------------------------------------------------------
    printf("%d\n", sizeof(int));
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int TARGET_FPS = 60;
    game_s game = game_new();
    grid_s display_data = grid_create(20, (Vector2){0, 0});

    InitWindow( SCREEN_WIDTH, 
                SCREEN_HEIGHT, 
                "raylib [core] example - 2d camera mouse zoom");

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

    timer_s timer;
    timer_start(&timer, .25);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){       // Detect window close button or ESC key
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        // Input
        //----------------------------------------------------------------------------------
            if (input_run(&rmb_input)){
                Vector2 delta = GetMouseDelta();
                delta = Vector2Scale(delta, -1.0f/camera.zoom);

                camera.target = Vector2Add(camera.target, delta);
            }
        
        if(input_run(&lmb_input)){
            // get the mouse position
            Vector2 mouse = Vector2Transform(
                GetMousePosition(), 
                MatrixInvert(GetCameraMatrix2D(camera)));


            // find what cell that mouse position corresponds to
            Vector2 cell = screen_to_grid(display_data, mouse);
            // Flip the state of the current cell at the mouse position
            game.screen_board[game_cell_index(&game, (int)cell.x, (int)cell.y)] = !game.screen_board[game_cell_index(&game, (int)cell.x, (int)cell.y)];
        }

        if(input_run(&space_input)){
            game.paused = !game.paused;
        }

        // Zoom based on mouse wheel
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
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(camera);
                for(int x = 0; x < game.width; x++){
                    for(int y = 0; y < game.height; y++){
                        if(game.screen_board[(x * game.width) + y]){
                            DrawRectangle(
                                display_data.offset.x + (x * display_data.size),
                                display_data.offset.y + (y * display_data.size),
                                display_data.size,
                                display_data.size,
                                ORANGE);
                        }
                    }
                }

                for(int x = 0; x <= game.width; x++){
                    DrawLine(
                        display_data.offset.x + (x * display_data.size),
                        display_data.offset.y,
                        display_data.offset.x + (x * display_data.size),
                        display_data.offset.y + (game.height * display_data.size),
                        GRAY);
                }

                for(int y = 0; y <= game.height; y++){
                    DrawLine(
                        display_data.offset.x,
                        display_data.offset.y + (y * display_data.size),
                        display_data.offset.x + (game.width * display_data.size),
                        display_data.offset.y + (y * display_data.size),
                        GRAY);
                }
            EndMode2D();
            DrawText("Mouse right button drag to move, mouse wheel to zoom", 10, 10, 20, WHITE);
            DrawText(game.paused ? "Game: Paused" : "Game: Running...", 11,20,20, game.paused ? RED : GREEN);
        EndDrawing();
        //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
game_delete(&game);
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
return 0;
}
