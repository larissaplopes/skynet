#ifndef NODES_HPP
#define NODES_HPP

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

#endif