#ifndef SpatialHashGrid_H
#define SpatialHashGrid_H

#include "raylib.h"
// include Ball.h so the grid knows what a ball is 
#include "Ball.h"

#include <vector>
#include <cmath>
#include <algorithm>

// struct SpatialHashGrid is a datatype that does the O(n) collisions;
struct SpatialHashGrid{
    // convert coordinate positions to integer cell coordinates
    float spatialHashGridCellDimension = 6.0f;
    int spatialHashGridCols = 0;
    int spatialHashGridRows = 0;
    int spatialHashGridTotalCells = 0;

    // 2d vector for the cell buckets
    // e.g. spatialHashGridMap[5] would have [0,4,13] which are the balls in the cell 5
    std::vector <std::vector<int>> spatialHashGridMap;

    void Init(int screenWidth, int screenHeight);

    // empties the bucket at the end for the next render loop
    void Clear();

    // The const is only read only and the & means to only look at the original list of balls in memory instead of copying each time
    void Insert(const std::vector<Ball>& balls);

    std::vector<int> GetNeighbours(Vector2 position);
};

#endif