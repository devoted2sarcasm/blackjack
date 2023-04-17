void dealerTurn(vector<Card>& deck, vector<vector<vector<Card>>>& hands) {
    hands.back()[0][0].hidden = false;

    printDealerHand(hands.back()[0]);

    while (handValue(hands.back()[0]) < 17) {
        cout << "Dealer hits a " << deck.back().rank << " of " << deck.back().suit << "." << endl;
        hands.back()[0].push_back(deck.back());
        cout << "Dealer now has: " << handValue(hands.back()[0]) << endl;
        deck.pop_back();
    }
    
    if (isBust(hands.back()[0])) {
        cout << "Dealer has busted!" << endl;
    }
    return;
}