//实现希尔排序

#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;


//类似插入排序实现
//注意临界条件
void shell_sort(vector<int>& arr){
    for(int gap = arr.size()/2;gap>0;gap/=2){
        for(int i = gap;i < arr.size();i++){
            int insert_val = arr[i];
            int j = i - gap;
            while(j >= 0 && arr[j] > insert_val){
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = insert_val;
        }
    }
}


int main(){
    srand(time(NULL));
    vector<int>arr(100,0);
    for (int i = 0; i < 100; i++)
    {
        arr[i] = rand() % (100 + 1);
    }
    for(int i = 0;i < 100;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    shell_sort(arr);
    for(int i = 0;i < 100;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}