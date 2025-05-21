//实现布隆过滤器

#include<bitset>
#include<functional>
#include <iostream>

class BloomFilter
{
public:
    void insert(std::string str)
    {
        bitset_.set(hash_fn(str) % BITSET_SIZE_);
        bitset_.set(hash_fn(str + "salt1") % BITSET_SIZE_);
        bitset_.set(hash_fn(str + "salt2") % BITSET_SIZE_);
    }

    bool find(std::string str)
    {
        if( bitset_.test(hash_fn(str) % BITSET_SIZE_) &&
            bitset_.test(hash_fn(str + "salt1") % BITSET_SIZE_) &&
            bitset_.test(hash_fn(str + "salt2") % BITSET_SIZE_))
        {
            return true;
        }
        return false;
    }

private:
    std::hash<std::string> hash_fn;
    static const int BITSET_SIZE_ = 10000;
    std::bitset<BITSET_SIZE_> bitset_;
};



int main()
{
    BloomFilter bloom_filter;
    bloom_filter.insert("www.baidu.com");
    bloom_filter.insert("www.alibaba.com");
    bloom_filter.insert("www.tencent.com");
    bloom_filter.insert("www.bilibili.com");

    std::cout << bloom_filter.find("www.bilibili.com") << std::endl;
    std::cout << bloom_filter.find("127.0.0.1") << std::endl;
    std::cout << bloom_filter.find("www.google.com") << std::endl;
    return 0;
}
