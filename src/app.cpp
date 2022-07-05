#include "app.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

#define SIZE    40
#define WIDTH   800
#define HEIGHT  800

void initializeBoard(std::vector<std::vector<int>> &board);
void printBoard(const std::vector<std::vector<int>> &board);
int countNeighbors(std::vector<std::vector<int>> arr, int row, int col);
std::vector<std::vector<int>> computeGeneration(std::vector<std::vector<int>> &board);

 std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE)); //we initialize a board filled with 0s

void App::setup() {
    // load fonts and images here
    initializeBoard(board);
}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(1,1,1,1));
    g.stroke(glm::vec4(0, 0,0, 1.0f));
    g.strokeWeight(1);
    g.noFill();
    int w = WIDTH/SIZE;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (board[i][j] == 1){
                g.push();
                g.fill(glm::vec4(0,0,0,1));
                g.rect(i*w, j*w,w,w);
                g.pop();
            } else{
                g.rect(i*w, j*w,w,w);
            }  
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    board = computeGeneration(board);
}

void App::keyPressed(int key){
    if(key == 32){
        initializeBoard(board);
    }
}

void initializeBoard(std::vector<std::vector<int>> &board){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 100); // define the range

    std::vector< std::vector<int> >::iterator row; 
    std::vector<int>::iterator col;


     for (row = board.begin(); row != board.end(); ++row)
    { 
         for (col = row->begin(); col != row->end(); ++col)
         {
            int value = distr(gen);
            if (value > 65){
                *col = 1;
            } else {
                *col = 0;
            }
         }
         std::cout << std::endl;
    }
}

void printBoard(const std::vector<std::vector<int>> &board){
    std::vector< std::vector<int> >::const_iterator row; 
    std::vector<int>::const_iterator col; 
    for (row = board.begin(); row != board.end(); ++row)
    { 
         for (col = row->begin(); col != row->end(); ++col)
         {
            //std::cout << *col;
            if (*col == 1){
                std::cout << "#";
            } else {
                std::cout << " ";
            }
         }
         std::cout << std::endl;
    }
}

std::vector<std::vector<int>> computeGeneration(std::vector<std::vector<int>> &board){
    std::vector<std::vector<int>> temp(SIZE, std::vector<int>(SIZE));

    std::vector< std::vector<int> >::const_iterator row; 
    std::vector<int>::const_iterator col; 
    int i = 0, j = 0;
    for (row = board.begin(); row != board.end(); ++row, ++i)
    { 
        for (col = row->begin(); col != row->end(); ++col, ++j)
        {
            int count = countNeighbors(board, i,j);
            if (*col == 1 && (count < 2 || count > 3)){
                temp[i][j] = 0;
            } else if (*col == 0 && count == 3){
                temp[i][j] = 1;
            }
        }
        j = 0;
    }
    return temp;
}

int countNeighbors(std::vector<std::vector<int>> arr, int row, int col){
    int count = 0;
    for (int i = -1; i < 2; ++i){
        for (int j = -1; j < 2; ++j){
            int indexI = (row + i) % arr.size();
            int indexJ = (col + j) % arr.size();
            if (i == 0 && j == 0) continue;
            if (arr[indexI][indexJ] == 1){
                ++count;
            } 
        }
    }
    return count;
}