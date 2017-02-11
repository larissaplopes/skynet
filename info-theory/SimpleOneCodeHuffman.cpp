#include <iostream>
#include <vector> //priority_queue overload
#include <queue>  //priority_queue
#include <map>    //table (char/code)
#include <iomanip> //setw

#define ASCII_SIZE 256 

//Notes:
//inheritance use cause overload operator() to create min_heap
//use flag: std=c++11

typedef std::map<char, std::string> HuffCode;

class PNode //Parent Node
{
public:
    const int info;

    virtual ~PNode() {} //abstract class
protected:
    PNode(int _info) : info(_info) {}
};

class SNode : public PNode //Simple Node
{
public:
    PNode* const left;
    PNode* const right;

    SNode(PNode* l, PNode* r) : 
        PNode(l->info + r->info), left(l), right(r) {}

    ~SNode() {
        delete left;
        delete right;
    }

};

class LNode : public PNode //Leaf Node
{
public:
    const char c;

    LNode(int _info, char _c) : PNode(_info), c(_c) {}
};

struct min_heap //Comparison to overload stl-priority_queue
{
    bool operator()(const PNode* u, const PNode* v) const
    { return u->info > v->info; }
};

const int* GetFrequency(const std::string& m)
{
    int *F = new int[ASCII_SIZE]{0}; 
    for (auto it = m.begin(); it != m.end(); it++) F[*it]++;
    return F;
}

PNode* GenHuffmanTree(const int* freq)
{
    std::priority_queue<PNode*, std::vector<PNode*>, min_heap> N; //nodes

    for (int i = 0; i < ASCII_SIZE; i++) //leafs
        if (freq[i]) N.push(new LNode(freq[i], char(i)));

    while (N.size() > 1) { //simples
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

void PrintHuffmanCode(const HuffCode &t)
{
    for (auto it : t) std::cout << it.first << " " << std::setw(10) << it.second << std::endl;
}

int main()
{
    HuffCode HuffCodeTable;
    std::string s = "AAAAAAAAAAAAAAABBBBBBBBBBBBBBCDEFGHIJK";

    const int *f = GetFrequency(s);
    PNode* root  = GenHuffmanTree(f);

    GenHuffmanCode(root, "", HuffCodeTable);
    PrintHuffmanCode(HuffCodeTable);

    delete root;
    delete f;

    return 0;
}