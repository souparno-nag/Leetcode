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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* temp = head;
        int count = 0;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        count -= n;
        if (count == 0) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }
        ListNode* dummy = new ListNode(0, head);
        temp = dummy;
        while (count > 0) {
            temp = temp->next;
            count--;
        }
        ListNode* delNode = temp->next;
        temp->next = delNode->next;
        delete delNode;
        return dummy->next;
    }
};