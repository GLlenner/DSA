//实现红黑树
#include <algorithm>
#include <cstdio>
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
    void insert_fix(Node* node);

    void erase(Node* node,int val);
    void erase_fix(Node* node);


    int check_isRB(Node* node);
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
        insert_fix(cur);
    }
    return;
}


void RB::insert_fix(Node* node)
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


/*当节点没有左右节点时,且待删除的节点是黑色节点,才进入这个函数*/
void RB::erase_fix(Node* node)
{   
    /*当对父节点再次修复时,会进入到这样的判断*/
    if(color(node) == Red || node == root)
    {
        node->color = Black;
        return;
    }


    Node* father = node->parent;
    /*兄弟节点*/
    Node* brother;
    bool is_left = true;//兄弟节点位于父节点左右的标志
    if(father->left == node)
    {
        brother = father->right; 
        is_left = false;
    }
    else
    {
        brother = father->left;
    }

    /*开始处理冲突*/
    /*1.如果兄弟节点的颜色为黑色*/
    /*分两种情况讨论: 
        1.兄弟至少有一个红子节点
        2.兄弟节点全黑*/
    if(color(brother) == Black)
    {   
        /*1.1兄黑,兄弟至少有一个红子节点*/
        /*分四种情况讨论: LL LR RL RR*/
        if(color(brother->left) == Red || color(brother->right) == Red)
        {
            if(is_left)
            {
                /*情况一: LL*/
                /*解决冲突: 兄子变兄,兄变父,父变黑  再右旋*/
                if(color(brother->left) == Red)
                {
                    brother->left->color = brother->color;
                    brother->color = father->color;
                    father->color = Black;
                    right_rotate(father);
                }
                /*情况二: LR*/
                /*解决冲突: 兄子变父, 父亲变黑 ,先左旋再右旋*/
                else
                {
                    brother->right->color = father->color;
                    father->color = Black;
                    left_rotate(brother);
                    right_rotate(father);
                }
            }
            else
            {   
                /*情况三: RR*/
                /*解决冲突: 兄子变兄,兄变父,父变黑  再左旋*/
                if(color(brother->right) == Red)
                {
                    brother->right->color = brother->color;
                    brother->color = father->color;
                    father->color = Black;
                    left_rotate(father);
                }
                /*情况四: RL*/
                /*解决冲突: 兄子变父, 父亲变黑, 先左旋再右旋*/
                else
                {
                    brother->left->color = father->color;
                    father->color = Black;
                    right_rotate(brother);
                    left_rotate(father);
                }
            }
        }
        /*1.2:兄弟节点的子节点全为黑色*/
        /*解决冲突: 兄弟变红,再对父亲节点修复*/
        else
        {
            brother->color = Red;
            erase_fix(father);
        }
    }
    /*兄弟节点为红色*/
    /*兄父变色,父向我旋*/
    else
    {   
        Color tmp = brother->color;
        brother->color = father->color;
        father->color = tmp;
        if(is_left)/*兄弟节点再左边,我要向右旋*/
        {
            right_rotate(father);
        }
        else
        {
            left_rotate(father);
        }
        erase_fix(node);
    }
}

void RB::erase(Node* node,int val)
{   
    /*如果不存在,直接返回即可*/
    if(node == nullptr)
        return;
    /*和二叉搜索树一样先找到要删除的节点*/
    if(node->val > val)
    {
        erase(node->left,val);
    }
    else if(node->val < val)
    {
        erase(node->right,val);
    }
    else
    {   
        /*如果左右子树都有节点*/
        if(node->left && node->right)
        {
            /*删除前驱*/
            Node* cur = node->left;
            while(cur->right != nullptr)
                cur = cur->right;
            node->val = cur->val;
            erase(node->left,cur->val);
        }
        /*当只有一个节点的时候,一定是父节点为黑色,子节点为红色*/
        /*解决冲突策略: 子取代父,变成黑色*/
        else if(node->left)/*只有左孩子*/
        {   
            /*将父节点的子节点置空*/
            Node* father = node->parent;
            node->left->color = Black;
            if(father->left == node)
            {
                father->left = node->left;
                node->left->parent = father;
            }
            else
            {
                father->right = node->left;
                node->left->parent = father;
            }
            delete node;
            return;
        }
        else if(node->right)/*只有右孩子*/
        {   
            /*将父节点的子节点置空*/
            Node* father = node->parent;
            node->right->color = Black;
            if(father->left == node)
            {
                father->left = node->right;
                node->right->parent = father;
            }
            else
            {
                father->right = node->right;
                node->right->parent = father;
            }
            delete node;
            return;
        }
        else/*没有孩子节点*/
        {   
            /*当没有孩子节点时，且要删除的是根节点，直接删除了*/
            if(node == root)
            {   
                root = nullptr;
                delete node;
                return;
            }
            Node* father = node->parent;
            /*待删除的是红色节点,直接删除*/
            if(color(node) == Red)
            {
                /*将父节点的子节点置空*/
                if(father->left == node)
                {
                    father->left = nullptr;
                }
                else
                {
                    father->right = nullptr;
                }
                delete node;
            }
            /*如果待删除的节点是黑色节点,且左右子节点都没有,才会进入到 erase_fix() 函数中*/
            else
            {   
                erase_fix(node);
                /*父节点置空*/
                if(node->parent->right == node)
                {
                    node->parent->right = nullptr;
                }
                else
                {
                    node->parent->left = nullptr;
                }
                /*删除节点 node*/
                delete node;
            }
        }
    }
}


int RB::check_isRB(Node* node)
{   
    if(node == nullptr)
        return 1;
    
    if(color(node) == Red && (color(node->left) == Red || color(node->right) == Red))
    {
        return -1;
    }

    int left = check_isRB(node->left);
    int right = check_isRB(node->right);

    if(left != right || left == -1 || right == -1)
        return -1;
    
    return color(node) == Black? left+1:left;
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
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,18);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,25);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,15);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,6);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,13);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,37);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,27);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,17);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,34);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,9);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,8);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,23);
    printf("%d\n",rb.check_isRB(rb.root));
    rb.erase(rb.root,5);
    printf("%d\n",rb.check_isRB(rb.root));

    return 0;
}