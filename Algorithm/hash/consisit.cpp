#include <map>
#include <vector>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

class PhyNode // 物理节点
{
public:
    PhyNode(string ip, string source = "source") : ip_(ip), source_(source) {}
    string gets_source() const
    {
        return source_ + " in " + ip_;
    }
    string get_ip() const { return ip_; }

private:
    string ip_;
    string source_;
};

class VirNode // 虚拟节点
{
public:
    VirNode(PhyNode* phynode, int index)
        : phynode_(phynode), vnode_name_(phynode->get_ip() + "#" + to_string(index)) {}

    PhyNode* get_phynode() const
    {
        return phynode_;
    }

    string get_vnode_name() const
    {
        return vnode_name_;
    }

private:
    PhyNode* phynode_;
    string vnode_name_; // 用于哈希
};

class ConsistentHash
{
public:
    void add_phynode(PhyNode* phynode)
    {
        for (int i = 0; i < vnode_count_; ++i)
        {
            VirNode* vnode = new VirNode(phynode, i);
            size_t hashval = hash<string>()(vnode->get_vnode_name());
            hashring_[hashval] = vnode;
        }
    }

    string find(string url)
    {
        if (hashring_.empty()) return "no nodes";

        size_t hashval = hash<string>()(url);
        auto it = hashring_.lower_bound(hashval);

        if (it == hashring_.end())
            it = hashring_.begin(); // 顺时针回到最前面

        return it->second->get_phynode()->gets_source();
    }

private:
    static const int vnode_count_ = 10;
    map<size_t, VirNode*> hashring_; // 有序哈希环
};

int main()
{
    PhyNode* node1 = new PhyNode("192.168.1.1", "Node1");
    PhyNode* node2 = new PhyNode("192.168.1.2", "Node2");

    ConsistentHash ch;
    ch.add_phynode(node1);
    ch.add_phynode(node2);

    cout << ch.find("http://example.com/file1") << endl;
    cout << ch.find("http://example.com/file2") << endl;
    cout << ch.find("http://example.com/file0") << endl;
    cout << ch.find("http://example.com/filewqe") << endl;
    cout << ch.find("http://example.com/file31") << endl;

    cout << ch.find("http://sdaddaad") << endl;

    // 记得释放 node1 和 node2 及 VirNode*
}
