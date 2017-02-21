#ifndef HUFFMAN_DECOMPRESSOR
#define HUFFMAN_DECOMPRESSOR

#include <iostream> //cout cin
#include <fstream>  //CreateHuffmanMap
#include <map>      //table (char/code)
#include <iomanip>  //setw setprecision
#include <string>   //string class

#define ASCII_SIZE 256 

typedef std::map<std::string, char> HuffDeCode;

class HuffmanDecompressor
{
    int totalSymbols;
    HuffDeCode HuffDeCodeTable;
    void FillHuffmanMap();
    std::ifstream::pos_type FileSize(const char* filename);
public:
    HuffmanDecompressor(const char* m); 
    void PrintHuffmanCode(); 
};

#endif