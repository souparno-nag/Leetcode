/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode oddEvenList(ListNode head) {
        if (head == null) return head;
        ListNode odd_current = head;
        ListNode even_current = head.next;
        ListNode even_head = head.next;
        while (even_current != null && even_current.next != null) {
            odd_current.next = even_current.next;
            odd_current = odd_current.next;
            even_current.next = odd_current.next;
            even_current = even_current.next;
        }
        odd_current.next = even_head;
        return head;
    }
}