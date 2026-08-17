#include "Ball.h"
#include <cmath>

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
        //update the velocity with gravity
        velocity.y += gravity * GetFrameTime(); 

        // init and predict the next position
        predictedPosition.x = position.x + velocity.x * GetFrameTime();
        predictedPosition.y = position.y + velocity.y * GetFrameTime();

        // what happens if it hits the right side
        if (predictedPosition.x + radius >= GetScreenWidth()){
            predictedPosition.x = GetScreenWidth() - radius;
            velocity.x *= -energyLost; // dampen the velocity
        }
        // what happens if it hits the left side
        if (predictedPosition.x - radius <= 0){
            predictedPosition.x = radius;
            velocity.x *= -energyLost; // dampen the velocity
        }
        // what happens if it hits the top side
        if (predictedPosition.y - radius <= 0){
            predictedPosition.y = radius;
            velocity.y *= -energyLost; // dampen the velocity
        }
        // what happens if it hits the bottom side
        if (predictedPosition.y + radius >= GetScreenHeight()){
            predictedPosition.y = GetScreenHeight() - radius;
            velocity.y *= -energyLost; // dampen the velocity
        }
        // you need to do this due to the DrawCircleV
        position = predictedPosition;
    }
}

// handles the collision of the balls with each other
void Ball::BallCollision(Ball& a,Ball& b){
    
    float dx = b.position.x - a.position.y;
    float dy = b.position.y - a.position.y;

    float distance = std::sqrt(dx * dx + dy * dy);

    if(distance <= b.radius + a.radius){
        
    }


}

void Ball::Draw(){
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