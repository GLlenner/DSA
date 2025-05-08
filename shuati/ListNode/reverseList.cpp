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
    ListNode* reverseList(ListNode* head) {
        if(!head)return head;
        ListNode* suf = nullptr;
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(cur!= nullptr){
            suf = cur->next;
            cur->next = pre;
            pre = cur;
            cur = suf;
        }
        return pre;
    }
};

int main(){
    ListNode* a = new ListNode(1);
    ListNode* b = new ListNode(2);
    a->next = b;
    ListNode*temp = Solution().reverseList(a);
    while (temp != nullptr)
    {
        std::cout << temp->val << "->";
        temp = temp->next;
    }
    return 0;
}