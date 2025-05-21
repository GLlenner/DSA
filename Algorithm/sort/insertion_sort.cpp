//实现插入排序

#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;

//实现还是简单
//例子展示:
//1 3 6 7 12 15 9 35 45 86
//              |将9插入到前面有序的队列中
//优化(折半插入排序):又因为前面是有序的数组,所以插入的时候可以使用二分搜索插入的位置,在整体向后移动
void insert_sort(vector<int>& arr){
    for(int i = 1;i < arr.size();i++){
        //注意边界条件
        int insert_val = arr[i];
        int j = i - 1 ;
        while(j >=0 && arr[j] > insert_val){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = insert_val;
    }
}
//算法分析:
//时间复杂度:       O(n^2)      注意:当数组基本有序时,时间复杂度趋于O(n)
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
    insert_sort(arr);
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}