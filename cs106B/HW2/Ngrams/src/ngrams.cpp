// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include "map.h"

using namespace std;

//constant declerations for further editing
const string INTRO = "Welcome to CS 106B Random Writer ('N-Grams').\n"
                     "This program makes random text based on a document.\n"
                     "Give me an input file and an 'N' value for groups\n"
                     "of words, and I'll create random text for you.\n\n";
const string PROMPT_FILE = "Input file name? ";
const string PROMPT_N = "Value of N? ";
const string PROMPT_RANDOM_WORD_NUMBER = "# of random words to generate (0 to quit)? ";
const string N_ERROR = "N must be 2 or greater.\n";
const string RANDOM_WORD_NUMBER_ERROR = "Must be at least 4 words.\n\n";
const string FILE_ERROR = "Unable to open that file.  Try again.\n";

void promptFile(string &file);
void promptN(int &N);
void promptRandomWordNumber(int &randomWordNumber);
Vector<string> getWords(string &file);
Map<Vector<string>, Vector<string>> getNGramMap(Vector<string> &words, int &N);
void printVector(Vector<string> &vec);
void printRandomText(Map<Vector<string>, Vector<string>> &NGramMap, int &randomWordNumber, int &N);

int main() {
    cout << INTRO;
    string file;
    promptFile(file);
    Vector<string> words = getWords(file);
    int N;
    promptN(N);
    auto NGramMap = getNGramMap(words, N);
    cout << endl;
    int randomWordNumber;
    do{
        promptRandomWordNumber(randomWordNumber);
        if(randomWordNumber != 0){
            cout << endl;
            printRandomText(NGramMap, randomWordNumber, N);
            cout << endl;
        }
    }while(randomWordNumber != 0);
    cout << "Exiting." << endl;
    return 0;
}


void promptFile(string& file){
    do{
        file = getLine(PROMPT_FILE);
        if(!isFile(file)){
            cout << FILE_ERROR;
        }
    }while(!isFile(file));
}

void promptN(int& N){
    do{
        N = getInteger(PROMPT_N);
        if(N < 2){
            cout << N_ERROR;
        }
    }while(N < 2);
}

void promptRandomWordNumber(int& randomWordNumber){
    do{
        randomWordNumber = getInteger(PROMPT_RANDOM_WORD_NUMBER);
        if(randomWordNumber != 0 && randomWordNumber < 4){
            cout << RANDOM_WORD_NUMBER_ERROR;
        }
    }while(randomWordNumber != 0 && randomWordNumber < 4);
}

Vector<string> getWords(string &file){
    ifstream input;
    openFile(input, file);
    Vector<string> words;
    string word;
    while(input >> word){
        words.add(word);
    }
    return words;
}


Map<Vector<string>, Vector<string>> getNGramMap(Vector<string> &words, int &N){
    Map<Vector<string>, Vector<string>> NGramMap;
    Vector<string> window;
    Vector<string> values;
    for (int i = 0; i < words.size(); i++) {
        for (int j = i; j < i + N - 1; j++) {
            if(j >= words.size()) { // wrap around
                window.add(words.get(j % words.size()));
            }
            else {
                window.add(words.get(j));
            }
        }
        if (NGramMap.containsKey(window)) {
            values = NGramMap.get(window);
        }
        else {
            values.clear();
        }
        if( i + N - 1 >= words.size()) { // wrap around
            values.add(words.get((i + N - 1) % words.size()));
            NGramMap.put(window, values);
        }
        else {
            values.add(words.get(i + N - 1));
            NGramMap.put(window, values);
        }
        window.clear();
    }
    return NGramMap;
}

void printVector(Vector<string> &vec) {
    for (string word: vec) {
        cout << word << " ";
    }
}

void printRandomText(Map<Vector<string>, Vector<string>> &NGramMap, int &randomWordNumber, int &N) {
    Vector<string> vec = NGramMap.keys().get(randomInteger(0, NGramMap.keys().size() - 1));
    cout << "... ";
    printVector(vec);
    string value;
    for (int i = N - 1; i < randomWordNumber; i++) {
        value = NGramMap.get(vec).get(randomInteger(0, NGramMap.get(vec).size() - 1));
        cout << value << " ";
        vec.remove(0);
        vec.add(value);
    }
    cout << "..." << endl;
}