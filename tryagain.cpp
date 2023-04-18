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

void buildDeck(int numDecks);
void shuffleDeck(vector<Card>& deck);
int choosePlayers();
int chooseDecks();
void chooseMoney();
vector<vector<vector<Card>>> dealCards(vector<Card>& deck, int numPlayers);
void printHand(vector<Card> hand);
void printDealerHand(vector<Card> hand);
int handValue(vector<Card> hand);
bool isBlackjack(vector<Card> hand);
bool isPair(vector<Card> hand);
bool isBust(vector<Card> hand);
void playerTurns(vector<vector<vector<Card>>>& hands, vector<Card>& deck, vector<int>& playerMoney, vector<int> bets, int numPlayers);
void dealerTurn(vector<Card>& deck, vector<vector<vector<Card>>>& hands);
void make_bets(vector<int>& playerMoney, vector<int>&bets, int numPlayers);
void checkWinner(vector<vector<vector<Card>>> hands, vector<int>& playerMoney, vector<int>& bets);
void singleTurn(vector<vector<Card>>& playerHands, int& playerMoney, int bet, vector<Card>& deck);
void hitStand(vector<Card>& hand, vector<Card>& deck);
bool playAgain();

//build deck of cards with user unput, up to 8 decks
void buildDeck(int numDecks, vector<Card>& deck) {
    //vector<Card> deck;
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
    //return deck;
}

//shuffle deck
void shuffleDeck(vector<Card>& deck) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    //random_device rd;
    //default_random_engine g(rd());
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
    cout << "Deck shuffled." << endl;
}

//choose number of players, up to 7
int choosePlayers() {
    int numPlayers;
    cout << "How many players? (1-7): ";
    //cin >> numPlayers;
    numPlayers = 3;
    while (numPlayers < 1 || numPlayers > 7) {
        cout << "Invalid number of players. Please enter a number between 1 and 7: ";
        cin >> numPlayers;
    }
    cout << numPlayers << " players chosen." << endl;
    return numPlayers;
}

//choose number of decks, up to 8
int chooseDecks() {
    int numDecks;
    cout << "How many decks? (1-8): ";
    //cin >> numDecks;
    numDecks = 2;
    while (numDecks < 1 || numDecks > 8) {
        cout << "Invalid number of decks. Please enter a number between 1 and 8: ";
        cin >> numDecks;
    }
    cout << numDecks << " decks chosen." << endl;
    return numDecks;
}

//choose starting money
void chooseMoney(int numPlayers, vector<int>& playerMoney) {
    //vector<int> playerMoney = {0};
    int startingMoney;
    cout << "How much money does each player start with? ($1-$10,000)";
    //cin >> startingMoney;
    startingMoney = 30;
    while (startingMoney < 1 || startingMoney > 10000) {
        cout << "Invalid amount of money. Please enter a valid number: ";
        cin >> startingMoney;
    }
    
    for (int i = 0; i < numPlayers; i++) {
        playerMoney[i] = startingMoney;
        cout << "Player " << i+1 << " has been funded with $" << playerMoney[i] << endl;
    }
    //return playerMoney;
}

//deal cards to players, returning vector of cards to manipulate with hits, stands, etc, dealer is last player, first card for dealer hidden
vector<vector<vector<Card>>> dealCards(vector<Card>& deck, int numPlayers) {
    vector<vector<vector<Card>>> hands;

    hands.reserve(numPlayers+1);

    for (int i = 0; i < numPlayers; i++) {
        hands[i].reserve(32);
        for (int j = 0; j < 32; j++) {
            hands[i][j].reserve(10);
        }
    }

    vector<vector<Card>> players;
    players.reserve(numPlayers+1);
    
    cout << "Temporary vector reserved." << endl;
    
    for (int i = 0; i < numPlayers; i++) {
        players[i].reserve(10);
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < (numPlayers+1); j++) {
            cout << "dealing card to player " << j+1 << endl;
            players[j][i] = deck.back();
            deck.pop_back();
        }
    }
    
    for (int i = 0; i < (numPlayers+1); i++) {
        hands[i].push_back(players[i]);
    }

    hands.back()[0][0].hidden = true;

    for (int i = 0; i < numPlayers; i++) {
        cout << "########## Player " << i+1 << " has: " << endl;
        cout << hands[i][0][0].rank << " of " << hands[i][0][0].suit << endl;
        cout << hands[i][0][1].rank << " of " << hands[i][0][1].suit << endl;
    }

    printDealerHand(hands.back()[0]);

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
/*
void printPlayerHands(vector<vector<vector<Card>>> hands) {
    for (int i = 0; i < (hands.size() - 1); i++) {
        cout << "##########  Player " << i + 1 << "'s hand:" << endl << endl;
        printHand(hands[i]);
        cout << endl;
    }
}
*/

//print cards in all hands
/*
void printAllHands(vector<vector<vector<Card>>> hands) {
    printPlayerHands(hands);
    printDealerHand(hands.back());
}
*/

//calculate hand value
int handValue(vector<Card> hand) {
    int value = 0;
    for (Card c : hand) {
        value += c.value;
    }
    int num_aces = 0;
    for (Card c : hand) {
        if (c.rank == "Ace") {
            num_aces++;
        }
    }
    if (value > 21 && num_aces > 0) {
        value -= 10;
        num_aces--;
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
        return true;
    }
    return false;
}

