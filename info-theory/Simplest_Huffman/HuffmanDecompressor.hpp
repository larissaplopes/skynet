#ifndef HUFFMAN_COMPRESSOR
#define HUFFMAN_COMPRESSOR

#include <iostream> //cout cin
#include <fstream>  //CreateHuffmanMap
#include <vector>   //priority_queue overload
#include <queue>    //priority_queue
#include <map>      //table (char/code)
#include <iomanip>  //setw
#include <string>   //string class

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
    
    HuffmanDeCompressor(const std::string& m);
    void PrintHuffmanCode();
    void CreateHuffmanMap();
};

#endif