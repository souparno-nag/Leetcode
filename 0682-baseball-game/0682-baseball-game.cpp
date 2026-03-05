class Solution {
public:
    int calPoints(vector<string>& operations) {
        int idx = 0;
        vector<int> arr;
        for (int i = 0; i < operations.size(); i++) {
            if (operations[i] == "+") {
                arr.push_back(arr[idx-1] + arr[idx-2]);
                idx++;
            } else if (operations[i] == "D") {
                arr.push_back(arr[idx-1] * 2);
                idx++;
            } else if (operations[i] == "C") {
                arr.pop_back();
                idx--;
            } else {
                arr.push_back(stoi(operations[i]));
                idx++;
            }
        }
        int sum = 0;
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
        }
        return sum;
    }
};