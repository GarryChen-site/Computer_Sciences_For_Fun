// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "pqueue.h"

MyMap buildFrequencyTable(istream& input) {
    MyMap freqTable;   // this is just a placeholder so it will compile
    int byte = input.get();
    while(byte != -1) {
        if(freqTable.containsKey(byte)) {
            freqTable.put(byte, freqTable.get(byte) + 1);
        } else {
            freqTable.put(byte, 1);
        }
        byte = input.get();
    }
    freqTable.put(PSEUDO_EOF, 1);
    return freqTable;   
}

HuffmanNode* buildEncodingTree(const MyMap& freqTable) {
    PriorityQueue<HuffmanNode*> frequencies;
    for(auto key : freqTable.keys()) {
        HuffmanNode* node = new HuffmanNode(key, freqTable.get(key));
        frequencies.enqueue(node, node->count);
    }
    while(frequencies.size() > 1) {
        HuffmanNode* left = frequencies.dequeue();
        HuffmanNode* right = frequencies.dequeue();
        HuffmanNode* parent = new HuffmanNode(NOT_A_CHAR, left->count + right->count, left, right);
        frequencies.enqueue(parent, parent->count);
    }
    if (frequencies.isEmpty()) {
        return nullptr; 
    }
    return frequencies.dequeue(); 
}

void generateEncodingMap(Map<int, string>& encodingMap, HuffmanNode* node, const string& prefix) {
    if (node == nullptr) {
        return;
    }

    if (node->character != NOT_A_CHAR) {
        encodingMap.put(node->character, prefix);
    }

    generateEncodingMap(encodingMap, node->zero, prefix + "0");
    generateEncodingMap(encodingMap, node->one, prefix + "1");
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    generateEncodingMap(encodingMap, encodingTree, "");
    return encodingMap;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    int byte = input.get();
    while(byte != -1) {
        string binaryCode = encodingMap.get(byte);
        for(char bit : binaryCode) {
            output.writeBit(bit - '0');
        }
        byte = input.get();
    }
    for (int bit: encodingMap.get(PSEUDO_EOF)) {
        output.writeBit(bit - '0');
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
