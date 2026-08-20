/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    ListNode* findIntersection(ListNode* shorter, ListNode* longer, int diff) {
        while (diff) {
            diff--;
            longer = longer->next;
        }
        while (shorter != longer) {
            shorter = shorter->next;
            longer = longer->next;
        }
        return shorter;
    }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int len1 = 0, len2 = 0;
        ListNode* temp = headA;
        while(temp != nullptr) {
            len1++;
            temp = temp->next;
        }
        temp = headB;
        while(temp != nullptr) {
            len2++;
            temp = temp->next;
        }
        if (len1 > len2) return findIntersection(headB, headA, len1-len2);
        return findIntersection(headA, headB, len2-len1);
    }
};