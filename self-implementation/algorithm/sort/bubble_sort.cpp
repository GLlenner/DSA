//实现冒泡排序

#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;

void bubble_sort(vector<int>& arr){
    for(int i = 0;i<arr.size();i++){
        //此处可以进行优化,如果一次遍历到最后没有发生交换,那么就已经排好序了
        //flag = true
        for(int j = 0;j<arr.size()-i-1;j++){ //冒泡操作,每次循环让最大/小值冒泡到最高位
            if(arr[j] > arr[j+1]){
                //flag = false
                swap(arr[j],arr[j+1]);
            }
        }
        //if(flag == true) return;
    }
}
//算法分析:
//时间复杂复杂度:   O(n^2) 
//空间复杂度:       O(1)
//稳定性:           稳定

int main(){
    srand(time(NULL));
    vector<int>arr(10,0);
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % (100 + 1);
    }
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    bubble_sort(arr);
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}