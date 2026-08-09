#include "Ball.h"

// This is the constructor and it must have the exact same name as teh struct
// and NO return type i.e. (void, int, etc...)
Ball::Ball(Vector2 ballPosition, Vector2 ballVelocity, Color ballColor, float ballRadius, float ballEnergyLost){
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
void Ball::Update(){
    const float PIXELS_PER_METER = 100.0f;
    const float gravity = 9.81f * PIXELS_PER_METER;
    Vector2 getMousePosition = GetMousePosition();

    timer += GetFrameTime();
    
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
void Ball::Draw(int textOffsetY = 0){
    Color ballcolor = color;
    if(isDragging){
        ballcolor = RED;
    }
    //DrawText(TextFormat("Let's Simulate!\nTime elapsed %.2f\nVertical velocity = %.2f\nVertical position = %.2f" ,GetTime(),velocity.y, position.y), textOffsetY, 0, 30, LIME);
    DrawText(TextFormat("Let's Simulate!\nTime elapsed %.2f",timer),0 ,0 ,30, LIME);
    DrawCircleV(position, radius, ballcolor);
}
void Ball::Reset(){
    // add the spacebar that brings ball to the original state
    position = INITIAL_POSITION;
    velocity = INITIAL_VELOCITY;
    timer = 0.0f; // this would reset the spacebar
};