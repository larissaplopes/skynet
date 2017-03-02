#include "HuffmanDecompressor.hpp"

PNode* HuffmanDecompressor::GenHuffmanTree()
{
    std::priority_queue<PNode*, std::vector<PNode*>, min_heap> N; //nodes

    for (int i = 0; i < BYTE_SIZE; i++) //leaf
        if (f[i]) N.push(new LNode(f[i], char(i)));

    while (N.size() > 1) { //simple
        PNode* r = N.top(); N.pop();
        PNode* l = N.top(); N.pop();
        N.push(new SNode(r, l));
    }

    return N.top();
}

void HuffmanDecompressor::GenHuffmanCode(const PNode* n, const std::string code)
{
    //dynamic comparison (similar to instanceof operator java)
    if (const LNode* leaf = dynamic_cast<const LNode*>(n)) { //leaf node
        HuffCodeTable[leaf->c] = code.empty() ? "0" : code; //solve 1 symbol
    } else if (const SNode* simple = dynamic_cast<const SNode*>(n)) { //simple node
        GenHuffmanCode(simple->left, code + '0');
        GenHuffmanCode(simple->right, code + '1');
    } else {
        return; 
    }
}

void HuffmanDecompressor::FillHuffmanFreq()
{
    std::ifstream in("Huffman.freq", std::ios::in);
    in >> this->totalSymbols;
    
    int i, v;
    while (in >> i >> v) this->f[i] = v;
}

std::ifstream::pos_type HuffmanDecompressor::FileSize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

void HuffmanDecompressor::fillHuffDeCodeTable()
{
    HuffDeCodeTable.clear();
    for (auto it : HuffCodeTable)
        HuffDeCodeTable[it.second] = it.first;
}

HuffmanDecompressor::HuffmanDecompressor(const char* m)
{
    file = m;
    std::ifstream input(file+".compress", std::fstream::binary);
    std::ofstream output(file+".decompress", std::fstream::binary);

    char c;
    int count = 0;
    std::string tmp;

    FillHuffmanFreq();
    this->root = GenHuffmanTree();
    GenHuffmanCode(this->root, "");
    fillHuffDeCodeTable();

    while (input.read((char*)&c, sizeof(char))) 
        for (int i = 0; i < 8; i++) {
            tmp += ((c & (1 << (7 - i))) ? "1" : "0");
            if (HuffDeCodeTable.find(tmp) != HuffDeCodeTable.end()) {
                output << HuffDeCodeTable[tmp];
                count++;
                if(count == this->totalSymbols) 
                    break;
                this->f[(uint8_t)HuffDeCodeTable[tmp]]--;
                this->root = GenHuffmanTree();
                HuffCodeTable.clear();
                GenHuffmanCode(this->root, "");
                fillHuffDeCodeTable();
                tmp.clear();
            }
        }
}  
