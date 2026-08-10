#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <vector>

#include "Ball.h"

int main() {
    // make sure the width and the height can be adjustable
    int width = 1000;
    int height = 1000;
    int numberOfBalls = 0;
    
    // this is what makes it expand with the minimize maximise icon 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Bouncy Ball Simulation"); 
    SetTargetFPS(60);

    std::vector<Ball> balls;// instead of creating one by one use a vector that holds ball objects
    // Ball is the Instance in the header file ball is the single object inside the container called balls

    //while the window is closed
    while (!WindowShouldClose()){

        //when i press the right key another ball needs to appear the the position of the cursor
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            
            numberOfBalls += 1;
            Vector2 mousePosition = {(float)GetMouseX(), (float)GetMouseY()};
            
            if(numberOfBalls % 3 == 0){
                //init the red balls
                //Vector2 mousePosition = {(float)GetMouseX(), (float)GetMouseY()};
                balls.push_back(Ball(mousePosition,{400.0f,500.0f},RED, 50.0f, 0.8f));
            }
            else if(numberOfBalls % 3 == 1){
                //init the default white balls
                balls.push_back(Ball(mousePosition, {200.0f, -200.0f}, RAYWHITE, 50.0f, 0.8f));
            }
            else{
                // init the yellow balls
                //Vector2 mousePosition = {(float)GetMouseX(), (float)GetMouseY()};
                balls.push_back(Ball(mousePosition, {100.0f, 500.0f}, YELLOW, 50.0f, 0.8f));
            }
        }
        // update the physics for all balls b4 redndering
        for (auto& ball : balls){
            ball.Update();
        }

        // reset logic for all balls when pressed space key
        if (IsKeyPressed(KEY_SPACE)){
            for (auto& ball : balls){
                ball.Reset();
            }
        }

        if (IsKeyPressed(KEY_C)){
            for (auto& ball : balls){
                balls.clear();
            }
        }
        
        BeginDrawing();
    
        ClearBackground(BLACK);
    
        // render the ball
        for (auto& ball : balls){
            ball.Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}