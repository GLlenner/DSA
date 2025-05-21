//哈希表的线性实现

#include<iostream>
using namespace std;


enum State{UNUSED,USEING,DELED};
struct Bucket{
    int val;
    State state;
    Bucket():val(0),state(UNUSED){};
};
class HashTable{
//insert find erase 
public:
    HashTable(int size=3,double workLoad=0.75):tableSize(0),workLoad(workLoad){
        for(int i = 0;i<PRIME_SIZE;i++){
            if(size <= primes[i]){
                prime_idx = i;
                tableCap = primes[i];
                break;
            }
            if(i == PRIME_SIZE - 1){
                throw "can't allocate such big HashTable";
            }
        }
        hashtable = new Bucket[tableCap];
    }
    ~HashTable(){
        delete[] hashtable;
        hashtable = nullptr;
    }
    bool insert(int val){
        double curWorkLoad = tableSize *1.0 / tableCap;
        if(curWorkLoad > workLoad){
            expand();
        }
        int idx = val % primes[prime_idx];
        int i = idx;
        do{
            if(hashtable[i].state!=USEING){
                hashtable[i].val = val;
                hashtable[i].state = USEING;
                ++tableSize;
                return true;
            }
            i = (i+1)%tableCap;
        }while(i!=idx);
        return false;
    }
private:
    void expand(){
        ++prime_idx;
        if(prime_idx == PRIME_SIZE){
            throw "can't expand the hashtable anymore";
        }
        int oldTableCap = tableCap;
        tableCap = primes[prime_idx];
        Bucket* newHashTable = new Bucket[tableCap];
        for(int i=0;i<oldTableCap;i++){
            if(hashtable[i].state == USEING){
                int idx = hashtable[i].val % tableCap;
                int j = idx;
                do{
                    if(newHashTable[j].state!=USEING){
                        newHashTable[j].val = hashtable[i].val;
                        newHashTable[j].state = USEING;
                        break;
                    }
                    j = (j+1)%tableCap;
                }while(i!=idx);
            }
        }
        delete[] hashtable;
        hashtable = newHashTable;
    }

    Bucket* hashtable;
    int tableCap;      //哈希表的容量
    int tableSize;      //哈希表现在使用的大小
    double workLoad;    //哈希表的工作负载

    int prime_idx;      //现在使用的哈希函数的数组的下标
    static const int PRIME_SIZE = 10;   //素数数组的大小
    static const int primes[PRIME_SIZE];      //素数数组
};
const int HashTable::primes[PRIME_SIZE] = {3,7,23,47,97,251,443,911,1471,42773}; 

int main(){
    cout << UNUSED << endl;

    Bucket a;
    cout << a.val << ' ' << a.state << endl;

    HashTable hashtable;
    hashtable.insert(1);
    hashtable.insert(2);
    hashtable.insert(3);
    hashtable.insert(2);


    return 0;
}