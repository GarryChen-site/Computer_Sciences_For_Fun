// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "shuffle.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    dimension = 4;

    gameBoard.resize(dimension, dimension);
    if (boardText == "") {
        shuffle(CUBES, 16);
        for (int r = 0; r < gameBoard.numRows(); r++) {
            for (int c = 0; c < gameBoard.numCols(); c++) {
                gameBoard[r][c] = stringToChar(toLowerCase(charToString(CUBES[r * dimension + c][randomInteger(0, 5)])));
            }
        }
    } else {
        for (int r = 0; r < gameBoard.numRows(); r++) {
            for (int c = 0; c < gameBoard.numCols(); c++) {
                gameBoard[r][c] = boardText[r * dimension + c];
            }
        }
    }

}

char Boggle::getLetter(int row, int col) {
    // TODO: implement
    return '?';   // remove this
}

bool Boggle::checkWord(string word) {
    // TODO: implement
    return false;   // remove this
}

bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    return false;   // remove this
}

int Boggle::getScoreHuman() {
    // TODO: implement
    return 0;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
