#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

// struct is a datatype that can create variables;
struct Ball{
    Vector2 position = {100.0f, 500.0f};
    Vector2 velocity = {200.0f, -200.0f};
    Color color = RAYWHITE;
    float radius = 50.0f; 
    bool isDragging = false;
    float energyLost = 0.9f;
    Vector2 INITIAL_POSITION = {100.0f, 500.0f};
    Vector2 INITIAL_VELOCITY = {200.0f, -200.0f};

    // default constructor
    Ball() = default;
    
    // This is the constructor and it must have the exact same name as teh struct
    // and NO return type i.e. (void, int, etc...)
    Ball(Vector2 ballPosition, Vector2 ballVelocity, Color ballColor, float ballRadius, float ballEnergyLost){
        position = ballPosition;
        velocity = ballVelocity;
        color = ballColor;
        radius = ballRadius; //cannot put float radius = radius due to variable shadowing
        energyLost = ballEnergyLost;
        INITIAL_POSITION = ballPosition;
        INITIAL_VELOCITY = ballVelocity;
        // isDragging would automatically default to false
    }

    // custom constructor for color and custom energy loss 
    
    void Update(){
        float timer = 0.0f;
        const float PIXELS_PER_METER = 100.0f;
        const float gravity = 9.81f * PIXELS_PER_METER;
        Vector2 getMousePosition = GetMousePosition();
        
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
                velocity.x = velocity.x *-energyLost;
                // snapping the position
                float overshoot = (position.x + radius) - GetScreenWidth();
                position.x = GetScreenWidth() - radius - overshoot;
            }
            // left side
            if (position.x - radius <= 0){
                velocity.x = velocity.x *-energyLost;
                float overshoot = (-position.x + radius);
                position.x = radius + overshoot;
            }
            // top side
            if (position.y - radius <= 0){
                velocity.y = velocity.y *-energyLost;
                float overshoot = (-position.y + radius);
                position.y = radius + overshoot;
            }
            // bottom side
            if (position.y + radius >= GetScreenHeight()){
                velocity.y *= -energyLost;
                float overshoot = (position.y + radius) - GetScreenHeight();
                position.y = GetScreenHeight() - radius - overshoot;
            }
        }
    }
    void Draw(){
        Color ballcolor = color;
        if(isDragging){
            ballcolor = RED;
        }
        DrawText(TextFormat("Let's Simulate!\nTime elapsed %.2f\nVertical velocity = %.2f\nVertical position = %.2f" ,GetTime(),velocity.y, position.y), 0, 0, 30, LIME);
        DrawCircleV(position, radius, ballcolor);
    }
    void Reset(){
        // add the spacebar that brings ball to the original state
        position = INITIAL_POSITION;
        velocity = INITIAL_VELOCITY;
    }
};

int main() {
    // make sure the width and the height can be adjustable
    int width = 1000;
    int height = 1000;
    
    // this is what makes it expand with the minimize maximise icon 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Bouncy Ball Simulation"); 
    
    Ball myBall;
    Ball myBall1 ({100.0f, 500.0f}, {100.0f, 500.0f}, YELLOW, 50.0f, 0.8f);

    //while the window is closed
    while (!WindowShouldClose()){

        if (IsKeyPressed(KEY_SPACE)){
            myBall.Reset();
            myBall1.Reset();
        }

        // calculates the physics and positions before rendering 
        myBall.Update();
        myBall1.Update();
        BeginDrawing();

        ClearBackground(BLACK);

        // render the ball
        myBall.Draw();
        myBall1.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}