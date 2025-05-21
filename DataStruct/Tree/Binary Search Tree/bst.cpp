//非递归版本实现二叉搜索树

#include <iostream>
#include<stack>
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
    bool find(int val);
    bool erase(int val);
    void preorder_traversal(Node* node);
    void inorder_traversal(Node* node);
    void postorder_traversal(Node* node);


public:
    Node* head;
};

void BST::insert(int val)
{
    Node* node = new Node(val); 
    if(head == nullptr)
    {
        head = node;
        return;
    }
    Node* cur = head;
    Node* parent = head;
    while(cur)
    {   
        parent = cur;
        if(cur->val == val)
        {
            throw "can't insert this val ,repeat";
        }
        else if(cur->val < val)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
    }
    if(parent->val > val)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }
}
bool BST::find(int val)
{
    Node* node = head;
    while(node)
    {
        if(node->val == val)
            return true;
        else if(node->val > val)
            node = node->left;
        else
            node = node->right;
    }
    return false;
}
bool BST::erase(int val)
{   
    Node* cur = head;
    Node* parent = head;
    while(cur)
    {   
        parent = cur;
        if(cur->val > val)
            cur = cur->left;
        else if(cur->val < val)
            cur = cur->right;
        else
            break;
    }
    if(!cur)
        return false;
    
    if(cur->left && cur->right)
    {   
        Node* del_node = cur;
        parent = cur;
        cur = cur->right;
        while(cur->left)
        {
            parent = cur;
            cur = cur->left;
        }
        del_node->val = cur->val;
        if(parent->right == cur)
            parent->right = cur->right;
        else
            parent->left = cur->right;
        delete cur;
    }
    else if(cur->right)
    {
        if(parent->left == cur)
            parent->left = cur->right;
        else
            parent->right = cur->right;
        delete cur;
    }
    else if(cur->left)
    {   
        if(parent->left == cur)
            parent->left = cur->left;
        else
            parent->right = cur->left;
        delete cur;
    }
    else
    {
        if(parent->left == cur)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete cur;
    }
    return true;
}
void BST::preorder_traversal(Node* head)
{
    stack<Node*> mstack;
    mstack.push(head);
    Node* temp;
    while(!mstack.empty())
    {
        temp = mstack.top();
        mstack.pop();
        cout << temp->val << " ";

        mstack.push(temp->right);
        mstack.push(temp->left);
    }
}
void BST::inorder_traversal(Node* node)
{
    stack<Node*> mstack;
    Node* cur = head;
    while (cur || !mstack.empty())
    {   
        while(cur)
        {
            mstack.push(cur);
            cur = cur->left;
        }
        cur = mstack.top();
        mstack.pop();
        cout << cur->val << " ";
        cur = cur->right;
    }
}
void postorder_traversal(Node* node)
{

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
    bst.erase(7);

    return 0;
}

