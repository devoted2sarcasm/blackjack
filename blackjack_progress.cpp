//hitting problems

//blackjack

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;


struct Card {
    string rank;
    string suit;
    int value;
    bool hidden; // indicates whether the card is hidden or not

    Card(string r, string s) {
        rank = r;
        suit = s;
        if (r == "Ace") {
            value = 11;
        } else if (r == "King" || r == "Queen" || r == "Jack" || r == "10") {
            value = 10;
        } else if (r == "9") {
        	value = 9;
        } else if (r == "8") {
        	value = 8;
        } else if (r == "7") {
        	value = 7;
        } else if (r == "6") {
        	value = 6;
        } else if (r == "5") {
        	value = 5;
        } else if (r == "4") {
        	value = 4;
        } else if (r == "3") {
        	value = 3;
        } else if (r == "2") {
        	value = 2;
        } else {
        	value = 21;
        	cout << "Bad deck build" << endl << endl;
        }
    }
};

//build deck of cards with user unput, up to 8 decks
vector<Card> buildDeck(int numDecks) {
    vector<Card> deck;
    vector<string> ranks = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    for (int i = 0; i < numDecks; i++) {
        for (string s : suits) {
            for (string r : ranks) {
                Card c(r, s);
                deck.push_back(c);
            }
        }
    }
    return deck;
}

