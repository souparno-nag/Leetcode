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
    public void reorderList(ListNode head) {
        if (head == null || head.next == null) return;
        // find middle
        ListNode slow = head, fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode mid = slow.next;
        slow.next = null;
        // reverse second half
        ListNode curr = mid, last = null;
        while (curr != null) {
            ListNode temp = curr;
            curr = curr.next;
            temp.next = last;
            last = temp;
        }
        // merge the two
        curr = head;
        while (curr != null && last != null) {
            ListNode temp1 = curr.next;
            ListNode temp2 = last.next;
            curr.next = last;
            last.next = temp1;
            curr = temp1;
            last = temp2;
        }
    }
}