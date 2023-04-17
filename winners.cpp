void checkWinners(vector<vector<vector<Card>>> hands, vector<int>& playerMoney, vector<int>& bets) {
    int dealerValue = handValue(hands.back());
    for (int i = 0, i < hands.size()-1; i++) {
        for (int j = 0; j < hands[i].size(), j++) {
            if (handValue(hands[i][j]) > dealerValue && !isBust(hands[i][j])) {
                cout << "Player " << i+1 << ", hand " << j+1 << " wins!" << endl;
                playerMoney[i] += bets[i] * 2;
            }
            else if (handValue(hands[i][j]) == dealerValue) {
                cout << "Player " << i+1 << ", hand " << j+1 << " pushes." << endl;
                playerMoney[i] += bets[i];
            }
            else {
                cout << "Player " << i+1 << ", hand " << j+1 << " loses." << endl;
                playerMoney[i] -= betCounts[i] * bets[i];
            }
        }
    }
    for (int i = 0; i < playerMoney.size(); i++) {
        cout << "Player " << i+1 << " now has: $" << playerMoney[i] << endl;
    }
    bets.clear();
    return
}