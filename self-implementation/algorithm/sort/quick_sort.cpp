//快速排序实现

#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;


int partition(vector<int>& arr,int left,int right){
    int base_val = arr[left];
    //注意临界条件
    while(left < right){
        while(left < right && arr[right] >= base_val) right--;//注意是>=号,否则相等时会陷入死循环,arr[right] >= base_val
        arr[left] = arr[right];//其次,交换之后不要直接变动
        while(left < right && arr[left] <= base_val) left++;
        arr[right] = arr[left];   
    }
    arr[left] = base_val;
    return left;
}
void quick_sort(vector<int>& arr,int left,int right){
    if(left < right){
        int mid = partition(arr,left,right);
        quick_sort(arr,left,mid-1);
        quick_sort(arr,mid+1,right);
    }
}
void quick_sort(vector<int>&arr){
    quick_sort(arr,0,arr.size()-1);
}
//算法分析:
//时间复杂度:       O(nlogn) 当数组趋于有序时,可能会退化到O(n^2)
//空间复杂度:       O(logn)   主要是递归调用时,栈上的内存开销
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
    quick_sort(arr);
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}