#include <stdio.h>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>

#include "raygui.h"
#include "gol/game.h"
#include "gol/grid.h"


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
    

    for(int x = 0; x <= GAME_WIDTH; x++){
        for(int y = 0; y <= GAME_HEIGHT; y++){
            if(y % 2 != 0){
                game.screen_board[x * SCREEN_WIDTH + y] = true;
            }
        }
    }
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Translate based on mouse right click
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }
        
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            // Flip the state of the currently selected cell
        }

        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
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

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                for(int x = 0; x <= GAME_WIDTH; x++){
                    for(int y = 0; y <= GAME_HEIGHT; y++){
                        if(game.screen_board[(x * GAME_WIDTH) + y]){
                            DrawRectangle(
                                display_data.offset.x + (x * display_data.size),
                                display_data.offset.y + (y * display_data.size),
                                display_data.size,
                                display_data.size,
                                YELLOW);
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