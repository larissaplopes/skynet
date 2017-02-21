#include "HuffmanDecompressor.hpp"
#include <bitset>

void HuffmanDecompressor::FillHuffmanMap()
{
    std::ifstream in("Huffman.map", std::ios::in);
    in >> this->totalSymbols;
    
    int v;
    std::string code;
    
    while (in >> v >> code) this->HuffDeCodeTable[code] = v;
}

std::ifstream::pos_type HuffmanDecompressor::FileSize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

HuffmanDecompressor::HuffmanDecompressor(const char* m)
{
    FillHuffmanMap();
    std::ifstream input(m, std::fstream::in | std::fstream::binary);
    std::ofstream output("decompressed.txt", std::fstream::out);

    char c;
    std::string tmp;

    while (input.read((char*)&c, sizeof(char))) 
        for (int i = 0; i < 8; i++) {
            tmp += ((c & (1 << (7 - i))) ? "1" : "0");
            if (HuffDeCodeTable.find(tmp) != HuffDeCodeTable.end()) {
                output << HuffDeCodeTable[tmp];
                tmp.clear();
            }
        }
}  

void HuffmanDecompressor::PrintHuffmanCode()
{
    for (auto it : HuffDeCodeTable) 
        std::cout << it.second << " " << std::setw(30) << it.first << std::endl;
}