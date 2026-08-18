#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <vector>

#include "Ball.h"
#include "SpatialHashGrid.h"

int main() {
    // make sure the width and the height can be adjustable
    int numberOfBalls = 0;
    
    // this is what makes it expand with the minimize maximise icon 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1000, 1000, "Bouncy Ball Simulation"); 
    SetTargetFPS(60);
    
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    
    // create a instance of SpatialHashGrid
    SpatialHashGrid spatialGrid;
    spatialGrid.Init(width,height);
    
    // Ball is the Instance in the header file ball is the single object inside the container called balls
    std::vector<Ball> balls;// instead of creating one by one use a vector that holds ball objects
    
    
    //while the window is closed
    while (!WindowShouldClose()){

        // we need to update the width and height when we resize
        if(IsWindowResized()){
            width = GetScreenWidth();
            height = GetScreenHeight();
            spatialGrid.Init(width, height);
        }
        
        //when i press the right key another ball needs to appear the the position of the cursor
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            
            numberOfBalls += 1;
            Vector2 mousePosition = {(float)GetMouseX(), (float)GetMouseY()};
            
            if(numberOfBalls % 3 == 0){
                //init the red balls
                //Vector2 mousePosition = {(float)GetMouseX(), (float)GetMouseY()};
                balls.push_back(Ball(mousePosition,{40.0f,50.0f},RED, 20.0f, 0.8f));
            }
            else if(numberOfBalls % 3 == 1){
                //init the default white balls
                balls.push_back(Ball(mousePosition, {20.0f, -20.0f}, RAYWHITE, 20.0f, 0.8f));
            }
            else{
                // init the yellow balls
                //Vector2 mousePosition = {(float)GetMouseX(), (float)GetMouseY()};
                balls.push_back(Ball(mousePosition, {10.0f, 50.0f}, YELLOW, 20.0f, 0.8f));
            }
        }

        // loop thru the balls and update (i.e. move the balls)
        for(auto& ball : balls){
            ball.Update();
        }

        // // First we insert all the balls and Insert will also clear() automatically
        spatialGrid.Insert(balls); // since balls is alr a datatype of ball

        for (size_t i = 0; i < balls.size(); ++i){
            std::vector <int> neighbours = spatialGrid.GetNeighbours(balls[i].position);

            // for (size_t j : neighbours){
            //     //do not check with itself
            //     if(i == j) continue;

            //     // stop checking the pair twice
            //     if(i < j){
            //         Ball::BallCollision(balls[i], balls[j]);
            //     }
            // }

            for (size_t j = i + 1; j < balls.size(); ++j) {
                Ball::BallCollision(balls[i], balls[j]);
            }
        }

        // reset logic for all balls when pressed space key
        if (IsKeyPressed(KEY_SPACE)){
            for (auto& ball : balls){
                ball.Reset();
            }
        }

        if (IsKeyPressed(KEY_C)){
            //for (auto& ball : balls){ //dont need to use this since i never use my functions that i created for Ball
            balls.clear();
            //}
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