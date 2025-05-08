#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
class Solution {
public:
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* fast = head;
    for(int i = 0;i < n + 1;i++){
        fast = fast->next;
    }
    ListNode* slow = head;
    while(fast != nullptr){
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* temp = slow->next;
    slow->next = slow->next->next;
    delete temp;
    return head;
}
};

int main(){
    ListNode* pre = nullptr;
    ListNode* head = nullptr;
    for (int i = 0; i < 5; i++){
        if(i == 0){
            head = new ListNode(i+1);
            pre = head;
            continue;
        }
        ListNode* a = new ListNode(i+1);
        pre->next = a;
        pre = a;
    }
    ListNode*temp = Solution().removeNthFromEnd(head,2);
    while (temp != nullptr)
    {
        std::cout << temp->val << "->";
        temp = temp->next;
    }
    return 0;
}