//players turns, checking for opportunity to split or double down, then offering to hit or stand (on each hand if split), no additional hits if double, and checking for bust
//functionality needs to be added to properly handle splits as far as the hands vector and bets vector go. inserts seem to be the best idea, as the dealer's hand will always be last, but there's a lot of counters and nuance to how to handle which hands belong to which player if more than one are splitting
//maybe a new nested vector, where the first element is all of player 1's hands, the second element is all of player 2's hands, and each time a hand is split, you'll have to change the bets vector to accomodate the new bet, and then you'll need to keep track of how many of the player's hands <beat, push, lose> and multiply his winnings accordingly and add them back to the playerMoney vector

void playerTurns(vector<vector<vector<Card>>>& hands, vector<Card>& deck, vector<int>& playerMoney, vector<int> bets, int numPlayers) {
    if (isBlackjack(hands.back()[0])) {
        cout << "Dealer has blackjack!" << endl;
        return;
    }
    else {
        for (int i = 0; i < (hands.size() - 1); i++) {
            singleTurn(hands[i], playerMoney[i], bets[i], deck);
        }
    }
}

//dealer's turn, checking for blackjack, then hitting until 17 or bust
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

/*
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
*/

//second attempt at bets, using a vector of bets instead of modifying playerMoney
void make_bets(vector<int>& playerMoney, vector<int>&bets, int numPlayers) {
    bets = {0};
    bets.reserve(7);
    for (int i = 0; i < numPlayers; i++) {
        if (playerMoney[i] == 0) {
            cout << "Player " << i+1 << " has no money left, how much would you like to add?" << endl;
            int addMoney;
            //cin >> addMoney;
            addMoney = 100;
            while (addMoney < 1) {
                cout << "Invalid amount. Please enter a number greater than 0: ";
                cin >> addMoney;
            }
            playerMoney[i] += addMoney;
        }
        cout << "Player " << i+1 << ", you have $" << playerMoney[i] << "." << endl;
        cout << "How much would you like to bet? ";
        int bet;
        //cin >> bet;
        bet = 20;
        while (bet < 1 || bet > playerMoney[i]) {
            cout << "Invalid bet. Please enter a number between 1 and $" << playerMoney[i] << ": ";
            cin >> bet;
        }
        bets[i] = bet;
        playerMoney[i] -= bet;
        //bets[i] = bet;
    }
    //debug print all bets
    for (int i = 0; i < numPlayers; i++) {
        cout << "Player " << i+1 << " bet $" << bets[i] << endl;
    }
}


//check for winner, paying out if player wins
void checkWinner(vector<vector<vector<Card>>> hands, vector<int>& playerMoney, vector<int>& bets) {
    int dealerValue = handValue(hands.back()[0]);
    for (int i = 0; i < hands.size()-1; i++) {
        for (int j = 0; j < hands[i].size(); j++) {
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
            }
        }
    }
    for (int i = 0; i < playerMoney.size(); i++) {
        cout << "Player " << i+1 << " now has: $" << playerMoney[i] << endl;
    }
    bets.clear();
    return;
}

//function for a single player taking a full turn
  
void singleTurn(vector<vector<Card>>& playerHands, int& playerMoney, int bet, vector<Card>& deck) {
    for (int i = 0; i < playerHands.size(); i++) {
        while (isPair(playerHands[i])) {
            cout << "Hand " << i+1 << " has a pair of " << playerHands[i][0].rank << "s." << endl;
            cout << "Would you like to split? (y/n): " << endl;
            char split;
            //cin >> split;
            split = 'y';
            if (split == 'y') {
                if (playerMoney < bet) {
                    cout << "You don't have enough money to split" << endl;
                    break;
                }
                else {
                    playerMoney -= bet;
                    vector<Card> newHand;
                    newHand.push_back(playerHands[i][1]);
                    playerHands[i].pop_back();
                    playerHands.push_back(newHand);
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
    return;
}

void hitStand(vector<Card>& hand, vector<Card>& deck) {
    cout << "Hand is: " << handValue(hand) << endl;
    cout << "Would you like to hit? (y/n): " << endl;
    char hit;
    //cin >> hit;
    hit = 'y';
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


//check if player wants to play again
bool playAgain() {
    cout << "Would you like to play again? (y/n): ";
    char again;
    //cin >> again;
    again = 'y';
    return again == 'y';
}

//debug print deck
void showDeck (vector<Card> deck) {
    for (int i = 0; i < deck.size(); i++) {
        cout << deck[i].rank << " of " << deck[i].suit << ": worth " << deck[i].value << endl;
    }
    cout << "######################################" << endl << endl;
}

vector<int> initializeBets(int numPlayers) {
    vector<int> bets = {0};
    for (int i = 0; i < numPlayers; i++) {
        bets.push_back(0);
        cout << "Player " << i+1 << "bet structure initialized." << endl;
    }
    return bets;
}


int main() {

    //initialize all my vectors and reserve space to prevent undefined behavior and memory leak/reusage
    vector<Card> deck;
    deck.reserve(52*8);

    vector<int> playerMoney;
    playerMoney.reserve(7);

    vector<int> bets;
    bets.reserve(7);



    //start with how many decks to use
    int deckCount = chooseDecks();

    //initialize deck using deckCount
    buildDeck(deckCount, deck);

    //debug print deck
    //showDeck(deck);

    //shuffle and print again for debug
    shuffleDeck(deck);
    //showDeck(deck);

    //initialize players
    int numPlayers = choosePlayers();

    //fund players
    chooseMoney(numPlayers, playerMoney);

    //bets
    //vector<int> bets = {0};

    //play game
    bool playing = true;
    while(playing) {
        make_bets(playerMoney, bets, numPlayers);

        vector<vector<vector<Card>>> hands = dealCards(deck, numPlayers);
    }







    return 0;
}