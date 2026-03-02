class Solution {
    void generatePermutations(List<Integer> current, boolean[] visited, List<List<Integer>> result, int[] nums, int n) {
        if (current.size() == n) {
            result.add(new ArrayList<>(current));
            return;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                current.add(nums[i]);
                visited[i] = true;
                generatePermutations(current, visited, result, nums, n);
                current.remove(current.size()-1);
                visited[i] = false;
            }
        }
    }
    public List<List<Integer>> permute(int[] nums) {
        int n = nums.length;
        List<List<Integer>> result = new ArrayList<>();
        boolean[] visited = new boolean[n];
        List<Integer> current = new ArrayList<>();
        generatePermutations(current, visited, result, nums, n);
        return result;
    }
}