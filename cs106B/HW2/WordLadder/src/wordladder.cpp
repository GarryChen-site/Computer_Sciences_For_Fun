// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "filelib.h"

using namespace std;

//constant declerations for further editing
const string INTRO = "Welcome to CS 106B Word Ladder.\n"
                     "Please give me two English words, and I will change the\n"
                     "first into the second by changing one letter at a time.\n\n";
const string FILE_PROMPT = "Dictionary file name? ";
const string WORD1_PROMPT = "\nWord #1 (or Enter to quit): ";
const string WORD2_PROMPT = "Word #2 (or Enter to quit): ";
const string LADDER_DISPLAY = "A ladder from back to :\n";
const string LADDER_NOT_FOUND = "No word ladder found from back to .\n";
const string WORD_LENGTH_ERROR = "The two words must be the same length.\n";
const string NOT_FOUND_ERROR = "The two words must be found in the dictionary.\n";
const string SAME_WORD_ERROR = "The two words must be different.\n";
const string FILE_ERROR = "Unable to open that file.  Try again.\n";
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

bool checkWords(Lexicon& words, string& word1, string& word2);
Lexicon getLexiconFromFile(string& file);
bool getWords(Lexicon &englishWords, string &word1, string &word2);

int main() {



    cout << "Have a nice day." << endl;
    return 0;
}

bool getWords(Lexicon &words, string &word1, string &word2){
    bool quit;
    do{
        word1 = getLine(WORD1_PROMPT);
        word1 = toLowerCase(word1);
        if(word1 == ""){
            quit = true;
        }
        else{
            word2 = getLine(WORD2_PROMPT);
            word2 = toLowerCase(word2);
            if(word2 == ""){
                quit = true;
            }
        }
    }while(!quit && !checkWords(words, word1, word2));
    return quit;
}

Lexicon getLexiconFromFile(string& file){
    do{
        file = getLine(FILE_PROMPT);
        if(!isFile(file)){
            cout << FILE_ERROR;
        }
    }while(!isFile(file));

    Lexicon words(file);
    return words;
}

bool checkWords(Lexicon& words, string& word1, string& word2){
    if(word1 == word2){
        cout << SAME_WORD_ERROR;
        return false;
    }
    if(word1.length() != word2.length()){
        cout << WORD_LENGTH_ERROR;
        return false;
    }
    if(!words.contains(word1) || !words.contains(word2)){
        cout << NOT_FOUND_ERROR;
        return false;
    }
    return true;
}