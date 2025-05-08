


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* vh = new ListNode(0);
        vh->next = head;
        ListNode* cur = vh;
        while(cur->next != nullptr){
            if(cur->next->val == val){
                delete cur->next;
                cur->next = cur->next->next;
            }
        }
        return vh->next;
    }
};

int main(){
    
}