// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include <simpio.h>

const int SMALL_GUI_DIMENSION = 4;

string getBoardText();
bool isBoardTextValid(const string& boardText);

void playOneGame(Lexicon& dictionary) {
    // TODO: implement

}



string getBoardText() {
    if(getYesOrNo("Do you want to generate a random board?")) {
        return "";
    } else {
        string boardText;
        do {
            boardText = toLowerCase(getLine("Type the 16 letters to appear on the board: "));
            if(!isBoardTextValid(boardText)) {
                cout << "That is not a valid 16-letter board string. Try again." << endl;
            }
        }while(!isBoardTextValid(boardText));
        return boardText;
    }
}

bool isBoardTextValid(const string& boardText) {
    if(boardText.length() == SMALL_GUI_DIMENSION * SMALL_GUI_DIMENSION) {
        for (char c : boardText) {
            if(!isalpha(c)) {
                return false;
            }
        }
        return true;
    }
    return false;
}