//使用链表实现哈希表

#include<vector>
#include<list>
#include <iostream>

using namespace std;
class HashTable{
public:
    HashTable(int bucket_size = 3,double work_load = 0.75):
    work_load_(work_load),used_bucket_(0){
        for(int i = 0;i<PRIME_SIZE;i++){
            if(primes[i] >= bucket_size){
                bucket_size_ = bucket_size;
                prime_idx_ = i;
                break;
            }
            if(i == PRIME_SIZE - 1){
                throw "can't expand such big hashtable";
            }
        }
        buckets.resize(bucket_size_);
    }

    bool find(int key){
        int idx = key % bucket_size_;
        for(auto val: buckets[idx]){
            if(val == key){
                return true;
            }
        }
        return false;
    }
    list<int>::iterator find_pos(int key){
        int idx = key % bucket_size_;
        for(auto it = buckets[idx].begin();it != buckets[idx].end();it++){
            if(*it == key){
                return it;
            }
        }
        return buckets[idx].end();
    }
    bool insert(int key){
        if(find(key)){
            cerr << "already have the key element can't insert" << endl;
            return false;
        }
        if(used_bucket_*1.0/bucket_size_ >= work_load_){
            expand();
        }
        int idx = key % bucket_size_;
        if(buckets[idx].empty()){
            used_bucket_++;
        }
        buckets[idx].emplace_back(key);
        return true;
    }
    bool erase(int key){
        int idx = key % bucket_size_;
        list<int>::iterator it = find_pos(key);
        if(it != buckets[idx].end()){
            buckets[idx].erase(it);
            return true;
        }
        cerr << "don't exist key in hashtable, can't erase" << endl;
        return false;
    }

private:
    void expand(){
        prime_idx_++;
        if(prime_idx_ == PRIME_SIZE){
            throw "can't expand such huge hashtable";
        }
        bucket_size_  = primes[prime_idx_];
        used_bucket_ = 0;
        vector<list<int>> old_buckets;
        buckets.swap(old_buckets);
        buckets.resize(bucket_size_);
        for(auto bucket:old_buckets){
            for(auto key:bucket){
                int idx = key % bucket_size_;
                if(buckets[idx].empty()){
                    used_bucket_++;
                }
                buckets[idx].emplace_back(key);
            }
        }
    }

    vector<list<int>> buckets;
    int bucket_size_;
    int used_bucket_;
    double work_load_;

    int prime_idx_;
    const static int PRIME_SIZE = 10;
    const static int primes[PRIME_SIZE];
};
const int HashTable::primes[PRIME_SIZE] = {3,7,23,47,97,251,443,911,1471,42773};

int main(){
    HashTable hashtable;
    hashtable.insert(1);
    hashtable.insert(2);
    hashtable.insert(3);
    hashtable.insert(3);
    hashtable.insert(8);

    cout << hashtable.find(8) << endl;
    hashtable.erase(8);
    cout << hashtable.find(8) << endl;

    cout << hashtable.find(1) << endl;
    hashtable.erase(1);
    cout << hashtable.find(1) << endl;
    return 0;
}