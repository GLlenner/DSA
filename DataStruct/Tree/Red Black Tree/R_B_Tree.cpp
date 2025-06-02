//实现红黑树
#include <algorithm>
enum Color{Red,Black};
struct Node
{   
    Node(int val,Color color = Red,Node* parent = nullptr):
        left(nullptr),right(nullptr),parent(parent),
        val(val),color(color){}
    Node* left;
    Node* right;
    Node* parent;
    int val;
    Color color;
};

class RB
{
public:
    RB():root(nullptr){}
    Node* root;
    void left_rotate(Node* node);
    void right_rotate(Node* node);
    void insert(int val);
    void fix(Node* node);
    Color color(Node* node)
    {   
        if(!node)
            return Black;
        return node->color;
    }
};


//左右旋转要操作四个节点，六个指针
void RB::left_rotate(Node* node)
{
    Node* child = node->right;
    Node* gfather = node->parent;
    child->parent = gfather;
    if(gfather == nullptr) //说明当前node节点是根节点，修改当前根节点的值
    {
        root = child;
    }
    else if(gfather->left == node)
    {
        gfather->left = child;
    }
    else
    {
        gfather->right = child;
    }
    node->right = child->left;
    if(node->right)
    {
        node->right->parent = node;
    }
    child->left = node;
    node->parent = child;
}


void RB::right_rotate(Node* node)
{
    Node* child = node->left;
    Node* gfather = node->parent;
    child->parent = gfather;
    if(gfather == nullptr)
    {
        root = child;
    }
    else if(gfather->left == node)
    {
        gfather->left = child;
    }
    else
    {
        gfather->right = child;
    }
    node->left = child->right;
    if(child->right)
    {
        child->right->parent = node;
    }
    child->right = node;
    node->parent = child;
}


void RB::insert(int val)
{
    //////////////////////////////////////////////////////
    //将数据插入到叶子节点，是否冲突下面在处理
    Node* cur = root;
    Node* parent = nullptr;
    if(cur == nullptr)
    {
        root = new Node(val,Black);
        return;
    }
    while(cur != nullptr)
    {   
        if(cur->val > val)
        {
            parent = cur;
            cur = cur->left;
        }
        else if(cur->val < val)
        {
            parent = cur;
            cur = cur->right;
        }
        else
        {
            return;
        }
    }
    cur = new Node(val,Red,parent);
    if(parent->val > val)
    {
        parent->left = cur;
    }
    else
    {
        parent->right = cur;
    }
    //////////////////////////////////////////////////////////
    
    //////////////////////////////////
    //如果有冲突现在解决
    if(cur->parent->color == Red)
    {
        fix(cur);
    }
    return;
}


void RB::fix(Node* node)
{   
    Node* parent = node->parent;
    Node* gfather = parent->parent;
    Node* uncle = nullptr;
    while(color(node->parent) == Red)
    {   
        parent = node->parent;
        gfather = parent->parent;
        //父亲节点在左节点上
        if(gfather->left == parent)
        {   
            uncle = gfather->right;
            //叔叔节点为红色的情况下，要将父亲祖父叔叔节点的颜色重新染色
            //父亲变黑,祖父变红,叔叔变黑
            if(color(uncle) == Red)
            {
                gfather->color = Red;
                parent->color = Black;
                uncle->color = Black;
                node = gfather;
            }
            else //叔叔节点颜色为黑色
            {
                //情况一:LR型,通过旋转变成LL型
                if(parent->right == node)
                {
                    left_rotate(parent);
                    std::swap(node,parent);
                }
                //情况二：LL型
                parent->color = Black;
                gfather->color = Red;
                right_rotate(gfather);
                break;
            }
        }
        else //父亲节点在右节点上
        {   
            uncle = gfather->left;
            if(color(uncle) == Red)
            {
                gfather->color = Red;
                parent->color = Black;
                uncle->color = Black;
                node = gfather;
            }
            else //叔叔节点颜色为黑色
            {
                //情况一:RL型,通过旋转变成LL型
                if(parent->left == node)
                {
                    right_rotate(parent);
                    std::swap(node,parent);
                }
                //情况二：RR型
                parent->color = Black;
                gfather->color = Red;
                left_rotate(gfather);
                break;
            }
        }
    }
    root->color = Black;
}


int main()
{
    RB rb;
    rb.insert(17);
    rb.insert(18);
    rb.insert(23);
    rb.insert(34);
    rb.insert(27);
    rb.insert(15);
    rb.insert(9);
    rb.insert(6);
    rb.insert(8);
    rb.insert(5);
    rb.insert(25);
    return 0;
}