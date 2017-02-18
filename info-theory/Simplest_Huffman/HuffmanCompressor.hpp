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
#include "Nodes.hpp"

#define ASCII_SIZE 256 

typedef std::map<char, std::string> HuffCode;

class HuffmanCompressor
{
    const PNode *root;
    HuffCode HuffCodeTable;
    std::string msg;

    const int* GetFrequency(); //get frequency
    PNode* GenHuffmanTree(const int* freq); //create tree
    void GenHuffmanCode(const PNode* n, const std::string codet); //fill HuffCodeTable
    void CreateHuffmanMap(); //create map used by decompressor
    std::ifstream::pos_type FileSize(const char *filename);
public:
    
    HuffmanCompressor(const std::string& m); //constructor need msg (size > 2)
    void PrintHuffmanCode(); //print the table
    void PrintEncodedMessage(); //print bit-bit
    void Compress(); //generate bin file
    void PrintStatistics();
    //TODO GEN STATISTIC
    //msg size
    //huffman map size
    //encoded msg size
    //info total -(sum log2(pbi)) pbi = nbi / n, 
    //entropia , entropia / caractere
    //dados do huffman: comprimento medio e info por bit
    //prob (menor prob -> maior surpresa -> maior info))
    //TODO SHELL CONTROLLER
    //TODO TEST WITH BRAZILIAN DICTIONARY
};

#endif