/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (k == 0 || head == nullptr || head -> next == nullptr) return head;
        int n = 0;
        ListNode* temp = head;
        while (temp != nullptr) {
            temp = temp -> next;
            n++;
        }
        k = k%n;
        if (k == 0) return head;
        k = n - k;
        ListNode* last = head;
        while (last -> next != nullptr) last = last -> next;
        ListNode* curr = head;
        for (int i = 1; i < k; i++) {            
            curr = curr -> next;
        }
        last -> next = head;
        head = curr -> next;
        curr -> next = nullptr;
        return head;
    }
};