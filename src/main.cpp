#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

#include "../include/Ball.h"

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
        myBall.Draw(0);
        myBall1.Draw(100);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}