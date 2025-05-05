/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "hashmap.h"

using namespace std;

void generateMapFromFile(istream& input, HashMap<string, Vector<string>>& BNFMap) {
   string line;
   while(getline(input, line)) {
    auto firstSplit = stringSplit(line, "::=");
    auto nonTerminal = trim(firstSplit[0]);
    auto rules = stringSplit(firstSplit[1], "|");
    BNFMap.put(nonTerminal, rules);
   } 
}

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    HashMap<string, Vector<string>> BNFMap;
    generateMapFromFile(input, BNFMap);

    return {};           // This is only here so it will compile
}
