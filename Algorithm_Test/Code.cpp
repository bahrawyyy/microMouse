#include <iostream>
#include <string>
#include <queue>
#include "API.h"
#include <stdio.h>


int Orient = 0;


#define FORWARD   0
#define RIGHT     1
#define BACKWARD  2
#define LEFT      3



int cellsArray[16][16] = {0};


int floodArray[16][16] = {
    {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
    {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
    {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
    {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
    {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
    {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
    {8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
    {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
    {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
    {8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
    {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
    {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
    {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
    {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
    {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
    {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14}
};








void log(const std::string &text)
{
  std::cerr << text << std::endl;
}



/**================================================================
 * @Fn             - updateWalls
 * @brief          - Updates cell values based on wall and orientation conditions
 * @param [in]     - x: The x-coordinate of the cell in the grid.
 * @param [in]     - y: The y-coordinate of the cell in the grid.
 * @param [in]     - orient: The current orientation (0 to 3) representing North, East, South, or West.
 * @param [in]     - L: Boolean indicating presence of left wall.
 * @param [in]     - R: Boolean indicating presence of right wall.
 * @param [in]     - F: Boolean indicating presence of front wall.
 * @retval         - None
 */


void updateCells(int x, int y, int orient, bool left, bool right, bool forward)
{
  log(std::to_string(x));
  log(std::to_string(y));
  if (left && right && forward)
  {
    if (orient == FORWARD)
      cellsArray[x][y] = 13;
    else if (orient == RIGHT)
      cellsArray[x][y] = 12;
    else if (orient == BACKWARD)
      cellsArray[x][y] = 11;
    else if (orient == LEFT)
      cellsArray[x][y] = 14;
  }
  else if (left && right && !forward)
  {
    if (orient == FORWARD || orient == BACKWARD)
      cellsArray[x][y] = 9;
    else if (orient == RIGHT || orient == LEFT)
      cellsArray[x][y] = 10;
  }
  else if (left && !right && forward)
  {
    if (orient == FORWARD)
      cellsArray[x][y] = 8;
    else if (orient == RIGHT)
      cellsArray[x][y] = 7;
    else if (orient == BACKWARD)
      cellsArray[x][y] = 6;
    else if (orient == LEFT)
      cellsArray[x][y] = 5;
  }
  else if (!left && right && forward)
  {
    if (orient == FORWARD)
      cellsArray[x][y] = 7;
    else if (orient == RIGHT)
      cellsArray[x][y] = 6;
    else if (orient == BACKWARD)
      cellsArray[x][y] = 5;
    else if (orient == LEFT)
      cellsArray[x][y] = 8;
  }
  else if (forward)
  {
    if (orient == FORWARD)
      cellsArray[x][y] = 2;
    else if (orient == RIGHT)
      cellsArray[x][y] = 3;
    else if (orient == BACKWARD)
      cellsArray[x][y] = 4;
    else if (orient == LEFT)
      cellsArray[x][y] = 1;
  }
  else if (left)
  {
    if (orient == FORWARD)
      cellsArray[x][y] = 1;
    else if (orient == RIGHT)
      cellsArray[x][y] = 2;
    else if (orient == BACKWARD)
      cellsArray[x][y] = 3;
    else if (orient == LEFT)
      cellsArray[x][y] = 4;
  }
  else if (right)
  {
    if (orient == FORWARD)
      cellsArray[x][y] = 3;
    else if (orient == RIGHT)
      cellsArray[x][y] = 4;
    else if (orient == BACKWARD)
      cellsArray[x][y] = 1;
    else if (orient == LEFT)
      cellsArray[x][y] = 2;
  }
}



/**================================================================
 * @Fn             - isAccessible
 * @brief          - Determines if the mouse can move from (current_x,current_y) to (target_x,target_y) (two adjacent cells)
 * @param [in]     - current_x: The x-coordinate of the current cell.
 * @param [in]     - current_y: The y-coordinate of the current cell.
 * @param [in]     - target_x: The x-coordinate of the target cell.
 * @param [in]     - target_y: The y-coordinate of the target cell.
 * @retval         - bool: True if the mouse can move, False otherwise.
 */



bool isAccessible(int current_x, int current_y, int target_x, int target_y)
{
  if (current_x == target_x)
  { // if the target is below current
    if (current_y > target_y)
    {
      if ((cellsArray[current_x][current_y] == 4) || (cellsArray[current_x][current_y] == 5) || (cellsArray[current_x][current_y] == 6) || (cellsArray[current_x][current_y] == 10) || (cellsArray[current_x][current_y] == 11) || (cellsArray[current_x][current_y] == 12) || (cellsArray[current_x][current_y] == 14))
        return false;
      else
        return true;
    }
    else
    { // if the target is above current
      if ((cellsArray[current_x][current_y] == 2) || (cellsArray[current_x][current_y] == 7) || (cellsArray[current_x][current_y] == 8) || (cellsArray[current_x][current_y] == 10) || (cellsArray[current_x][current_y] == 12) || (cellsArray[current_x][current_y] == 13) || (cellsArray[current_x][current_y] == 14))
        return false;
      else
        return true;
    }
  }
  else if (current_y == target_y)
  { // if target is on the left of the current
    if (current_x > target_x)
    {
      if ((cellsArray[current_x][current_y] == 1) || (cellsArray[current_x][current_y] == 5) || (cellsArray[current_x][current_y] == 8) || (cellsArray[current_x][current_y] == 9) || (cellsArray[current_x][current_y] == 11) || (cellsArray[current_x][current_y] == 13) || (cellsArray[current_x][current_y] == 14))
        return false;
      else
        return true;
    }
    else
    { // if target is on the right of the current
      if ((cellsArray[current_x][current_y] == 3) || (cellsArray[current_x][current_y] == 6) || (cellsArray[current_x][current_y] == 7) || (cellsArray[current_x][current_y] == 9) || (cellsArray[current_x][current_y] == 11) || (cellsArray[current_x][current_y] == 12) || (cellsArray[current_x][current_y] == 13))
        return false;
      else
        return true;
    }
  }
}



/**=============================================================================================
 * @Fn             - getSurroungings
 * @brief          - Computes the coordinates of neighboring cells in four cardinal directions
 * @param [in]     - current_x: The x-coordinate of the current cell.
 * @param [in]     - current_y: The y-coordinate of the current cell.
 * @param [out]    - north_x: A pointer to store the x-coordinate of the cell to the north.
 * @param [out]    - north_y: A pointer to store the y-coordinate of the cell to the north.
 * @param [out]    - east_x: A pointer to store the x-coordinate of the cell to the east.
 * @param [out]    - east_y: A pointer to store the y-coordinate of the cell to the east.
 * @param [out]    - south_x: A pointer to store the x-coordinate of the cell to the south.
 * @param [out]    - south_y: A pointer to store the y-coordinate of the cell to the south.
 * @param [out]    - west_x: A pointer to store the x-coordinate of the cell to the west.
 * @param [out]    - west_y: A pointer to store the y-coordinate of the cell to the west.
 * @retval         - None
 * Note            - Coordinates are set to -1 when they would be out of bounds (beyond 15x15 grid)
 **/



void getSurroungings(int current_x, int current_y, int *north_x, int *north_y, int *east_x, int *east_y, int *south_x, int *south_y, int *west_x, int *west_y)
{
  if ((current_x + 1) >= 16)
    *east_x = -1;
  else
    *east_x = current_x + 1;

  *north_x = current_x;
  *east_y = current_y;

  if ((current_y + 1) >= 16)
    *north_y = -1;
  else
    *north_y = current_y + 1;

  *south_x = current_x;
  *south_y = current_y - 1;
  *west_x = current_x - 1;
  *west_y = current_y;
}



/**===================================================================================================
 * @Fn             - isIncrementConsistent
 * @brief          - Checks if the value increment in the current cell is consistent with its accessible neighbors
 * @param [in]     - current_x: The x-coordinate of the current cell.
 * @param [in]     - current_y: The y-coordinate of the current cell.
 * @retval         - bool: True if the increment is consistent, False otherwise.
 */



bool isIncrementConsistent(int current_x, int current_y)
{
  int north_X=0, north_Y=0, east_X=0, east_Y=0, south_X=0, south_Y=0, west_X=0, west_Y=0;
  getSurroungings(current_x, current_y, &north_X, &north_Y, &east_X, &east_Y, &south_X, &south_Y, &west_X, &west_Y);

  int curentValue = floodArray[current_x][current_y];
  int minValues[4] = {1000, 1000, 1000, 1000};
  int minCounts = 0;

  if ((north_X >= 0) && (north_Y >= 0) && isAccessible(current_x, current_y, north_X, north_Y))
    minValues[FORWARD] = floodArray[north_X][north_Y];
  if ((east_X >= 0) && (east_Y >= 0) && isAccessible(current_x, current_y, east_X, east_Y))
    minValues[RIGHT] = floodArray[east_X][east_Y];
  if ((south_X >= 0) && (south_Y >= 0) && isAccessible(current_x, current_y, south_X, south_Y))
    minValues[BACKWARD] = floodArray[south_X][south_Y];
  if ((west_X >= 0) && (west_Y >= 0) && isAccessible(current_x, current_y, west_X, west_Y))
    minValues[LEFT] = floodArray[west_X][west_Y];


  if(isAccessible(current_x, current_y, north_X, north_Y))
    log("North Accessible");
  else
    log("North Unaccessible");



  for (int i = 0; i < 4; i++)
  {
    if ((minValues[i] == (curentValue - 1)) && (minValues[i] != 1000))
      minCounts++;
  }


  if (minCounts > 0)
    return true;
  else
    return false;
}



/**========================================================================================================

 * @Fn             - makeCellConsistent

 * @brief          - Ensures the cell's value is consistent with the minimum value among accessible neighbors

 * @param [in]     - current_x: The x-coordinate of the current cell.

 * @param [in]     - current_y: The y-coordinate of the current cell.

 * @retval         - None

 */



void makeCellConsistent(int current_x, int current_y)
{
  int north_X, north_Y, east_X, east_Y, south_X, south_Y, west_X, west_Y;
  getSurroungings(current_x, current_y, &north_X, &north_Y, &east_X, &east_Y, &south_X, &south_Y, &west_X, &west_Y);

  int currentValue = floodArray[current_x][current_y];
  int minValues[4] = {1000, 1000, 1000, 1000}; // Initialize with a high value.

  if (north_X >= 0 && north_Y >= 0 && isAccessible(current_x, current_y, north_X, north_Y))
    minValues[FORWARD] = floodArray[north_X][north_Y];
  if (east_X >= 0 && east_Y >= 0 && isAccessible(current_x, current_y, east_X, east_Y))
    minValues[RIGHT] = floodArray[east_X][east_Y];
  if (south_X >= 0 && south_Y >= 0 && isAccessible(current_x, current_y, south_X, south_Y))
    minValues[BACKWARD] = floodArray[south_X][south_Y];
  if (west_X >= 0 && west_Y >= 0 && isAccessible(current_x, current_y, west_X, west_Y))
    minValues[LEFT] = floodArray[west_X][west_Y];

  int minimalValue = 1000;

  for (int i = 0; i < 4; i++)
  {
    if (minValues[i] < minimalValue)
      minimalValue = minValues[i];
  }
  log(std::to_string(minimalValue));


  if (minimalValue != 1000){
    log("I have updated floodArray");
    floodArray[current_x][current_y] = minimalValue + 1;
  }
}



/**=====================================================================================
 * @Fn          - floodFillUsingStack
 * @brief Perform flood-fill algorithm using a stack-based approach.
 *
 * This function fills a region of connected cells in the `flood` matrix using a stack-based
 * flood-fill algorithm. It updates the values of cells while ensuring consistency based on
 * certain conditions.
 *
 * @param[in]   - start_x The x-coordinate of the starting cell.
 * @param[in]   - start_y The y-coordinate of the starting cell.
 * @param[in]   - previous_x The x-coordinate of the previous cell.
 * @param[in]   - previous_y The y-coordinate of the previous cell.
 *
 * @return None.
 */




bool visited[16][16] = {false}; // Initialize a visited array to keep track of visited cells





void floodFillUsingQueue(int start_x, int start_y, int previous_x, int previous_y)
{
    int north_X, north_Y, east_X, east_Y, south_X, south_Y, west_X, west_Y;

    std::queue<int> cellQueue;
    cellQueue.push(start_x);
    cellQueue.push(start_y);

    while (!cellQueue.empty())
    {
        int current_X = cellQueue.front();
        cellQueue.pop();
        int current_Y = cellQueue.front();
        cellQueue.pop();

        // Check if the current cell is already visited
        if (visited[current_Y][current_X]) {
            continue; // Skip this cell
        }

        // Mark the current cell as visited
        visited[current_Y][current_X] = true;

        // Check if the current cell is incrementally consistent with its neighbors
        if (!isIncrementConsistent(current_X, current_Y))
        {
            log("Not Consistent");
            // If not consistent, make it consistent and increment its value
            makeCellConsistent(current_X, current_Y);

            getSurroungings(current_X, current_Y, &north_X, &north_Y, &east_X, &east_Y, &south_X, &south_Y, &west_X, &west_Y);



            int neighborsX[] = {north_X, east_X, south_X, west_X};
            int neighborsY[] = {north_Y, east_Y, south_Y, west_Y};

            for (int i = 0; i < 4; i++)
            {
                int neighborX = neighborsX[i];
                int neighborY = neighborsY[i];

                if (neighborX >= 0 && neighborY >= 0 && isAccessible(current_X, current_Y, neighborX, neighborY))
                {
                    cellQueue.push(neighborX);
                    cellQueue.push(neighborY);
                }
            }
        }else{
          log("Consistent");
        }
    }
}





/**=====================================================================
 * @fn          - whereToMove
 * @brief       - Determines the optimal direction for the robot to move based on flood values and orientation.
 * @param[in]   - current_x: X-coordinate of the current cell
 * @param[in]   - current_y: Y-coordinate of the current cell
 * @param[in]   - previous_x: X-coordinate of the previous cell
 * @param[in]   - previous_y: Y-coordinate of the previous cell
 * @param[in]   - orient: Orientation of the robot (0 to 3)
 * @retvzl      - Char representing the direction to move: 'F' (Forward), 'L' (Left), 'R' (Right), or 'B' (Back)
 * @note        - The function considers flood values and previous movements to determine the best direction.
 *=======================================================================
 */





char whereToMove(int current_x, int current_y, int previous_x, int previous_y, int orient)
{
    int north_X, north_Y, east_X, east_Y, south_X, south_Y, west_X, west_Y;
    getSurroungings(current_x, current_y, &north_X, &north_Y, &east_X, &east_Y, &south_X, &south_Y, &west_X, &west_Y);

    int minValue = 1000; // Initialize with a high value
    int minCell = -1;       // Initialize to an invalid value
    int previous = -1;
    int AccessiblePathsNum = 0;

    int accessibleNeighbors[4] = {-1, -1, -1, -1}; // Initialize to invalid values


    if ((south_X == previous_x) && (south_Y == previous_y))
    {
      previous = BACKWARD;
    }else if ((north_X == previous_x) && (north_Y == previous_y)){
      previous = FORWARD;
    }else if ((east_X == previous_x) && (east_Y == previous_y)){
      previous = RIGHT;
    }else if ((west_X == previous_x) && (west_Y == previous_y)){
      previous = LEFT;
    }

    // Check each direction (north, east, south, west)
    for (int i = 0; i < 4; i++)
    {
        int neighborX = 0, neighborY = 0;
        int* currentNeighborX = nullptr;
        int* currentNeighborY = nullptr;

        switch (i)
        {
        case FORWARD:
            currentNeighborX = &north_X;
            currentNeighborY = &north_Y;
            break;
        case RIGHT:
            currentNeighborX = &east_X;
            currentNeighborY = &east_Y;
            break;
        case BACKWARD:
            currentNeighborX = &south_X;
            currentNeighborY = &south_Y;
            break;
        case LEFT:
            currentNeighborX = &west_X;
            currentNeighborY = &west_Y;
            break;
        }

        if (*currentNeighborX >= 0 && *currentNeighborY >= 0 && isAccessible(current_x, current_y, *currentNeighborX, *currentNeighborY))
        {
            AccessiblePathsNum++;
            accessibleNeighbors[i] = floodArray[*currentNeighborX][*currentNeighborY];

            // if (orient == i || (orient == (i + 2) % 4))
            // {
            //     // If the direction aligns with current orientation or is opposite, return 'F'
            //     return 'F';
            // }
        }
    }

    log("Accessible Path: ");
    log(std::to_string(AccessiblePathsNum));



    // Find the minimum value among accessible neighbors
    for (int i = 0; i < 4; i++)
    {
        // if (accessibleNeighbors[i] != -1 && accessibleNeighbors[i] < minValue)
        // {
        //     minValue = accessibleNeighbors[i];
        //     minCell = i;
        // }



        if (accessibleNeighbors[i] != -1 && accessibleNeighbors[i] < minValue)
        {
          if (AccessiblePathsNum == 1){
            minValue = accessibleNeighbors[i];
            minCell = i;
          }else{
            if(i==previous) {
              continue;
            }else{
              minValue = accessibleNeighbors[i];
              minCell = i;    
            }
          }
        }

        // if (minCell != -1 && minCell != previous)
        // {
        //     return (minCell == orient) ? 'F' : (minCell == (orient + 1) % 4) ? 'R' : (minCell == (orient + 3) % 4) ? 'L' : 'B';
        // }
    }



  if (minCell == orient)
    return 'F';
  else if ((minCell == (orient - 1) % 4) || (minCell == (orient + 3) % 4))
    return 'L';
  else if ((minCell == (orient + 1) % 4) || (minCell == (orient - 3) % 4))
    return 'R';
  else
    return 'B';

    // If there are no accessible neighbors or no better direction found, return 'B'
    // return 'B';
}




/**=====================================================================
 * @fn          - displayFlood
 * @brief       - Displays the flood values matrix for visualization.
 * @param       - None
 * @retval      - None
 * @note        - This function is used to visualize the flood values matrix, which represents the exploration progress or path cost in a maze.
 *=======================================================================
 */



void displayFlood(void)

{

  for(int i=0;i<16;i++)

  {

    for(int j=0;j<16;j++)

    {

      API::setText(i,j,std::to_string(floodArray[i][j]));

    }

  }

}



void displayCellsArray(void)

{

  for(int i=0;i<16;i++)

  {

    for(int j=0;j<16;j++)

    {

      API::setText(i,j,std::to_string(cellsArray[i][j]));

    }

  }

}



int current_x = 0, current_y = 0, previous_x = 0, previous_y = 0, orient = FORWARD;
char Direction = 0;
bool left=false, right=false, forward=false;


int main(int argc, char *argv[])
{
  API::setColor(0, 0, 'G');
  API::setText(0, 0, "abc");

  while (true)
  {
    left = API::wallLeft();

    if(left)
      log("Wall Left");

    right = API::wallRight();

    if(right)
      log("Wall Right");

    forward = API::wallFront();

    if(forward)
      log("Wall Front");

    updateCells(current_x, current_y, orient, left, right, forward);



    if (floodArray[current_x][current_y] != 0)
    {
      floodFillUsingQueue(current_x, current_y,previous_x,previous_y);
    }
    else
    {
      while(true);
    }


      Direction = whereToMove(current_x, current_y, previous_x, previous_y, orient);

      std::string s(1, Direction);
      log(s);
      

      if (Direction == 'L')
      {
        API::turnLeft();
        orient = orientation(orient, 'L');
      }
      else if (Direction == 'R')
      {
        API::turnRight();
        orient = orientation(orient, 'R');
      }
      else if (Direction == 'B')
      {
        API::turnLeft();
        orient = orientation(orient, 'L');
        API::turnLeft();
        orient = orientation(orient, 'L');
      }





      log("moveForwad");
      API::moveForward();
      previous_x = current_x;
      previous_y = current_y;

      displayFlood();
      // displayCellsArray();


      // log(std::to_string(current_x));
      // log(std::to_string(current_y));
      updateCoordinates(orient, &current_x, &current_y);



  }

  return 0;

}
