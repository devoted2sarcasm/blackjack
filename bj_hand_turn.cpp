//function for a single player taking a full turn
  
void singleTurn(vector<vector<Card>>& playerHands, int& playerMoney, int bet, vector<Card>& deck) {
    for (int i = 0; i < playerHands.size(); i++) {
        while (isPair(playerHands[i])) {
            cout << "Hand " << i+1 << " has a pair of " << playerHands[i][0].rank << "s." << endl;
            cout << "Would you like to split? (y/n): " << endl;
            char split;
            cin >> split;
            if (split == 'y') {
                if (playerMoney < bet) {
                    cout << "You don't have enough money to split" << endl;
                    break;
                }
                else {
                    betCounts++;
                    playerMoney -= bet;
                    vector<Card> newHand;
                    newHand.push_back(playerHands[i][1]);
                    playerHands[i].pop_back();
                    playerHands.insert(i+1, newHand);
                    playerHands[i].push_back(deck.back());
                    deck.pop_back();
                    playerHands[i+1].push_back(deck.back());
                    deck.pop_back();
                    continue;
                }
            }
            else {
                break;
            }
        }
        hitStand(playerHands[i], deck);
    }
}

void hitStand(vector<Card>& hand, vector<Card>& deck) {
    cout << "Hand is: " << handValue(hand) << endl;
    cout << "Would you like to hit? (y/n): " << endl;
    char hit;
    cin >> hit;
    if (hit == 'y') {

        hand.push_back(deck.back());
        deck.pop_back();
        cout << "New hand value: " << handValue(hand) << endl;

        if (isBust(hand)) {
            cout << "Hand has busted!" << endl;
            return;
        }
        else {
            hitStand(hand, deck);
        }
    }
    else {
        return;
    }
}