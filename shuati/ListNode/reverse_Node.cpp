//反转相邻的节点
//[1,2,3,4,5,6,7,8,9] ----> [2,1,4,3,6,5,8,7,9]

#include<iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head) return head;
        ListNode* vh = new  ListNode(0);
        vh->next = head;
        ListNode* cur = vh;
        while(cur->next!=nullptr && cur->next->next!=nullptr){
            ListNode* temp = cur->next;
            cur->next = temp->next;
            temp->next = temp->next->next;
            cur->next->next = temp;
            cur = cur->next->next;
        }
        return vh->next;
    }
};

int main(){
    ListNode* pre = nullptr;
    ListNode* head = nullptr;
    for (int i = 0; i < 9; i++){
        if(i == 0){
            head = new ListNode(i+1);
            pre = head;
            continue;
        }
        ListNode* a = new ListNode(i+1);
        pre->next = a;
        pre = a;
    }
    ListNode*temp = Solution().swapPairs(head);
    while (temp != nullptr)
    {
        std::cout << temp->val << "->";
        temp = temp->next;
    }
    return 0;
}