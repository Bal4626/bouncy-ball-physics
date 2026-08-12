#include "SpatialHashGrid.h"


//no constructor needed in this case

void SpatialHashGrid::Init(int screenWidth, int screenHeight){
    spatialHashGridCols = screenWidth / spatialHashGridCellDimension;
    spatialHashGridRows = screenHeight / spatialHashGridCellDimension;
    spatialHashGridTotalCells = spatialHashGridRows * spatialHashGridCols;

    spatialHashGridMap.resize(spatialHashGridTotalCells);
}

// to reset every grid back to 0 in the 2d grid map
void SpatialHashGrid::Clear(){
    for (auto& map : spatialHashGridMap){
        map.clear();
    }
}

void SpatialHashGrid::Insert(const std::vector<Ball>& balls){
    Clear();
    for (size_t i = 0; i < balls.size(); ++i){
        // if ball is at pixel 20,49 and the celldimension is 6x6 so floor(20/6) floor(49/6) whcih is 3,8
        int colX = static_cast<int>(balls[i].position.x / spatialHashGridCellDimension);
        int rowY = static_cast<int>(balls[i].position.y / spatialHashGridCellDimension);

        // lets say there are 10 columns and 10 rows converts the (cols, rows) (3,8) into 83
        int cellIndex = colX + (rowY * spatialHashGridCols);

        // since the cellIndex = 83 is less than cell 99 and more or equal to 0 we push it
        if(cellIndex >= 0 && cellIndex < spatialHashGridTotalCells){
            // if both ball number 4 and 9 are in that cellIndex that means that when i = 4, 4 will get pushed and so when i = 9 resulting in [4, 9] in cellIndex[83]
            spatialHashGridMap[cellIndex].push_back(i);
        }
    }
}
/* This function looks at each balls position (position.x,position.y) and
checks the immeadiate 3x3 cells around it and then adds into the list of integers
and pushes the id of the ball into the list. example:
GetNeighbours(balls[0].position) => [0,1,3] means you only need to calculate
balls 0 with 1 and 3
*/
std::vector <int> SpatialHashGrid::GetNeighbours(Vector2 position){
    // this is the list that u wanna return
    std::vector <int> neighbours;


}



/*
Let's break down the logic for querying the grid.

The core question for querying is: **"If I have a ball, which grid cells do I need to check for potential collisions?"**

**The "Edge" Problem**
If a ball is sitting right on the right boundary of Cell 0, it might be overlapping with a ball located in Cell 1. If you only check the ball's "home" cell, you will completely miss this collision.

**The 3x3 Solution**
To guarantee we catch every overlap, we check a **3x3 block** of cells centered on the ball. That means checking the ball's home cell, plus up to 8 surrounding neighbors (top, bottom, left, right, and diagonals).

Here is the step-by-step logic to build this:

1. **Find the Home Cell:** Calculate the target ball's `colX` and `rowY` using the exact same division and `static_cast<int>` you used in `Insert()`.
2. **Setup the Search Grid:** You need to check every column from `colX - 1` to `colX + 1`, and every row from `rowY - 1` to `rowY + 1`. (This creates 9 coordinate pairs).
3. **The Boundary Check (Crucial):** Before you convert a neighbor's 2D coordinate into a 1D index, you must verify that the neighbor actually exists. If your ball is in Column 0, trying to check `colX - 1` results in Column -1, which will crash your game.
4. **Convert and Collect:** If the neighbor coordinate is safely inside the grid dimensions, convert it to your 1D `cellIndex` and gather all the ball IDs stored in that cell.

Do you want to try setting up the loops for Step 2, or should we look at how to handle the boundary math in Step 3 first?*/