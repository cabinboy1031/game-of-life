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
        .ignore_hold = true };

    key_input_s space_input = (key_input_s){
        .key = KEY_SPACE,
        .ignore_hold = true
    };
    bool run_simulation = false;

    Timer timer;
    StartTimer(&timer, .25);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){       // Detect window close button or ESC key
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        // Input
        //----------------------------------------------------------------------------------
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
                Vector2 delta = GetMouseDelta();
                delta = Vector2Scale(delta, -1.0f/camera.zoom);

                camera.target = Vector2Add(camera.target, delta);
            }
        
        if(input_mouse_run(&lmb_input)){
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                // get the mouse position
                Vector2 mouse = Vector2Transform(
                    GetMousePosition(), 
                    MatrixInvert(GetCameraMatrix2D(camera)));


                // find what cell that mouse position corresponds to
                Vector2 cell = screen_to_grid(display_data, mouse);
                // Flip the state of the current cell at the mouse position
                game.screen_board[(int)((cell.x * GAME_WIDTH) + cell.y)] = !game.screen_board[(int)((cell.x * GAME_WIDTH) + cell.y)];
            }
        }
        if(input_key_run(&space_input)){
            run_simulation = !run_simulation;
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
        if(run_simulation && TimerDone(timer)){
            game_update(&game);
            StartTimer(&timer, 0.25);
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(camera);

                for(int x = 0; x <= GAME_WIDTH; x++){
                    for(int y = 0; y <= GAME_HEIGHT; y++){
                        if(game.screen_board[(x * GAME_WIDTH) + y]){
                            DrawRectangle(
                                display_data.offset.x + (x * display_data.size),
                                display_data.offset.y + (y * display_data.size),
                                display_data.size,
                                display_data.size,
                                ORANGE);
                        }
                    }
                }

                for(int x = 0; x <= GAME_WIDTH; x++){
                    DrawLine(
                        display_data.offset.x + (x * display_data.size),
                        display_data.offset.y,
                        display_data.offset.x + (x * display_data.size),
                        display_data.offset.y + (GAME_HEIGHT * display_data.size),
                        GRAY);
                }
                for(int y = 0; y <= GAME_HEIGHT; y++){
                    DrawLine(
                        display_data.offset.x,
                        display_data.offset.y + (y * display_data.size),
                        display_data.offset.x + (GAME_WIDTH * display_data.size),
                        display_data.offset.y + (y * display_data.size),
                        GRAY);
                }
                
                
            EndMode2D();

            DrawText("Mouse right button drag to move, mouse wheel to zoom", 10, 10, 20, WHITE);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
return 0;
}