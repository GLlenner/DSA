//递归版本实现二叉搜索树

#include <iostream>
using namespace std;


struct Node
{
    int val;
    Node* left;
    Node* right;
    Node(int val):val(val),left(nullptr),right(nullptr){}
};
class BST
{
public:
    BST():head(nullptr){}
    BST(int val):head(new Node(val)){}
    void insert(int val);
    Node* insert(Node* node, int val);
    bool find(int val);
    bool find(Node* node,int val);
    void erase(int val);
    Node* erase(Node* node,int val);
    void preorder_traversal(Node* node);
    void inorder_traversal(Node* node);
    void postorder_traversal(Node* node);
public:
    Node* head;
};

void BST::insert(int val)
{
    head = insert(head,val);
}
Node* BST::insert(Node* node, int val)
{
    if(!node)
        return new Node(val);
    if(node->val == val)
        throw "can't insert this val ,repeat";
    else if(node->val > val)
        node->left = insert(node->left,val);
    else
        node->right = insert(node->right,val);
    return node;
}
bool BST::find(int val)
{
    return find(head,val);
}
bool BST::find(Node* node,int val)
{
    if(!node)
        return false;
    else if(node->val > val)
        return find(node->left,val);
    else if(node->val < val)
        return find(node->right,val);
    else
        return true;
}
void BST::erase(int val)
{
    head = erase(head,val);
}
Node* BST::erase(Node* node,int val)
{   if(!node)
        return nullptr;
    if(node->val > val)
        node->left = erase(node->left,val);
    else if(node->val < val)
        node->right = erase(node->right,val);
    else
    {
        if(node->left && node->right)
        {
            Node* cur = node->right;
            while(cur->left)
            {
                cur = cur->left;
            }
            node->val = cur->val;
            node->right = erase(node->right,cur->val);
        }
        else if(node->left)
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else if(node->right)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else
        {
            delete node;
            return nullptr;
        }
    }
    return node;
}
void BST::preorder_traversal(Node* node)
{   
    if(!node) return;
    cout << node->val << " ";
    preorder_traversal(node->left);
    preorder_traversal(node->right);
    return;
}
void BST::inorder_traversal(Node* node)
{
    if(!node) return;
    inorder_traversal(node->left);
    cout << node->val << " ";
    inorder_traversal(node->right);
    return;
}
void BST::postorder_traversal(Node* node)
{
    if(!node) return;
    postorder_traversal(node->left);
    cout << node->val << " ";
    postorder_traversal(node->right);
    return;
}

int main()
{
    BST bst;
    bst.insert(7);
    bst.insert(5);
    bst.insert(10);
    bst.insert(9);

    cout << bst.find(9) << endl;
    cout << bst.find(99) << endl;

    bst.insert(15);
    bst.insert(11);
    bst.insert(16);

    bst.inorder_traversal(bst.head);
    cout << endl;
    bst.erase(7);
    bst.inorder_traversal(bst.head);
    return 0;
}