// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include <simpio.h>
#include "bogglegui.h"

const int SMALL_GUI_DIMENSION = 4;

void setUpGame(Boggle& game, const string& boardText);
void setUpGUI();
void fillGameBoardGUI(Boggle& game, const string& boardText);
void playHumanTurn(Boggle& game);
void playComputerTurn(Boggle& game);
void displayScores(Boggle& game);
string getBoardText();
bool isBoardTextValid(const string& boardText);

void playOneGame(Lexicon& dictionary) {
    setUpGUI();
    string boardText = getBoardText();
    Boggle game(dictionary, boardText);
    fillGameBoardGUI(game, boardText);
    playHumanTurn(game);
    playComputerTurn(game);
    displayScores(game);
}

void setUpGUI() {
    if(!BoggleGUI::isInitialized()) {
        BoggleGUI::initialize(SMALL_GUI_DIMENSION, SMALL_GUI_DIMENSION);
    } else {
        BoggleGUI::reset();
    }
}

void fillGameBoardGUI(Boggle& game, const string& boardText) {
    if (boardText != "") {
        BoggleGUI::labelAllCubes(toUpperCase(boardText));
    } else {
        for (int r = 0; r < game.getDimension(); r++) {
            for (int c = 0; c < game.getDimension(); c++) {
                BoggleGUI::labelCube(r, c, stringToChar(toUpperCase(charToString(game.getLetter(r, c)))),false);
            }
        }
    }
}

void setUpGame(Boggle& game, const string& boardText) {
    clearConsole();
    cout << boardText << endl << game << endl
        << "Your words (" << game.getFoundWords().size() << "): " << game.getFoundWords() 
        << endl << "Your score: " << game.getScoreHuman() << endl;
}

void playHumanTurn(Boggle& game){
    clearConsole();
    setUpGame(game, "It's your turn!");
    BoggleGUI::setStatusMessage("It's your turn!");
    string word = toLowerCase(getLine("Type a word (or Enter to stop): "));
    while(word != "") {
        if(!game.checkWord(word)) {
            setUpGame(game, "You must enter an unfound 4+ letter word from the dictionary.");
            BoggleGUI::setStatusMessage("You must enter an unfound 4+ letter word from the dictionary.");
        } else if (game.humanWordSearch(word)) {
            setUpGame(game, "You found a new word! \" " + toUpperCase(word) + "\"");
            BoggleGUI::setStatusMessage("You found a new word! \"" + toUpperCase(word) + "\"");
            BoggleGUI::recordWord(toLowerCase(word), BoggleGUI::HUMAN);
            BoggleGUI::setScore(game.getScoreHuman(), BoggleGUI::HUMAN);            
        } else if (word != "") {
            setUpGame(game, "That word is not on the board. Try again.");
            BoggleGUI::setStatusMessage("That word is not on the board. Try again.");
        }
        word = toLowerCase(getLine("Type a word (or Enter to stop): "));
    }
}

void playComputerTurn(Boggle& game) {
    BoggleGUI::clearHighlighting();
    Set<string> computerWords = game.computerWordSearch();
    cout << "\nIt's my turn!\nMy words (" << computerWords.size() << "): " << computerWords
         << "\nMy score: " <<  game.getScoreComputer() << endl;
    BoggleGUI::setStatusMessage("It's my turn!");
    for (string word: computerWords) {
        BoggleGUI::recordWord(toLowerCase(word), BoggleGUI::COMPUTER);
    }
    BoggleGUI::setScore(game.getScoreComputer(), BoggleGUI::COMPUTER);    
}

void displayScores(Boggle& game) {
    if (game.getScoreComputer() > game.getScoreHuman()) {
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!\n";
        BoggleGUI::setStatusMessage("Ha ha ha, I destroyed you. Better luck next time, puny human!");
    } else {
        cout << "WOW, you defeated me! Congratulations!\n";
        BoggleGUI::setStatusMessage("WOW, you defeated me! Congratulations!");
    }    
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