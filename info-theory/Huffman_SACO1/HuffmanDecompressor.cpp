#include "HuffmanDecompressor.hpp"

void HuffmanDecompressor::FillHuffmanMap()
{
    std::ifstream in("Huffman.map", std::ios::in);
    in >> this->totalSymbols;
    
    int v, context;
    std::string code;
    
    while (in >> v) {
        if (v == -1) in >> context;
        else {
            in >> code;
            this->HuffDeCodeTable[context][code] = v;
        }
    }
}

std::ifstream::pos_type HuffmanDecompressor::FileSize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

HuffmanDecompressor::HuffmanDecompressor(const char* m)
{
    file = m;
    FillHuffmanMap();
    std::ifstream input(file+".compress", std::fstream::binary);
    std::ofstream output(file+".decompress", std::fstream::binary);

    char c;
    int count = 0, flag = -1; //flag to first symbol
    uint8_t ctx;
    std::string tmp;

    while (input.read((char*)&c, sizeof(char))) {
        if (flag == -1) {
            flag = 1;
            ctx = (uint8_t) c;
            output << c;
            continue;
        }
        for (int i = 0; i < 8; i++) {
            tmp += ((c & (1 << (7 - i))) ? "1" : "0");
            if (HuffDeCodeTable[ctx].find(tmp) 
                != HuffDeCodeTable[ctx].end()) 
            {
                output << HuffDeCodeTable[ctx][tmp];
                ctx = (uint8_t)HuffDeCodeTable[ctx][tmp];
                tmp.clear();
                count++;
                if(count == this->totalSymbols - 1) 
                    break;
            }
        }
    }
}  