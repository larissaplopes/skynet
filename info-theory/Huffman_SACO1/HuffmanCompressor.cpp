#include "HuffmanCompressor.hpp"

void HuffmanCompressor::GetFrequency()
{
    F = new int*[BYTE_SIZE]; 
    for (int i = 0; i < BYTE_SIZE; i++)
        F[i] = new int[BYTE_SIZE]{0};
    for (int i = 1; i < msgSize; i++) F[(uint8_t)msg[i-1]][(uint8_t)msg[i]]++; //first symbol only get out
}

PNode* HuffmanCompressor::GenHuffmanTree(const int t)
{
    std::priority_queue<PNode*, std::vector<PNode*>, min_heap> N; //nodes

    for (int i = 0; i < BYTE_SIZE; i++) { //leaf 
        if (F[t][i]) {
            N.push(new LNode(F[t][i], char(i)));
            //std::cout << (char)t << " " <<  F[t][i] << " " << (char)i << std::endl;
        }
    }

    while (N.size() > 1) { //simple
        PNode* r = N.top(); N.pop();
        PNode* l = N.top(); N.pop();
        N.push(new SNode(r, l));
    }

    return (N.empty() ? NULL : N.top());
}

void HuffmanCompressor::GenHuffmanCode(const PNode* n, const std::string code, const int i)
{
    //dynamic comparison (similar to instanceof operator java)
    if (const LNode* leaf = dynamic_cast<const LNode*>(n)) { //leaf node
        HuffCodeTable[i][leaf->c] = code.empty() ? "0" : code; //solve 1 symbol
    } else if (const SNode* simple = dynamic_cast<const SNode*>(n)) { //simple node
        GenHuffmanCode(simple->left, code + '0', i);
        GenHuffmanCode(simple->right, code + '1', i);
    } else {
        return; 
    }
}

void HuffmanCompressor::CreateHuffmanMap()
{
    std::ofstream out("Huffman.map", std::ofstream::out);
    out << msgSize << std::endl; //Partial solution cause we can't write bits
    for (int i = 0; i < BYTE_SIZE; i++) { //for each context 
        out << "-1 " << i << std::endl;
        for (auto it : HuffCodeTable[i]) 
            out << std::setw(3) << (int)it.first << " " << std::setw(30) << it.second << std::endl;
    }
    
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

    GetFrequency();
    for (int i = 0; i < BYTE_SIZE; i++) {
        this->root[i] = GenHuffmanTree(i);
        GenHuffmanCode(this->root[i], "", i);
    }
}    

void HuffmanCompressor::Compress()
{
    //Note: I can't write a single bit directly to a file. 
    //The I/O unit of reading/writing is a byte (8-bits).
    //Idea: Collect bits until you have enough bits to fill 
    //a byte and then write it..
    
    this->CreateHuffmanMap();

    std::string msgComp; //message encoded
    for (int i = 1; i < msgSize; i++) 
        msgComp+=HuffCodeTable[(uint8_t)msg[i-1]][(uint8_t)msg[i]];

    std::ofstream bin(file+".compress", std::ios::out | std::ios::binary);
    bin << msg[0]; //first symbol only go to out

    while (msgComp.size() % 8 != 0) msgComp += "0";
    char bin_buffer;
    for (int i = 0; i < msgComp.size(); i+=8) {
        bin_buffer &= 0;
        for (int j = 0; j < 8; j++) 
            bin_buffer |= (msgComp[i+j] == '1' ? 1 << (7-j) : 0);
         bin << bin_buffer;
    }
}

/*void HuffmanCompressor::PrintStatistics()
{
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "| Message            size: " << msgSize << " bytes." << std::endl;
    std::cout << "| Huffman    Map     size: " << FileSize("Huffman.map") << " bytes." << std::endl; 
    std::cout << "| Compressed Message size: " << FileSize(file+".compress") << " bytes." << std::endl;
    std::cout << "| Economy                : " << (int)msgSize - FileSize("Huffman.map") - FileSize(file+".compress") << " bytes." << std::endl;
    std::cout << "| Compress         Reason: " << (double)(FileSize("Huffman.map") + FileSize(file+".compress")) / msgSize << "." << std::endl;
    std::cout << "|------------------------------------------------------" << std::endl;

    double total_info = 0;
    int total_huff_bits = 0, total_freq = 0;
    const int* freq = GetFrequency();

    std::cout << "| Symbol Frequency Probability Information HuffmanPerf" << std::endl;
    for (int i = 0; i < BYTE_SIZE; i++) {
        if (freq[i]) {
            printf("| %3d    %8d     %1.5lf     %3.5lf  %6d\n", 
                      i,
                      freq[i],        
                      (double)freq[i]/msgSize,
                      std::log2((double)msgSize/freq[i]),      
                      (int)HuffCodeTable[i].size());
            total_freq += freq[i];
            total_info += freq[i] * std::log2((double)msgSize/freq[i]);
        }
        total_huff_bits += freq[i] * HuffCodeTable[i].size();
    }

    std::cout << "|------------------------------------------------------" << std::endl;
    std::cout << "| Total       Information: " << total_info << " bits." << std::endl;
    std::cout << "| Summed        Frequency: " << total_freq << " [" << msgSize << "]." << std::endl;
    std::cout << "| Entropy                : " << total_info / msgSize << " bits/char." <<  std::endl;
    std::cout << "| Huffman     Performance: " << total_huff_bits  << " bits." << std::endl;
    std::cout << "| Huffman  Perf  by  char: " << (double)total_huff_bits / msgSize << " bits." << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
}
*/