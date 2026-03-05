class Solution {
public:
    bool judgeCircle(string moves) {
        int ver = 0, hor = 0;
        for (int i = 0; i < moves.length(); i++) {
            if (moves[i] == 'U') {
                ver++;
            } else if (moves[i] == 'D') {
                ver--;
            } else if (moves[i] == 'R') {
                hor++;
            } else if (moves[i] == 'L') {
                hor--;
            }
        }
        return (ver == 0) && (hor == 0);
    }
};