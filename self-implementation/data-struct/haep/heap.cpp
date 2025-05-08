#include<functional>
#include <iostream>
using namespace std;

class Heap{
public:
    using Comp = function<bool(int,int)>;
    int* m_addr;
private:
    int m_size;
    int m_cap;
    Comp m_comp;

public:
    Heap(int cap = 20, Comp comp = greater<int>()):m_size(0),m_cap(cap),m_comp(comp){
        m_addr = new int[m_cap];
    }
    Heap(Comp comp):m_size(0),m_cap(20),m_comp(comp){
        m_addr = new int[m_cap];
    }
    ~Heap(){
        delete[] m_addr;
        m_addr = nullptr;
    }
    //下面是Heap需要的方法 push pop top empty size
    bool empty(){
        return m_size == 0;
    }
    void push(int val){
        if(m_size == m_cap){
            expand(2*m_cap);
        }
        siftUp(m_size,val);
        m_size++;
    }
    int pop(){
        if(empty()){
            throw "Heap is empty,can't pop anymore";
        }
        int result = m_addr[0];
        m_size--;
        if(m_size > 0){
            m_addr[0] = m_addr[m_size];
            siftDown(0);
        }
        return result; 
    }
    int top(){
        return m_addr[0];
    }
    int size(){
        return m_size;
    }
private:
    void expand(int cap){
        int* temp = new int[cap];
        for(int i = 0; i < m_size; ++i){
            temp[i] = m_addr[i];
        }
        delete[] m_addr;
        m_addr = temp;
        m_cap = cap;
    }
    void siftUp(int pos,int val){
        if(pos == 0){
            m_addr[pos] = val;
            return;
        }
        int f = (pos - 1)/2;
        while(pos > 0 && m_comp(val,m_addr[f])){
            m_addr[pos] = m_addr[f];
            pos = f;
            f = (pos - 1)/2;
        }
        m_addr[pos] = val;
        return;
    }
    void siftDown(int pos){
        if(pos > m_size){
            throw "can't find the val of that position";
        }
        int val = m_addr[pos];
        while(pos < m_size/2){ //判断条件(找到第一个非叶子节点)
            int child = pos*2 + 1;//左子树一定存在
            if(child + 1 < m_size && m_comp(m_addr[child + 1],m_addr[child])){
                child = child + 1;//判断左右子节点中符合比较条件的那一个
            }
            if(m_comp(val,m_addr[child]))//如果,更符合条件的那个都不满足,那么已经下滤到了最后,退出
                break;
            m_addr[pos] = m_addr[child];
            pos = child;
        }
        m_addr[pos] = val;
    }
};

int main(){
    Heap heap;
    heap.push(1);
    heap.push(9);
    heap.push(5);
    heap.push(4);
    heap.push(17);
    heap.push(66);
    heap.push(45);
    heap.push(99);
    heap.push(56);
    heap.push(12);
    heap.push(66);
    heap.push(45);
    heap.push(99);
    heap.push(56);
    heap.push(12);
    for(int i = 0;i<heap.size();i++){
        cout << *(heap.m_addr + i) << " ";
    }
    cout << endl;
    int size = heap.size();
    for(int i = 0;i<size;i++){
        cout << heap.pop() << " ";
    }
}