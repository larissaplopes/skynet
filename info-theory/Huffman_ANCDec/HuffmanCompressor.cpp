#include "HuffmanCompressor.hpp"

int* HuffmanCompressor::GetFrequency()
{
    int *F = new int[BYTE_SIZE]{0}; 
    for (int i = 0; i < msgSize; i++) F[(uint8_t)msg[i]]++;
    return F;
}

PNode* HuffmanCompressor::GenHuffmanTree()
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

void HuffmanCompressor::GenHuffmanCode(const PNode* n, const std::string code)
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

void HuffmanCompressor::CreateHuffmanFreq()
{
    std::ofstream out("Huffman.freq", std::ofstream::out);
    out << msgSize << std::endl; //Partial solution cause we can't write bits
    for (int i = 0; i < BYTE_SIZE; i++) 
        out << std::setw(3) << i << " " << std::setw(15) << f[i] << std::endl;
    
    out.close();
}

std::ifstream::pos_type HuffmanCompressor::FileSize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

std::ifstream::pos_type HuffmanCompressor::FileSize(std::string filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

HuffmanCompressor::HuffmanCompressor(const char* filename)
{
    std::ifstream input(filename, std::fstream::in | std::fstream::binary);

    file = filename;
    msgSize = HuffmanCompressor::FileSize(filename);
    msg = new char[msgSize];

    input.read(msg, msgSize);

    this->f = GetFrequency();

    for (int i = 0; i < msgSize - (msgSize == 1 ? 0 : 1); i++) //-1 we now the last symbol
    {
        HuffCodeTable.clear();
        this->root = GenHuffmanTree();
        GenHuffmanCode(this->root, "");
        if (i == 0) 
            this->CreateHuffmanFreq(); //we need first values
        total_info += std::log2((double)(msgSize-i)/f[(uint8_t)msg[i]]);
        msgComp+=HuffCodeTable[msg[i]];
        this->f[(uint8_t)msg[i]]--;
    }

    msgCompSize = msgComp.size();
}    

void HuffmanCompressor::PrintEncodedMessage()
{
    std::cout << msgComp << std::endl;
    std::cout << msgCompSize << " bits. " << msgCompSize/8 + (msgCompSize%8 ? 1 : 0) << " bytes." << std::endl;
}

void HuffmanCompressor::Compress()
{
    //Note: I can't write a single bit directly to a file. 
    //The I/O unit of reading/writing is a byte (8-bits).
    //Idea: Collect bits until you have enough bits to fill 
    //a byte and then write it..
    
    std::ofstream bin(file+".compress", std::ios::out | std::ios::binary);

    while (msgComp.size() % 8 != 0) msgComp += "0";
    char bin_buffer;
    for (int i = 0; i < msgComp.size(); i+=8) {
        bin_buffer &= 0;
        for (int j = 0; j < 8; j++) 
            bin_buffer |= (msgComp[i+j] == '1' ? 1 << (7-j) : 0);
         bin << bin_buffer;
    }
}

void HuffmanCompressor::PrintStatistics()
{
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "| Message            size: " << msgSize << " bytes." << std::endl;
    std::cout << "| Huffman    Freq    size: " << FileSize("Huffman.freq") << " bytes." << std::endl; 
    std::cout << "| Compressed Message size: " << FileSize(file+".compress") << " bytes (" << msgCompSize << " bits)." << std::endl;
    std::cout << "| Economy                : " << (int)msgSize - FileSize("Huffman.freq") - FileSize(file+".compress") << " bytes." << std::endl;
    std::cout << "| Compress         Reason: " << (double)(FileSize("Huffman.freq") + FileSize(file+".compress")) / msgSize << "." << std::endl;
    std::cout << "|------------------------------------------------------" << std::endl;
    std::cout << "| Total       Information: " << total_info << " bits." << std::endl;
    std::cout << "| Entropy                : " << total_info / msgSize << " bits/char." <<  std::endl;
    std::cout << "| Huffman     Performance: " << msgCompSize << " bits." << std::endl;
    std::cout << "| Huffman  Perf  by  char: " << (double)msgCompSize / msgSize << " bits." << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
}