#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;

//Constant declerations (for further changes)
const string WELCOME_MESSAGE = "Welcome to the CS 106B Game of Life,\n"
                               "a simulation of the lifecycle of a bacteria colony.\n"
                               "Cells (X) live and die by the following rules:\n"
                               "- A cell with 1 or fewer neighbors dies.\n"
                               "- Locations with 2 neighbors remain stable.\n"
                               "- Locations with 3 neighbors will create life.\n"
                               "- A cell with 4 or more neighbors dies.\n\n";
const string PROMPT_FILE = "Grid input file name? ";
const string FILE_ERROR = "Unable to open that file.  Try again.\n";
const string OPTIONS = "Should the simulation wrap around the grid (y/n)? ";
const string MENU = "a)nimate, t)ick, q)uit? ";
const string PROMPT_FRAME_NUMBER = "How many frames? ";
const string ERROR = "Invalid choice; please try again.\n";
const int PAUSE = 50;


void displayGrid(Grid<string> &grid);
void advanceGrid(Grid<string>& grid, bool wrapping);
int countNeighbors(Grid<string>& grid, int row, int col, bool wrapping);

int main() {

    // Displaying the intro welcome message
    cout << WELCOME_MESSAGE;


    cout << "Have a nice Life!" << endl;
    return 0;
}

/**
 * @brief Displays the grid in the console.
 * @param grid The grid to display.
 */
void displayGrid(Grid<string> &grid) {
    for (int r = 0; r < grid.numRows(); r++) {
        for (int c = 0; c < grid.numCols(); c++) {
            cout << grid[r][c];
        }
        cout << endl;
    }
}


void advanceGrid(Grid<string>& grid, bool wrapping){
    Grid<int> counts(grid.numRows(), grid.numCols());
    for(int r = 0; r < grid.numRows(); r++){
        for(int c = 0; c < grid.numCols(); c++){
            counts[r][c] = countNeighbors(grid, r, c, wrapping);
        }
    }
    for (int r = 0; r < grid.numRows(); r++){
        for (int c = 0; c < grid.numCols(); c++) {
            if(counts[r][c] <= 1 || counts[r][c] >= 4) {
                grid.set(r, c, "-");
            }
            else if(counts[r][c] == 3) {
                grid.set(r, c, "X");
            }
        }
    }
    displayGrid(grid);
}


int countNeighbors(Grid<string>& grid, int row, int col, bool wrapping){
    int count = 0;
    if(!wrapping) {
        for(int r = row - 1; r <= row + 1; r++) {
            for(int c = col - 1; c <= col + 1; c++) {
                if(row != r || col != c){
                    if(grid.inBounds(r, c)) {
                        if(grid[r][c] == "X") {
                            count++;
                        }
                    }
                }
            }
        }
    } 
    else {
        int numRows = grid.numRows();
        int numCols = grid.numCols();
        for(int r = row - 1; r <= row + 1; r++){
            for(int c = col - 1; c <= col + 1; c++) {
                if(row != r || col != c) {
                    if(grid.inBounds(r, c)){
                        if(grid[r][c] == "X"){
                            count++;
                        }
                    }
                    else {
                        if((r == -1 || r == numRows) && (c == -1 || c == numCols)) {
                            if(grid[(r + numRows) % numRows][(c + numCols) % numCols] == "X") {
                                count++;
                            }
                        }
                        else if(r == -1 || r == numRows) {
                            if(grid[(r + numRows) % numRows][c] == "X") {
                                count++;
                            }
                        }
                        else if(c == -1 || c == numCols) {
                            if(grid[r][(c + numCols) % numCols] == "X") {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}