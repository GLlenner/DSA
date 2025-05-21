//位图实现查重算法
#include<vector>
#include <iostream>

class BitMap
{
public:
    BitMap(int maxnum)
    :maxnum_(maxnum)
    {
        int size = maxnum_ / 32 + 1;
        bitmap_.resize(size);
    }

    bool insert(int num)
    {
        if(num > maxnum_)
        {
            throw "can't insert such big num";
        }
        if(check_bit(num))
        {
            std::cout << "num already exist" << std::endl;
            return false;
        }
        set_bit(num);
        return true;
    }

    bool erase(int num)
    {
        if(num > maxnum_)
        {
            throw "can't insert such big num";
        }
        if(check_bit(num) == 0)
        {
            std::cout << "the num doesn't exist" << std::endl;
            return false;
        }
        set_bit(num,false);
        return true;
    }

    bool find(int num)
    {
        return check_bit(num);
    }
private:
    void set_bit(int num,bool type = true)
    {
        int index = num / 32;
        int offset = num % 32;
        if(type)
        {
            bitmap_[index] = bitmap_[index] | (1 << offset);
        }
        else
        {
            bitmap_[index] = bitmap_[index] & ~(1 << offset);
        }
    }

    bool check_bit(int num)
    {
        int index = num / 32;
        int offset = num % 32;
        return (bitmap_[index] >> offset) & 1; 
    }

    int maxnum_;
    std::vector<int> bitmap_;
};


int main()
{
    BitMap bitmap(6547);
    int a[] = {1,14,421,23,5325,6547,756,413,4324,44,556,6,654};
    for(auto val: a){
        bitmap.insert(val);
    }

    std::cout << bitmap.find(23) << std::endl;
    bitmap.erase(23);
    std::cout << bitmap.find(23) << std::endl;
    
    return 0;
}