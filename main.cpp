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
    Vector2 position = {100.0f, 500.0f};
    // initialise the velocity for both the 2 dimensions
    // take note that Vector 2 is defined by 2 public float variables x and y
    Vector2 velocity = {000.0f, -000.0f};
    float radius = 50.0f;
    float timer = 0.0f;
    const float PIXELS_PER_METER = 100.0f;
    const float gravity = 10.0f * PIXELS_PER_METER;

    //while the window is closed
    while (!WindowShouldClose()){

        // update the velocity for the gravity
        velocity.y += gravity * GetFrameTime();

        // update the positon
        position.x += GetFrameTime()*velocity.x; 
        position.y += GetFrameTime()*velocity.y;

        // the update phrase should be seperate from the render drawing
        // what happens if it hits the right side 
        if (position.x + radius >= GetScreenWidth()){
            velocity.x = velocity.x *-1;
            // snapping the position
            position.x = GetScreenWidth() - radius;
        }
        // left side
        if (position.x - radius <= 0){
            velocity.x = velocity.x *-1;
            position.x = radius;
        }
        // top side
        if (position.y - radius <= 0){
            velocity.y = velocity.y *-1;
            position.y = radius;
        }
        // bottom side
        if (position.y + radius >= GetScreenHeight()){
            velocity.y *= -1;
            float overshoot = (position.y + radius) - GetScreenHeight();
            position.y = GetScreenHeight() - radius - overshoot;
        }

        BeginDrawing();
          
        // draw the text from the top of the screen
        DrawText(TextFormat("Let's Simulate!\nTime elapsed %.2f\nVertical velocity = %.2f\nVertical position = %.2f" ,GetTime(),velocity.y, position.y), 0, 0, 30, LIME);

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