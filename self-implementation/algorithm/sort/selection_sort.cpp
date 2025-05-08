//实现选择排序(遍历让数组中最小的值放在第一个)

#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;


void select_sort(vector<int>& arr){//主要思想就是,每趟遍历然后把最小/大值一位一位放到前端
    for(int i = 0;i<arr.size();i++){
        int min = i;
        for(int j = i;j<arr.size();j++){
            if(arr[j] < arr[min])
                min = j;
        }
        swap(arr[min],arr[i]);
    }
}
//算法分析:
//时间复杂复杂度:   O(n^2) 
//空间复杂度:       O(1)
//稳定性:           不稳定  //举例: 5(1) 5(2) 3 ---> 3 5(2) 5(1) 不稳定了


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
    select_sort(arr);
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}


