#ifndef HUFFMAN_DECOMPRESSOR
#define HUFFMAN_DECOMPRESSOR

#include <iostream> //cout cin
#include <fstream>  //CreateHuffmanMap
#include <map>      //table (char/code)
#include <iomanip>  //setw setprecision
#include <string>   //string class
#include "Nodes.hpp"

#define BYTE_SIZE 1 << 8 

typedef std::map<uint8_t, std::string> HuffCode;
typedef std::map<std::string, char> HuffDeCode;


class HuffmanDecompressor
{
    //
    const PNode* root;
    int* f;
    HuffCode HuffCodeTable;
    //
    HuffDeCode HuffDeCodeTable;
    std::string file;
    int totalSymbols;
    //
    PNode* GenHuffmanTree(); //create tree
    void GenHuffmanCode(const PNode* n, const std::string c); //fill HuffCodeTable
    //
    void FillHuffmanFreq();
    void fillHuffDeCodeTable();
    std::ifstream::pos_type FileSize(const char* filename);

public:
    HuffmanDecompressor(const char* m); 
};

#endif