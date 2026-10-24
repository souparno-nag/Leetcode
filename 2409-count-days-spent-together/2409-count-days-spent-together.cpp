class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // arriveAlice
        int arriveAliceMonth = stoi(arriveAlice.substr(0, 2));
        int arriveAliceDay = stoi(arriveAlice.substr(3, 2));
        // leaveAlice
        int leaveAliceMonth = stoi(leaveAlice.substr(0, 2));
        int leaveAliceDay = stoi(leaveAlice.substr(3, 2));
        // arriveBob
        int arriveBobMonth = stoi(arriveBob.substr(0, 2));
        int arriveBobDay = stoi(arriveBob.substr(3, 2));
        // leaveBob
        int leaveBobMonth = stoi(leaveBob.substr(0, 2));
        int leaveBobDay = stoi(leaveBob.substr(3, 2));
        // traverse through 365 days
        int count_days = 0;
        for (int i = 1; i <= 12; i++) {
            for (int j = 1; j <= days_per_month[i-1]; j++) {
                // date is after Alice's arrival
                if (arriveAliceMonth < i || (i == arriveAliceMonth && j >= arriveAliceDay)) {
                    // date is before Alice's departure
                    if (leaveAliceMonth > i || (leaveAliceMonth == i && j <= leaveAliceDay)) {
                        // date is after Bob's arrival
                        if (arriveBobMonth < i || (i == arriveBobMonth && j >= arriveBobDay)) {
                            // date is before Bob's departure
                            if (leaveBobMonth > i || (leaveBobMonth == i && j <= leaveBobDay)) {
                                count_days++;
                            }
                        }
                    }
                }
            }
        }
        return count_days;
    }
};