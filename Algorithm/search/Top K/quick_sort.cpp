//使用快排分割解决top K 问题

#include <vector>
#include <iostream>

int partition(std::vector<int>& arr,int begin,int end)
{   
    int base = arr[begin];
    while(begin < end)
    {
        while(begin < end && arr[end] >= base)
            end--;
        arr[begin] = arr[end];
        while(begin < end && arr[begin] <= base)
            begin++;
        arr[end] = arr[begin];
    }
    arr[begin] = base;
    return begin;
}

void quick_sort(std::vector<int>& arr,int begin,int end,int K)
{
    if(begin > end)
    {
        return;
    }
    int index = partition(arr,begin,end);
    if(index == K - 1)
    {
        return;
    }
    else if(index < K -1)
    {
        quick_sort(arr,index + 1,end,K);
    }
    else
    {
        quick_sort(arr,begin,index - 1,K);
    }
    return;
}

void quick_sort(std::vector<int>& arr,int K)
{
    quick_sort(arr,0,arr.size()-1,K);
}

int main()
{
    std::vector<int> data = {10, 31, 45, 56, 67, 32, 44, 56, 76, 56, 89, 91, 112, 134, 456, 1, 22};
    quick_sort(data,12);
    for(int i= 0;i<12;i++)
    {
        std::cout << data[i] << ' ';
    }
    return 0;
}




