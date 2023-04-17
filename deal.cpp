vector<vector<vector<Card>>> dealCards(vector<Card>& deck, int numPlayers) {
    vector<vector<vector<Card>>> hands;
    for (int i = 0; i < numPlayers; i++) {
        hands[i][0].push_back(deck.back());
    }
    hands.back()[0].push_back(deck.back());
    for (int i = 0; i < numPlayers; i++) {
        hands[i][0].push_back(deck.back());
    }
    hands.back()[0].push_back(deck.back());
    hands.back()[0][0].hidden = true;

    for (int i = 0; i < numPlayers; i++) {
        cout << "########## Player " << i+1 << " has: " << endl;
        cout << hands[i][0][0].rank << " of " << hands[i][0][0].suit << endl;
        cout << hands[i][0][1].rank << " of " << hands[i][0][1].suit << endl;
    }

    printDealerHand(hands.back()[0]);

    return hands;
}

