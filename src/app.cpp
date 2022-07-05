#include "app.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>


//Costants for cell count and resolution
#define SIZE    40
#define WIDTH   800
#define HEIGHT  800

//Redifined vector of vectors as a 2D Vector
typedef std::vector<std::vector<int>> vector2Dint;

//Function declarations
void initializeBoard(vector2Dint &board);
int countNeighbors(vector2Dint arr, int row, int col);
vector2Dint computeGeneration(vector2Dint&board);

//We initialize a board filled with 0s
vector2Dint board(SIZE, std::vector<int>(SIZE)); 

void App::setup() {
    initializeBoard(board);
}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(1,1,1,1));   //Set a white background
    g.stroke(glm::vec4(0, 0,0, 1.0f));  //Lines will be black
    g.strokeWeight(1);                  //Line width
    g.noFill();                         //Don't fill the shapes
    
    /*
    Because we can willfully change the resolution and number of cells, we need a variable to store
    the correct proportiones needed to draw the grid.
    */
    int res = WIDTH/SIZE;                  
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (board[i][j] == 1){
                g.push();   //We push and pop because we only want to change the drawing settings when alive.
                g.fill(glm::vec4(0,0,0,1)); //We would fill with black.
                g.rect(i*res, j*res,res,res);//Rect of same size sides positioned relative to the upper left corner.
                g.pop();
            } else{
                g.rect(i*res, j*res,res,res);//Hollow square.
            }  
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(250)); //Sleep to observe more easily the changes.
    board = computeGeneration(board); //Obtain the new generation.
}


void App::keyPressed(int key){
    if(key == 32){ //If you press the space key, it reinitializes randomly the board.
        initializeBoard(board);
    }
}


void initializeBoard(vector2Dint &board){
    /*
    If we start with a random board, we have to obtain the cells of the initial state
    that will be randomly alive.
    */
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 100); // define the range

    vector2Dint::iterator row; 
    std::vector<int>::iterator col;


     for (row = board.begin(); row != board.end(); ++row)
    { 
         for (col = row->begin(); col != row->end(); ++col)
         {
            int value = distr(gen);
            if (value > 65){    //35% of possibilites of being alive.
                *col = 1;
            } else {
                *col = 0;
            }
         }
         std::cout << std::endl;
    }
}


vector2Dint computeGeneration(vector2Dint &board){
    /*
    We need another Vector2D because we can't change the values of our current board until we have
    checked all cells.
    */
    vector2Dint temp(SIZE, std::vector<int>(SIZE));

    //We instatiate an iterator for the rows and another for each cell of each row.
    vector2Dint::const_iterator row; 
    std::vector<int>::const_iterator col;

    /*
    We need to check every position on the board and compute the new value, which we will store in the
    temporary board. However, as we traverse our Vector2D with iterators, we cannot access the specific 
    position on our temporary vector. In order to circumvent this problem, we set two counters that will
    be incremented every time we step through a column or a row. 
    */
    int i = 0, j = 0; 
    for (row = board.begin(); row != board.end(); ++row, ++i)
    { 
        for (col = row->begin(); col != row->end(); ++col, ++j)
        {
            int vecinity = countNeighbors(board, i,j);
            if (*col == 1 && (vecinity < 2 || vecinity > 3)){   //Rules if alive
                temp[i][j] = 0;
            } else if (*col == 0 && vecinity == 3){             //Rule if dead
                temp[i][j] = 1;
            }
        }
        j = 0;
    }
    return temp;
}

int countNeighbors(vector2Dint arr, int row, int col){
    int count = 0;
    for (int i = -1; i < 2; ++i){
        for (int j = -1; j < 2; ++j){
            /*
            We are checking the 8 adjacent cells(positions) to the one specified in the arguments.
            [y-1,x-1],  [y-1,x],    [y-1,x+1]
            [y,x-1],    [y,x],      [y, x+1]
            [y+1,x-1],  [y+1,x],    [y+1,x+1]
            Because we add and substract, we might access invalid positions (such as -1 or SIZE + 1).
            We can fix it by wrapping the operation with the modulo operator. You can learn more about
            the modulo operator here: https://stackoverflow.com/questions/12556946/how-does-the-modulus-operator-work
            Basically, if we obtain a value over the limit (let SIZE=24) such as 25, if we use the % operator:
            25 % 24 = 1 -> Second position, because we went by the limit by two (End of the vector is SIZE-1)
            -1 % 24 = 23 -> Wraps to the last position.
            You can use the Google calculator for quick access to modulo operations.
            */
            int y = (row + i) % arr.size(); //Named 'y' because it represents the Y axis (rows)
            int x = (col + j) % arr.size(); //Named 'x' because it represents the X axis (columns)
            if (i == 0 && j == 0) continue; //We skip ourselves (the cell pointed by the arguments)
            if (arr[y][x] == 1){            //If the cell is alive, we increment the counter
                ++count;
            } 
        }
    }
    return count;
}