#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

int main() {
    // make sure the width and the height can be adjustable
    int width = 1000;
    int height = 1000;

    // this is what makes it expand with the minimize maximise icon 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(width, height, "Bouncy Ball Simulation"); 

    // start the position of the circle 
    Vector2 position = {500.0f, 500.0f};
    // initialise the velocity for both the 2 dimensions
    // take note that Vector 2 is defined by 2 public float variables x and y
    Vector2 velocity = {10.0f, 10.0f};
    float radius = 50.0f;
    float timer = 0.0f;

    //while the window is closed
    while (!WindowShouldClose()){

        BeginDrawing();
          
        // draw the text from the top of the screen
        DrawText(TextFormat("Let's Simulate!\nTime elapsed %.2f",GetTime()), 0, 0, 30, LIME);
        // update the positon
        position.x += GetFrameTime()*velocity.x; 
        position.y += GetFrameTime()*velocity.y;
        
        // for changing the background colour
        timer += GetFrameTime();
        if ((int)timer % 2 == 0){
            ClearBackground(BLACK);

        } else{
            //this is what changes the background
            ClearBackground(DARKBLUE);
        }
        DrawCircleV(position, radius, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}