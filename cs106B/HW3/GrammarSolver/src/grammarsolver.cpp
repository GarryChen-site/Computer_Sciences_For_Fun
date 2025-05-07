/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "include/hashmap.h"
#include <vector>

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

void grammarGenerate(istream& input, string symbol, HashMap<string, Vector<string>>& BNFMap, string& element) {
    if(!BNFMap.containsKey(symbol)) {
        element += " " + trim(symbol);
    } else {
        auto rules = BNFMap.get(symbol);
        string rule = rules[randomInteger(0, rules.size() - 1)];
        rule = trim(rule);
        auto ruleSplit = stringSplit(rule, " ");
        for(auto curr : ruleSplit) {
            grammarGenerate(input, trim(curr), BNFMap, element);
        }
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

    Vector<string> res;

    for(int i = 0; i < times; i++) {
        string element = "";
        grammarGenerate(input, symbol, BNFMap, element);
        res.add(element);
    }
    return res;
}
