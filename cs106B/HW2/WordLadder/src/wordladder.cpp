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
#include "hashset.h"
#include "queue.h"

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
Stack<string> findShortestPath(Lexicon& words, string& word1, string& word2);
HashSet<string> findNeighbors(Lexicon& words, string word);
void displayLadder(Stack<string>& stack, string& word1, string& word2);

int main() {
    cout << INTRO;
    string file;
    Lexicon englishWords = getLexiconFromFile(file);
    string word1, word2;
    bool quit;
    do{
        quit = getWords(englishWords, word1, word2);
        if(!quit){
            Stack<string> ladder = findShortestPath(englishWords, word1, word2);
            displayLadder(ladder, word1, word2);
        }
    }while(!quit);

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

/**
 * Generates and returns a Lexicon object from a file.
 */
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


void displayLadder(Stack<string>& stack, string& word1, string& word2){
    if (stack.isEmpty()) {
        cout << LADDER_NOT_FOUND.substr(0, 26) + word1 + LADDER_NOT_FOUND.substr(25, 9)
                + word2 + LADDER_NOT_FOUND.substr(LADDER_NOT_FOUND.length() - 2);
    }
    else {
        cout << LADDER_DISPLAY.substr(0, 14) + word2 + LADDER_DISPLAY.substr(13, 9)
                + word1 + LADDER_DISPLAY.substr(LADDER_DISPLAY.length() - 2);
        while (!stack.isEmpty()) {
            cout << stack.pop() << " ";
        }
        cout << endl;
    }
}


HashSet<string> findNeighbors(Lexicon& words, string word){
    HashSet<string> neighbors;
    string copy = word;
    for(int i = 0; i < word.length(); i++) {
        for (int j = 0; j < ALPHABET.length(); j++) {
            copy[i] = ALPHABET[j];
            if(words.contains(copy)){
                neighbors.add(copy);
            }
        }
        copy = word;
    }    
    return neighbors;
}


Stack<string> findShortestPath(Lexicon& words, string& word1, string& word2){
    Queue<Stack<string>> ladders = {{word1}};
    Stack<string> ladder;
    HashSet<string> used = {word1};
    while(!ladders.isEmpty()) {
        ladder = ladders.dequeue();
        if(ladder.peek() == word2) {
            return ladder;
        }
        for(string neighbor: findNeighbors(words, ladder.peek())) {
            if(!used.contains(neighbor)) {
                Stack<string> copyLadder = ladder;
                copyLadder.push(neighbor);
                used.add(neighbor);
                ladders.enqueue(copyLadder);
            }
        }
    }    
    return {};
}