#ifndef HUFFMAN_COMPRESSOR
#define HUFFMAN_COMPRESSOR

#include <iostream> //cout cin
#include <fstream>  //CreateHuffmanMap
#include <vector>   //priority_queue overload
#include <queue>    //priority_queue
#include <map>      //table (char/code)
#include <iomanip>  //setw setprecision
#include <string>   //string class
#include <cmath>    //log2
#include <cstdio>   //printf
#include <cstdint>  //uint8_t type
#include "Nodes.hpp"

#define BYTE_SIZE 1 << 8 

typedef std::map<uint8_t, std::string> HuffCode;

class HuffmanCompressor
{
    const PNode* root;
    HuffCode HuffCodeTable;
    std::string file;
    char* msg;
    int msgSize;

    const int* GetFrequency(); //get frequency
    PNode* GenHuffmanTree(const int* freq); //create tree
    void GenHuffmanCode(const PNode* n, const std::string codet); //fill HuffCodeTable
    void CreateHuffmanMap(); //create map used by decompressor
    std::ifstream::pos_type FileSize(const char* filename);
    std::ifstream::pos_type FileSize(std::string filename);
public:
    
    HuffmanCompressor(const char* filename); //constructor need file
    void PrintHuffmanCode(); //print the table
    void PrintEncodedMessage(); //print bit-bit
    void Compress(); //generate bin file
    void PrintStatistics();
};

#endif