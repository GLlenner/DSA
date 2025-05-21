//实现堆排序

#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;

void siftDown(vector<int>& arr,int pos,int count){
    int val = arr[pos];
    int boundary = count/2;
    while(pos < boundary){
        int child = 2*pos + 1;
        if(child + 1 < count && arr[child+1] > arr[child]){
            child = child+1;
        }
        if(arr[child] < val)
            break;
        arr[pos] = arr[child];
        pos = child;
    }
    arr[pos] = val;
}
void bulid_heap(vector<int>& arr){
    int size = arr.size();
    for(int i=(size-2)/2;i>=0;--i){
        siftDown(arr,i,size);            //对每个非叶子节点进行下滤操作,实现建堆(即自底向上建堆)
    }
}
void organize_heap(vector<int>& arr){
    int size = arr.size();
    for(int i=size-1;i>0;--i){
        swap(arr[0],arr[i]);            //组织一下数组,把每个0号元素与最后一个元素交换,再对0号元素进行下滤
        siftDown(arr,0,i);            
    }
}
void heap_sort(vector<int>& arr){
    bulid_heap(arr);//原地建堆
    organize_heap(arr);
}
//算法分析:
//时间复杂度:       O(nlogn)
//空间复杂度:       O(1)
//稳定性:           不稳定


int main(){
    srand(time(NULL));
    vector<int>arr(10);
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % (100 + 1);
    }
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    heap_sort(arr);
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}