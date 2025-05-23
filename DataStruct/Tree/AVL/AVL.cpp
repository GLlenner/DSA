//实现二叉平衡树

#include <algorithm>
#include <iostream>
struct Node
{   
    Node(int val):left(nullptr),right(nullptr),val(val),height(1){}
    Node* left;
    Node* right;
    int val;
    int height;
};

class AVL
{
public:
    AVL():root(nullptr){}
    //获取节点高度
    int height(Node* node);
    //右子树的右节点失衡,左旋转
    Node* left_rotate(Node* node);
    //左子树的左节点失衡,右旋转
    Node* right_rotate(Node* node);
    //右子树的左节点失衡,左平衡
    Node* left_balance(Node* node);
    //左子树的右节点失衡,右平衡
    Node* right_balance(Node* node);

    //插入节点
    Node* insert(int val,Node* node);
    //删除节点
    Node* erase(int val,Node* node);
    Node* root;
};

int AVL::height(Node* node)
{
    return node ? node->height:0;
}

Node* AVL::left_rotate(Node* node)
{
    Node* child = node->right;
    node->right = child->left;
    child->left = node;
    node->height = std::max(height(node->left),height(node->right)) + 1;
    child->height = std::max(height(child->left),height(child->right)) + 1;
    return child;
} 

Node* AVL::right_rotate(Node* node)
{
    Node* child = node->left;
    node->left = child->right;
    child->right = node;
    node->height = std::max(height(node->left),height(node->right)) + 1;
    child->height = std::max(height(child->left),height(child->right)) + 1;
    return child;
}

Node* AVL::left_balance(Node* node)
{   
    Node* child = node->left;
    node->left = left_rotate(child);
    return right_rotate(node);
}

Node* AVL::right_balance(Node* node)
{
    Node* child = node->right;
    node->right = right_rotate(child);
    return left_rotate(node);
}

Node* AVL::insert(int val,Node* node)
{   
    if(node == nullptr)
    {   
        return new Node(val);
    }
    else if(val < node->val)
    {
        node->left = insert(val,node->left);
        node->height = std::max(height(node->left),height(node->right)) + 1;
        if(height(node->left) - height(node->right) > 1)
        {   
            Node* tem = node->left;
            if(height(tem->left) < height(tem->right))
            {
                node = left_balance(node);
            }
            else
            {
                node = right_rotate(node);
            }
        }
    }
    else if(val > node->val)
    {
        node->right = insert(val,node->right);
        node->height = std::max(height(node->left),height(node->right)) + 1;
        if(height(node->right) - height(node->left) > 1)
        {   
            Node* tem = node->right;
            if(height(tem->left) > height(tem->right))
            {
                node = right_balance(node);
            }
            else
            {
                node = left_rotate(node);
            }
        }
    }
    else
    {
        ;
    }
    return node;
}

Node *AVL::erase(int val, Node *node)
{
    if(node == nullptr)
    {   
        return node;
    }
    else if(node->val < val)
    {
        node->right = erase(val,node->right);
    }
    else if(node->val > val)
    {
        node->left = erase(val,node->left);
    }
    else
    {
        if(node->left && node->right)
        {
            if(height(node->left) > height(node->right))
            {
                Node* cur = node->left;
                while(cur->right)
                {
                    cur = cur->right;
                }
                node->val = cur->val;
                node->left = erase(node->val,node->left);   
            }
            else
            {
                Node* cur = node->right;
                while(cur->left)
                {
                    cur = cur->left;
                }
                node->val = cur->val;
                node->right = erase(node->val,node->right);
            }
        }
        else if(node->left)
        {
            Node* tem = node->left;
            delete node;
            return tem;
        }
        else if(node->right)
        {
            Node* tem = node->right;
            delete node;
            return tem;
        }
        else
        {
            delete node;
            return nullptr;
        }
    }

    node->height = std::max(height(node->left),height(node->right)) + 1;
    if(height(node->left) - height(node->right) > 1)
    {   
        Node* tem = node->left;
        if(height(tem->left) < height(tem->right))
        {
            node = left_balance(node);
        }
        else
        {
            node = right_rotate(node);
        }
    }
    else if(height(node->right) - height(node->left) > 1)
    {
        Node* tem = node->right;
        if(height(tem->left) > height(tem->right))
        {
            node = right_balance(node);
        }
        else
        {
            node = left_rotate(node);
        }
    }
    return node;
}

void inorder(Node* node)
{
    if (!node) return;
    inorder(node->left);
    std::cout << node->val << " ";
    inorder(node->right);
}
bool is_balanced(Node* node)
{
    if (!node) return true;
    int lh = node->left ? node->left->height : 0;
    int rh = node->right ? node->right->height : 0;

    if (std::abs(lh - rh) > 1) return false;
    return is_balanced(node->left) && is_balanced(node->right);
}
int main()
{
    AVL avl;

    // 插入测试
    for (int i = 1; i < 10; i++) {
        avl.root = avl.insert(i, avl.root);
    }

    std::cout << "中序遍历（插入后）: ";
    inorder(avl.root);
    std::cout << "\nAVL 是否平衡: " << (is_balanced(avl.root) ? "是" : "否") << std::endl;

    // 删除测试
    avl.root = avl.erase(1, avl.root);
    avl.root = avl.erase(3, avl.root);

    std::cout << "中序遍历（删除后）: ";
    inorder(avl.root);
    std::cout << "\nAVL 是否平衡: " << (is_balanced(avl.root) ? "是" : "否") << std::endl;
    
    avl.root = avl.insert(99, avl.root);
    avl.root = avl.insert(56, avl.root);
    avl.root = avl.insert(32, avl.root);
    inorder(avl.root);
    std::cout << "\nAVL 是否平衡: " << (is_balanced(avl.root) ? "是" : "否") << std::endl;

    avl.root = avl.erase(9, avl.root);
    inorder(avl.root);
    std::cout << "\nAVL 是否平衡: " << (is_balanced(avl.root) ? "是" : "否") << std::endl;
    return 0;
}
