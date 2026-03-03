class Solution {
    public List<Integer> spiralOrder(int[][] matrix) {
        int m = matrix.length, n = matrix[0].length;
        List<Integer> result = new ArrayList<>();
        boolean[][] visited = new boolean[m][n];
        int[] dr = {0, 1, 0, -1};
        int[] dc = {1, 0, -1, 0};
        int r = 0, c = 0, dir = 0;
        int count = 0;
        while (count < m*n) {
            result.add(matrix[r][c]);
            visited[r][c] = true;
            int newR = r + dr[dir], newC = c + dc[dir];
            if (newR >= 0 && newR < m && newC >= 0 && newC < n && !visited[newR][newC]) {
                r = newR; c = newC;
            } else {
                dir = (dir + 1)%4;
                r += dr[dir]; c += dc[dir];
            }
            count++;
        }
        return result;
    }
}