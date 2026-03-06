/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    int count = 0;
    while (count != n) {
        fast = fast -> next;
        count++;
    }
    if (fast == NULL) {
        struct ListNode* temp = head;
        head = head -> next;
        free(temp);
        return head;
    }
    while (fast -> next != NULL) {
        fast = fast -> next;
        slow = slow -> next;
    }
    struct ListNode* temp = slow -> next;
    slow -> next = temp -> next;
    free(temp);
    return head;
}