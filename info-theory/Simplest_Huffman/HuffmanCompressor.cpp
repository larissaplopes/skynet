#include <iostream>
#include <vector> //priority_queue overload
#include <queue>  //priority_queue
#include <map>    //table (char/code)
#include <iomanip> //setw
#include <string>
#include "Nodes.hpp"

#define ASCII_SIZE 256 

typedef std::map<char, std::string> HuffCode;

class HuffmanCompressor
{
    PNode *root;
    HuffCode HuffCodeTable;

    const int* GetFrequency(const std::string& m)
    {
        int *F = new int[ASCII_SIZE]{0}; 
        for (auto it = m.begin(); it != m.end(); it++) F[*it]++;
        return F;
    }

    PNode* GenHuffmanTree(const int* freq)
    {
        std::priority_queue<PNode*, std::vector<PNode*>, min_heap> N; //nodes

        for (int i = 0; i < ASCII_SIZE; i++) //leaf
            if (freq[i]) N.push(new LNode(freq[i], char(i)));

        while (N.size() > 1) { //simple
            PNode* r = N.top(); N.pop();
            PNode* l = N.top(); N.pop();
            N.push(new SNode(r, l));
        }

        return N.top();
    }

    void GenHuffmanCode(const PNode* n, const std::string code,
                        HuffCode &out)
    {
        if (const LNode* leaf = dynamic_cast<const LNode*>(n)) { //leaf node
            out[leaf->c] = code;
        } else if (const SNode* simple = dynamic_cast<const SNode*>(n)) { //simple node
            GenHuffmanCode(simple->left, code + '0', out);
            GenHuffmanCode(simple->right, code + '1', out);
        } else {
            return; 
        }
    }

public:
    
    HuffmanCompressor(const std::string& m)
    {
        const int *f = GetFrequency(m);
        this->root = GenHuffmanTree(f);
        GenHuffmanCode(this->root, "", HuffCodeTable);
    }    

    void PrintHuffmanCode()
    {
        for (auto it : HuffCodeTable) 
            std::cout << it.first << " " << std::setw(10) << it.second << std::endl;
    }

    void CreateHuffmanMap(){}
};

