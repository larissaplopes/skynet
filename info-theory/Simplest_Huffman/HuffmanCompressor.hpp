#ifndef HUFFMAN_COMPRESSOR
#define HUFFMAN_COMPRESSOR

#include <iostream>
#include <vector> //priority_queue overload
#include <queue>  //priority_queue
#include <map>    //table (char/code)
#include <iomanip> //setw
#include <string>
#include "Nodes.hpp"

#define ASCII_SIZE 256 

typedef std::map<char, std::string> HuffCode;

class HuffmanCompressor
{
    PNode *root;
    HuffCode HuffCodeTable;

    const int* GetFrequency(const std::string& m);
    PNode* GenHuffmanTree(const int* freq);
    void GenHuffmanCode(const PNode* n, const std::string code,
                        HuffCode &out);

public:
    
    HuffmanCompressor(const std::string& m);
    void PrintHuffmanCode();
    void CreateHuffmanMap();
};

#endif