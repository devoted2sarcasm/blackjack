void playerTurns(vector<vector<vector<Card>>>& hands, vector<Card>& deck, vector<int>& playerMoney, vector<int> bets, int numPlayers) {
    if (isBlackjack(hands.back())) {
        cout << "Dealer has blackjack!" << endl;
        return;
    }
    else {
        for (int i = 0; i < (hands.size() - 1); i++) {
            singleTurn(hands[i], playerMoney[i], bets[i], deck);
        }
    }
}