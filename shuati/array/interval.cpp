//https://www.programmercarl.com/kamacoder/0058.%E5%8C%BA%E9%97%B4%E5%92%8C.html
//前缀和
#include <iostream>
#include<vector>
using namespace std;

int main(){
    int size;
    cin >> size;
    vector<int> arr(size,0);
    for (int i = 0; i < size; i++){
        cin >> arr[i];
        if(i != 0){
            arr[i] += arr[i-1];
        }
    }
    int a,b;
    while(cin >> a >> b){
        if(a == 0){
            cout << arr[b] <<endl;
        }
        else{
            cout << arr[b] - arr[a-1] << endl;
        }
    }
    return 0;
}