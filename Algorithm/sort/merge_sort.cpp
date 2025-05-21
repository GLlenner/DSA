//实现归并排序

#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;

void merge(vector<int>& arr,int left,int mid,int right){
    vector<int>newarr(right-left+1);
    int i = left;
    int j = mid + 1;
    int k = 0;
    while(i <= mid && j <= right){
        if(arr[i] < arr[j]){
            newarr[k++] = arr[i++];
        }
        else{
            newarr[k++] = arr[j++];
        }
    }
    if(i == mid+1){
        while(j <= right){
            newarr[k++] = arr[j++];
        }
    }
    if(j == right + 1){
        while (i <= mid){
            newarr[k++] = arr[i++];
        }
    }
    for(int i = 0;i<newarr.size();i++){
        arr[left + i] = newarr[i]; 
    }
}

void merge_sort(vector<int>& arr,int left,int right){
    if(left >= right) return;
    int mid = (left + right) / 2;
    merge_sort(arr,left,mid);
    merge_sort(arr,mid+1,right);
    merge(arr,left,mid,right);
}

void merge_sort(vector<int>& arr){
    merge_sort(arr,0,arr.size()-1);
}
//算法分析:
//时间复杂度:       O(nlogn)
//空间复杂度:       O(n)   数据转存时的开销
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
    merge_sort(arr);
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}