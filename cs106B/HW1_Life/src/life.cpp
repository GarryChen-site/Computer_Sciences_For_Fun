// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

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
const string RANDOM = "(type \"random\" to generate a random pattern) ";
const string FILE_ERROR = "Unable to open that file.  Try again.\n";
const string OPTIONS = "Should the simulation wrap around the grid (y/n)? ";
const string MENU = "a)nimate, t)ick, q)uit? ";
const string PROMPT_FRAME_NUMBER = "How many frames? ";
const string ERROR = "Invalid choice; please try again.\n";
const int PAUSE = 50;

int main() {

    // Displaying the intro welcome message
    cout << WELCOME_MESSAGE;


    cout << "Have a nice Life!" << endl;
    return 0;
}
