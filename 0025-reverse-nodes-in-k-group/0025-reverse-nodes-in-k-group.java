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
    boolean exists(ListNode root, int k) {
        int count = 0;
        while (root != null) {
            root = root.next;
            count++;
        }
        return (count >= k);
    }
    public ListNode reverseKGroup(ListNode head, int k) {
        if (head == null || head.next == null) return head;
        ListNode curr = head, last = null;
        int count = 0;
        // reverse k nodes
        while (curr != null && count != k) {
            ListNode temp = curr.next;
            curr.next = last;
            last = curr;
            curr = temp;
            count++;
        }
        // recursively call function to reverse the rest
        if (exists(curr, k)) {
            head.next = reverseKGroup(curr, k);
        } else {
            head.next = curr;
        }
        return last;
    }
}