//shuffle deck
void shuffleDeck(vector<Card>& deck) {
    random_device rd;
    default_random_engine g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

//choose number of players, up to 7
int choosePlayers() {
    int numPlayers;
    cout << "How many players? (1-7): ";
    cin >> numPlayers;
    while (numPlayers < 1 || numPlayers > 7) {
        cout << "Invalid number of players. Please enter a number between 1 and 7: ";
        cin >> numPlayers;
    }
    return numPlayers;
}

//choose number of decks, up to 8
int chooseDecks() {
    int numDecks;
    cout << "How many decks? (1-8): ";
    cin >> numDecks;
    while (numDecks < 1 || numDecks > 8) {
        cout << "Invalid number of decks. Please enter a number between 1 and 8: ";
        cin >> numDecks;
    }
    return numDecks;
}

//choose starting money
int chooseMoney() {
    int startingMoney;
    cout << "How much money does each player start with? ";
    cin >> startingMoney;
    while (startingMoney < 1) {
        cout << "Invalid amount of money. Please enter a number greater than 0: ";
        cin >> startingMoney;
    }
    return startingMoney;
}

//deal cards to players, returning vector of cards to manipulate with hits, stands, etc, dealer is last player, first card for dealer hidden
vector<vector<Card>> dealCards(vector<Card>& deck, int numPlayers) {
    vector<vector<Card>> hands;
    for (int i = 0; i < numPlayers; i++) {
        vector<Card> hand;
        for (int j = 0; j < 2; j++) {
            hand.push_back(deck.back());
            deck.pop_back();
        }
        hands.push_back(hand);
    }
    vector<Card> dealerHand;
    for (int j = 0; j < 2; j++) {
        dealerHand.push_back(deck.back());
        deck.pop_back();
    }
    dealerHand[0].hidden = true;
    hands.push_back(dealerHand);
    return hands;
}

//print cards in hand
void printHand(vector<Card> hand) {
    for (Card c : hand) {
        cout << c.rank << " of " << c.suit << endl;
    }
}

//print cards in dealer's hand
void printDealerHand(vector<Card> hand) {
    if (hand[0].hidden) {
        cout << "##########  Dealer's hand:" << endl << endl;
        cout << "Hidden" << endl;
        cout << hand[1].rank << " of " << hand[1].suit << endl << endl;
    }
    else {
        cout << "##########  Dealer's hand:" << endl << endl;
        printHand(hand);
        cout << endl;
    }   
}

//print cards in player's hands
void printPlayerHands(vector<vector<Card>> hands) {
    for (int i = 0; i < (hands.size() - 1); i++) {
        cout << "##########  Player " << i + 1 << "'s hand:" << endl << endl;
        printHand(hands[i]);
        cout << endl;
    }
}

//print cards in all hands
void printAllHands(vector<vector<Card>> hands) {
    printPlayerHands(hands);
    printDealerHand(hands.back());
}

//calculate hand value
int handValue(vector<Card> hand) {
    int value = 0;
    for (Card c : hand) {
        value += c.value;
    }
    return value;
}
//better version, other to be deprecated
int get_hand_value(const vector<Card>& hand, bool soft) {
    int value = 0;
    int num_aces = 0;
    for (const auto& card : hand) {
        if (card.rank == "Ace") {
            num_aces++;
            value += 11;
        } else if (card.rank == "King" || card.rank == "Queen" || card.rank == "Jack") {
            value += 10;
        } else {
            value += stoi(card.rank);
        }
    }
    while (value > 21 && num_aces > 0) {
        value -= 10;
        num_aces--;
    }
    if (soft && num_aces > 0 && value <= 11) {
        value += 10;
    }
    return value;
}


//check if hand is a blackjack
bool isBlackjack(vector<Card> hand) {
    return hand.size() == 2 && handValue(hand) == 21;
}

//check if hand is a pair
bool isPair(vector<Card> hand) {
    return hand.size() == 2 && hand[0].rank == hand[1].rank;
}

//check for bust, allowing for aces to be 1 or 11
bool isBust(vector<Card> hand) {
    int value = handValue(hand);
    if (value > 21) {
        for (Card c : hand) {
            if (c.rank == "Ace") {
                value -= 10;
                if (value <= 21) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

//players turns, checking for opportunity to split or double down, then offering to hit or stand (on each hand if split), no additional hits if double, and checking for bust
void playerTurns(vector<Card>& deck, vector<vector<Card>>& hands, int numPlayers, vector<int>& playerMoney, int& bet) {
    for (int i = 0; i < numPlayers; i++) {
        if (isBlackjack(hands[i])) {
            cout << "Player " << i+1 << " has blackjack!" << endl;
            playerMoney[i] += bet * 1.5;
            continue;
        }
        if (isPair(hands[i])) {
            cout << "Player " << i+1 << " has a pair of " << hands[i][0].rank << "s." << endl;
            cout << "Would you like to split? (y/n): ";
            char split;
            cin >> split;
            //if yes, all remaining players hands, including dealer, should be pushed back one spot, so that the current player plays 2 hands before progressing to the next
            //i may not have this implemented in time, but i need to get the rest working properly before polishing. as long as i can get an additional hand to be dealt, we're good to start.

            if (split == 'y') {
                vector<Card> newHand;
                //removes second card from hand and adds it to new hand
                newHand.push_back(hands[i][1]);
                hands[i].pop_back();
                //deals new card to each hand
                hands[i].push_back(deck.back());
                deck.pop_back();
                newHand.push_back(deck.back());
                deck.pop_back();
                //adds new hand to hands vector
                hands.push_back(newHand);
                numPlayers++;
                playerMoney.push_back(playerMoney[i]);
                cout << "Player " << i+1 << " has been split into Player " << i+1 << " and Player " << numPlayers << "." << endl;
            }
        }

        int j = 0;
        while (j < hands[i].size() && !isBust(hands[i])) {
            cout << "Player " << i+1 << "'s hand (value: " << get_hand_value(hands[i], false) << "):" << endl;
            printHand(hands[i]);
            if (j == 0) {
                cout << "Would you like to double down? (y/n): ";
                char doubleDown;
                cin >> doubleDown;
                if (doubleDown == 'y') {
                    bet *= 2;
                    hands[i].push_back(deck.back());
                    deck.pop_back();
                    cout << "Player " << i+1 << "'s hand (value: " << get_hand_value(hands[i], false) << "):" << endl;
                    printHand(hands[i]);
                    if (isBust(hands[i])) {
                        cout << "Player " << i+1 << " has busted!" << endl;
                        playerMoney[i] -= bet;
                    }
                    break;
                }
            }
            cout << "Would you like to hit? (y/n): ";
            char hit;
            cin >> hit;
            if (hit == 'n') {
                break;
            }
            hands[i].push_back(deck.back());
            deck.pop_back();
            cout << "Player " << i+1 << "'s hand (value: " << get_hand_value(hands[i], false) << "):" << endl;
            printHand(hands[i]);
            j++;
        }

        if (isBust(hands[i])) {
            cout << "Player " << i+1 << " has busted!" << endl;
            playerMoney[i] -= bet;
        }

        cout << "------------------------" << endl;
    }
}


//dealer's turn, checking for blackjack, then hitting until 17 or bust
void dealerTurn(vector<Card>& deck, vector<vector<Card>>& hands) {
    hands.back()[0].hidden = false;
    printDealerHand(hands.back());
    if (isBlackjack(hands.back())) {
        cout << "Dealer has blackjack!" << endl;
        return;
    }
    while (handValue(hands.back()) < 17) {
        hands.back().push_back(deck.back());
        deck.pop_back();
        printDealerHand(hands.back());
    }
    if (isBust(hands.back())) {
        cout << "Dealer has busted!" << endl;
    }
}

//players make bets before deal
void makeBets(vector<int>& playerMoney, int& bet) {
    for (int i = 1; i < playerMoney.size(); i++) {
        cout << "Player " << i << ", you have $" << playerMoney[i] << "." << endl;
        cout << "How much would you like to bet? ";
        cin >> bet;
        while (bet < 1 || bet > playerMoney[i]) {
            cout << "Invalid bet. Please enter a number between 1 and $" << playerMoney[i] << ": ";
            cin >> bet;
        }
        playerMoney[i] -= bet;
    }
}


//check for winner, paying out if player wins
void checkWinner(vector<vector<Card>> hands, vector<int>& playerMoney, int bet) {
    int dealerValue = handValue(hands.back());
    if (isBust(hands.back())) {
        for (int i = 0; i < (hands.size()-1); i++) {
            if (!isBust(hands[i])) {
                cout << "Player " << i+1 << " wins!" << endl;
                playerMoney[i] += bet * 2;
            }
        }
    }
    else {
        for (int i = 0; i < (hands.size()-1); i++) {
            int playerValue = handValue(hands[i]);
            if (playerValue > dealerValue && !isBust(hands[i])) {
                cout << "Player " << i+1 << " wins!" << endl;
                playerMoney[i] += bet * 2;
            }
            else if (playerValue == dealerValue) {
                cout << "Player " << i+1 << " pushes." << endl;
                playerMoney[i] += bet;
            }
            else {
                cout << "Player " << i+1 << " loses." << endl;
            }
        }
    }
}

    //as originally written, this function would have the players lose even if the dealer busted, which is obv not correct.
/*    for (int i = 0; i < (hands.size()-1); i++) {
        int playerValue = handValue(hands[i]);
        if (playerValue > dealerValue && !isBust(hands[i])) {
            cout << "Player " << i+1 << " wins!" << endl;
            playerMoney[i] += bet * 2;
        }
        else if (playerValue == dealerValue) {
            cout << "Player " << i+1 << " pushes." << endl;
            playerMoney[i] += bet;
        }
        else {
            cout << "Player " << i+1 << " loses." << endl;
        }
    }
}
*/


//check if player wants to play again
bool playAgain() {
    cout << "Would you like to play again? (y/n): ";
    char again;
    cin >> again;
    return again == 'y';
}

//main function
int main() {
    int deckcount = chooseDecks();
    //initialize deck
    vector<Card> deck = buildDeck(deckcount);
    shuffleDeck(deck);
    //initialize players
    vector<int> playerMoney = { 0 };
    int numPlayers = 0;
    cout << "How many players? ";
    cin >> numPlayers;
    for (int i = 0; i < numPlayers; i++) {
        playerMoney.push_back(100);
    }
    //initialize bet
    int bet = 0;
    //play game
    bool playing = true;
    while (playing) {
        //make bets
        makeBets(playerMoney, bet);
        //deal cards
        vector<vector<Card>> hands = dealCards(deck, numPlayers);
        //print hands
        printAllHands(hands);
        //player turns
        playerTurns(deck, hands, numPlayers, playerMoney, bet);
        //dealer turn
        dealerTurn(deck, hands);
        //print hands
        printAllHands(hands);
        //check winner
        checkWinner(hands, playerMoney, bet);
        //check if players want to play again
        playing = playAgain();
    }
    return 0;
}
