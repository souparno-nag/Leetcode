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
    ListNode* deleteMiddle(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return NULL;
        }
        // find middle node
        ListNode *slow = head, *fast = head;
        fast = (fast->next)->next;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = (fast->next)->next;
        }
        ListNode* middle = slow->next;
        // delete
        slow->next = middle->next;
        middle->next = NULL;
        delete middle;
        return head;
    }
};