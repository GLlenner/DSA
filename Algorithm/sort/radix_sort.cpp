//实现基数排序

#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;


void radix_sort(vector<int>& arr){
    int maxnum = arr[0];
    for(auto& num: arr){
        if(num > maxnum){
            maxnum = num;
        }
    }
    int len = to_string(maxnum).size();
    vector<vector<int>> vecs(10,vector<int>());
    int mod = 1;
    int dev = 10;
    for(int i = 0;i<len;i++,mod*=10,dev*=10){
        for(int j = 0;j<arr.size();j++){
            vecs[arr[j]/mod%dev].push_back(arr[j]);
        }
        int count = 0;
        for(auto& vec:vecs){
            for(auto num:vec){
                arr[count] = num;
                count++;
            }
            vec.clear();
        }
    }
}
//算法分析:
//时间复杂度:       O(nd) d是最大元素的长度
//空间复杂度:       O(n)    桶的开销
//稳定性:           稳定
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
    radix_sort(arr);
    for(int i = 0;i < 10;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}