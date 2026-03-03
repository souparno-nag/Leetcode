/**
 * // This is MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface MountainArray {
 *     public int get(int index) {}
 *     public int length() {}
 * }
 */
 
// class Solution {
//     int max (int a, int b) {
//         return (a >= b) ? a : b;
//     }
//     int min (int a, int b) {
//         return (a <= b) ? a : b;
//     }
//     int minValidIndex (int a, int b) {
//         if (a == -1) return b;
//         if (b == -1) return a;
//         return min(a, b);
//     }
//     int binarySearch(int low, int high, int target, MountainArray mountainArr) {
//         if (low > high) return -1;
//         int curr_index = (low + high) / 2;
//         int curr = mountainArr.get(curr_index);
//         if (low == high) return (curr == target) ? low : -1;
//         if (curr == target) {
//             int leftResult = binarySearch(low, curr_index-1, target, mountainArr);
//             if (leftResult != -1) return leftResult;
//             return curr_index;
//         }
//         int prev = mountainArr.get(max(low, curr_index-1)), next = mountainArr.get(min(high, curr_index+1));
//         if (curr >= prev && curr >= next) { // peak
//             if (target > curr) return -1;
//             return minValidIndex(binarySearch(low, curr_index-1, target, mountainArr), binarySearch(curr_index+1, high, target, mountainArr));
//         } else if (curr >= prev) { // left side
//              if (curr > target) return minValidIndex(binarySearch(low, curr_index-1, target, mountainArr), binarySearch(curr_index+1, high, target, mountainArr));
//             if (curr < target) return binarySearch(curr_index+1, high, target, mountainArr);
//         } else if (curr >= next) { // right side
//              if (curr < target) return binarySearch(low, curr_index-1, target, mountainArr);
//             if (curr > target) return minValidIndex(binarySearch(low, curr_index-1, target, mountainArr), binarySearch(curr_index+1, high, target, mountainArr));
//         }
//         return -1;
//     }
//     public int findInMountainArray(int target, MountainArray mountainArr) {
//         int n = mountainArr.length();
//         return binarySearch(0, n-1, target, mountainArr);
//     }
// }

class Solution {
    public int findInMountainArray(int target, MountainArray mountainArr) {
        int n = mountainArr.length();
        
        // Step 1: Find peak
        int lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        int peak = lo;
        
        // Step 2: Binary search on left (ascending) side
        int result = binarySearchAsc(0, peak, target, mountainArr);
        if (result != -1) return result;
        
        // Step 3: Binary search on right (descending) side
        return binarySearchDesc(peak + 1, n - 1, target, mountainArr);
    }
    
    int binarySearchAsc(int lo, int hi, int target, MountainArray mountainArr) {
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }
    
    int binarySearchDesc(int lo, int hi, int target, MountainArray mountainArr) {
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val > target) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }
}