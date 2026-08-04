#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

int main() {
    // make sure the width and the height can be adjustable
    int width = 1000;
    int height = 1000;
    const float energylost = 0.9f;
    
    // this is what makes it expand with the minimize maximise icon 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(width, height, "Bouncy Ball Simulation"); 

    // start the position of the circle 
    // initialise the velocity for both the 2 dimensions
    const Vector2 INITIAL_POSITION = {100.0f, 500.0f};
    const Vector2 INITIAL_VELOCITY = {200.0f, -200.0f};

    // create the active variables that would move frame by frame
    Vector2 position = INITIAL_POSITION;
    Vector2 velocity = INITIAL_VELOCITY;
    
    float timer = 0.0f;
    const float PIXELS_PER_METER = 100.0f;
    const float gravity = 9.81f * PIXELS_PER_METER;
    const float radius = 50.0f;
    
    // are you holding the ball
    bool isDragging = false;
    
    //while the window is closed
    while (!WindowShouldClose()){
        Vector2 getMousePosition = GetMousePosition();
        
        // add the spacebar that brings ball to the original state
        if (IsKeyPressed(KEY_SPACE)){
            position = INITIAL_POSITION;
            velocity = INITIAL_VELOCITY;
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // hold the ball when you click on it
            if (CheckCollisionPointCircle(getMousePosition, position, radius)) {
                isDragging = true;
            }
        }
        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            if (isDragging){
                
                Vector2 getMouseDelta = GetMouseDelta();
                // guard by divide by 0 errors
                if (GetFrameTime() > 0.0f){
                    velocity.x = getMouseDelta.x / GetFrameTime();
                    velocity.y = getMouseDelta.y / GetFrameTime();
                }
            }
            isDragging = false;
        }

        if (isDragging){
            velocity = {0.0f,0.0f};
            position = getMousePosition;
        } else{ 
            // update the velocity for the gravity
            velocity.y += gravity * GetFrameTime();
    
            // update the positon
            position.x += GetFrameTime()*velocity.x; 
            position.y += GetFrameTime()*velocity.y;
    
            // the update phrase should be seperate from the render drawing
            // what happens if it hits the right side 
            if (position.x + radius >= GetScreenWidth()){
                velocity.x = velocity.x *-energylost;
                // snapping the position
                float overshoot = (position.x + radius) - GetScreenWidth();
                position.x = GetScreenWidth() - radius - overshoot;
            }
            // left side
            if (position.x - radius <= 0){
                velocity.x = velocity.x *-energylost;
                float overshoot = (-position.x + radius);
                position.x = radius + overshoot;
            }
            // top side
            if (position.y - radius <= 0){
                velocity.y = velocity.y *-energylost;
                float overshoot = (-position.y + radius);
                position.y = radius + overshoot;
            }
            // bottom side
            if (position.y + radius >= GetScreenHeight()){
                velocity.y *= -energylost;
                float overshoot = (position.y + radius) - GetScreenHeight();
                position.y = GetScreenHeight() - radius - overshoot;
            }
        }

        BeginDrawing();
          
        // draw the text from the top of the screen
        DrawText(TextFormat("Let's Simulate!\nTime elapsed %.2f\nVertical velocity = %.2f\nVertical position = %.2f" ,GetTime(),velocity.y, position.y), 0, 0, 30, LIME);

        // for changing the background colour
        ClearBackground(BLACK);

        Color ballcolor = RAYWHITE;
        if(isDragging){
            ballcolor = RED;
        }
        DrawCircleV(position, radius, ballcolor);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}