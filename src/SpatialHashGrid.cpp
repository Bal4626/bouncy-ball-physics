#include "SpatialHashGrid.h"


//no constructor needed in this case
//init the 4 main variables in this funciton
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

/*
Input: Reference to a vector of ALL Ball instance (std::vector<Ball>)
(the inputs to the constructor) returns nothing but populates
SpartialHashGridMap = [[0,3,5],[2,4,6],[1], []] for example
*/

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


/*
GetNeighbours(balls[0].position) => [0,1,3] Hence balls 1 and 3 are neighbours w 0
*/
std::vector <int> SpatialHashGrid::GetNeighbours(Vector2 position){
    // this is the list that u wanna return
    std::vector <int> neighbours;

    int colX = static_cast<int>(std::floor(position.x / spatialHashGridCellDimension));
    int rowY = static_cast<int>(std::floor(position.y / spatialHashGridCellDimension));

    // loop over the termination conditions
    for (int i = colX - 1; i <= colX + 1; ++i){
        for (int j = rowY - 1; j <= rowY + 1; ++j){

            // validate bounds for the neighbour cells (i,j)
            if(i >= 0 && i < spatialHashGridCols && j >= 0 && j < spatialHashGridRows){
                int cellIndex = i + (j * spatialHashGridCols);

                // extract the ball ID's that are stored at spartialHashGridMap[cellIndex]
                for (int ballId : spatialHashGridMap[cellIndex]){
                    neighbours.push_back(ballId);
                }
            }
        }
    }
    return neighbours;
}
