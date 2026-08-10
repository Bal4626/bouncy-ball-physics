#ifndef BALL_H
#define BALL_H
#include "raylib.h"

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
    float timer = 0.0f;

    // default constructor
    Ball() = default;
    Ball(Vector2 ballPosition, Vector2 ballVelocity, Color ballColor, float ballRadius, float ballEnergyLost);

    //Methods
    void Update();
    void Draw();
    void Reset();
};
#endif