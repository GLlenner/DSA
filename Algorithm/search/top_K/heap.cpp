//使用大小根堆解决top K 问题


#include<queue>
#include<vector>
#include<iostream>
#include<functional>

int digitSum(int num)
{
    int sum = 0;
    while (num > 0) {
        sum += num % 10;  // 提取最后一位数字
        num /= 10;         // 移除最后一位
    }
    return sum;
}

int main()
{   
    std::vector<int> data = {10, 31, 45, 56, 67, 32, 44, 56, 76, 56, 89, 91, 112, 134, 456, 1, 22};
    
    int K = 17;
    //问题：求data中最小的 K 个元素
    std::priority_queue<int> min_pq;

    //问题：求data中最大的 K 个元素
    std::priority_queue<int,std::vector<int>,std::greater<int>> max_pq;
    
    //问题：求data中位数和最大的 K 个元素
    std::priority_queue<int,std::vector<int>,std::function<bool(int,int)>> pq(
        [](int a,int b)->bool{
            return digitSum(a) > digitSum(b);
        }
    );

    int i = 0;
    for(;i<K;i++)
    {
        min_pq.push(data[i]);
        max_pq.push(data[i]);
        pq.push(data[i]);
    }
    for(;i<data.size();i++)
    {
        if(min_pq.top() > data[i])
        {
            min_pq.pop();
            min_pq.push(data[i]);
        }
        if(max_pq.top() < data[i])
        {
            max_pq.pop();
            max_pq.push(data[i]);
        }
        if(digitSum(pq.top()) < digitSum(data[i]))
        {
            pq.pop();
            pq.push(data[i]);
        }
    }
    for(int i = 0;i< K;i++)
    {
        std::cout << min_pq.top() << " ";
        min_pq.pop();
        
    }
    std::cout << std::endl;
    for(int i = 0;i< K;i++)
    {
        std::cout << max_pq.top() << " ";
        max_pq.pop();
    }
    std::cout << std::endl;
    for(int i = 0;i< K;i++)
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }
}