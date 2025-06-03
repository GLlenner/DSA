
struct Node
{   
    Node():
    left(nullptr),right(nullptr),mid(nullptr),
    lval(0),rval(0){}
    Node* left;
    Node* right;
    Node* mid;
    int lval;
    int rval;
};


class Tree2_3
{
public:
        
    Node* root;
};