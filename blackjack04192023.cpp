//Ken Page
//CIS205 - Fifer - Winter 2023
//Blackjack semester project

/*
goal is to make a blackjack game to as closely as possible play like a real casino game, with a maximum number of players, chosen number of decks, offering player a split if they have a pair, doubling down, normal hit or stand function, and the option at insurance if the dealer shows an ace

as of 04-19-2023, the game is functional, with a few bugs
- i need to sanitize some input to account for extraneous responses from user
- i need to add the offer for insurance, and handle the playerMoney vector accordingly - probably create an insurance vector
- generally speaking it runs as planned, i got in way over my head by turning the players' hands into a 3-dimensional vector, but after many many hours of reading and debugging, i believe i fixed any memory errors that were preventing the full game from being played
*/

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

//custom struct, built-in value to be accounted for in functions
//hidden attribute allows for a dealer's card to remain unknown until players have taken their turns

struct Card {
    string rank;
    string suit;
    int value;
    bool hidden; 

    Card(string r, string s) {
        rank = r;
        suit = s;
        if (r == "Ace") {
            value = 11;
        }
        else if (r == "King" || r == "Queen" || r == "Jack" || r == "10") {
            value = 10;
        }
        else if (r == "9") {
            value = 9;
        }
        else if (r == "8") {
            value = 8;
        }
        else if (r == "7") {
            value = 7;
        }
        else if (r == "6") {
            value = 6;
        }
        else if (r == "5") {
            value = 5;
        }
        else if (r == "4") {
            value = 4;
        }
        else if (r == "3") {
            value = 3;
        }
        else if (r == "2") {
            value = 2;
        }
        else {
            value = 21;
            cout << "Bad deck build" << endl << endl;
        }
    }
};


//this section is messy, but i changed and added functions so many different times, they ended up being fairly out of logical order, so i put them all up here at the top as prototypes so as to avoid calling a function before it was defined

void buildDeck(int numDecks);
void shuffleDeck(vector<Card>& deck);
int choosePlayers();
int chooseDecks();
void chooseMoney(int numPlayers, vector<int>& playerMoney);
void dealCards();
void printHand(vector<Card> hand);
void printDealerHand(vector<Card> hand);
int handValue(vector<Card> hand);
bool isBlackjack(vector<Card> hand);
bool isPair(vector<Card> hand);
bool isBust(vector<Card> hand);
void playerTurns(vector<vector<vector<Card>>>& hands, vector<Card>& deck, vector<int>& playerMoney, vector<int> bets, int numPlayers);
void dealerTurn(vector<Card>& deck, vector<vector<vector<Card>>>& hands);
void make_bets(vector<int>& playerMoney, vector<int>& bets, int numPlayers);
void checkWinner(vector<vector<vector<Card>>> hands, vector<int>& playerMoney, vector<int>& bets);
void singleTurn(vector<vector<Card>>& playerHands, int& playerMoney, int bet, vector<Card>& deck);
void hitStand(vector<Card>& hand, vector<Card>& deck, int& playerMoney, int bet);
bool playAgain();
//end of the mess


//build deck of cards with user unput, up to 8 decks
void buildDeck(int numDecks, vector<Card>& deck) {

    vector<string> ranks = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

    vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" };

    //steps through each possible card based on these nested loops, and creates that card, adding it to the master deck.
    //outside loop from creating each deck is doing that the number of times specified by user

    for (int i = 0; i < numDecks; i++) {
        for (string s : suits) {
            for (string r : ranks) {
                Card c(r, s);
                deck.push_back(c);
            }
        }
    }
}

//shuffle deck
//originally used random_device, but the deck was shuffling in the same order every time, so i switched to epoch time
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
    cin >> numPlayers;

    //sanitizing input
    while (numPlayers < 1 || numPlayers > 7) {
        cin.clear();
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
    cin >> numDecks;

    //just sanitizing input
    while (numDecks < 1 || numDecks > 8) {
        cin.clear();
        cout << "Invalid number of decks. Please enter a number between 1 and 8: ";
        cin >> numDecks;
    }

    cout << numDecks << " decks chosen." << endl;
    return numDecks;
}

//choose starting money, funds each player with that amount
void chooseMoney(int numPlayers, vector<int>& playerMoney) {
    int startingMoney;
    cout << "How much money does each player start with? ($1-$10,000)";
    cin >> startingMoney;

    //sanitizing input
    while (startingMoney < 1 || startingMoney > 10000) {
        cin.clear();
        cout << "Invalid amount of money. Please enter a valid number: ";
        cin >> startingMoney;
    }

    for (int i = 0; i < numPlayers; i++) {
        playerMoney[i] = startingMoney;
        cout << "Player " << i + 1 << " has been funded with $" << playerMoney[i] << endl;
    }
}

//
void dealCards(vector<Card>& deck, int numPlayers, vector<vector<vector<Card>>>& hands) {

    //instantiate temporary vector to hold card for dealing, later to be passed to the master 3d vector of hands
    //is this ideal? i have no idea, but it works
    vector<vector<Card>> players;

    //resizes the vector for number of players, plus one for the dealer
    //dealer hand will always be referenced as hands.back()[0]
    players.resize(numPlayers + 1);


    //for two loops - two cards per index which includes the dealer - will deal a card, one at a time, to each index
    //so player 1 dealt first, etc. etc., dealer last, then the same, everyone gets a second card, in order again
    //this should exactly mimic casino dealing
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < (numPlayers + 1); j++) {
            players[j].push_back(deck.back());
            deck.pop_back();
        }
    }

    //this pushes each hand from the temporary vector to the master 3d vector, including dealer
    for (int i = 0; i < (numPlayers + 1); i++) {
        hands[i].push_back(players[i]);
    }

    //hides dealer's first card
    hands.back()[0][0].hidden = true;

    //prints each player's initial hand for the whole table to see before moving on to players' turns
    for (int i = 0; i < numPlayers; i++) {
        cout << "########## Player " << i + 1 << " has: " << endl;
        cout << hands[i][0][0].rank << " of " << hands[i][0][0].suit << endl;
        cout << hands[i][0][1].rank << " of " << hands[i][0][1].suit << endl;
    }

    //dealer's hand handled separately so as to be identified as the dealer's hand
    printDealerHand(hands.back()[0]);

}



//print cards in given hand, adaptable for hands of any size, i.e. after they've already hit
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

//calculate hand value, accounting for aces preventing a player from busting
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
//hand must be only 2 cards, and value must be 21
bool isBlackjack(vector<Card> hand) {
    return hand.size() == 2 && handValue(hand) == 21;
}

//check if hand is a pair, for splitting
bool isPair(vector<Card> hand) {
    return hand.size() == 2 && hand[0].rank == hand[1].rank;
}

//check for bust, aces handled by value function
bool isBust(vector<Card> hand) {
    int value = handValue(hand);
    if (value > 21) {
        return true;
    }
    return false;
}

//players turns, starting with checking if dealer has blackjack, ending the round if so
//insurance needs to be built in here, before checking for dealer blackjack and ending the round prematurely
void playerTurns(vector<vector<vector<Card>>>& hands, vector<Card>& deck, vector<int>& playerMoney, vector<int> bets, int numPlayers) {
    if (isBlackjack(hands.back()[0])) {
        cout << "Dealer has blackjack!" << endl;
        return;
    }
    else {
        for (int i = 0; i < (hands.size() - 1); i++) {
            cout << "########## Player " << i+1 << "'s turn" << endl;
            singleTurn(hands[i], playerMoney[i], bets[i], deck);
            cout << endl;
        }
    }
    return;
}

//dealer's turn, showing both cards, then hitting until 17 or bust
//there is a bug that exists within this code, where a dealer could have 2 aces, leading to a hand value over 21, and would stay
void dealerTurn(vector<Card>& deck, vector<vector<vector<Card>>>& hands) {
    hands.back()[0][0].hidden = false;

    printDealerHand(hands.back()[0]);

    while (handValue(hands.back()[0]) < 17) {
        cout << "Dealer hits a " << deck.back().rank << " of " << deck.back().suit << "." << endl;
        hands.back()[0].push_back(deck.back());
        cout << "Dealer now has: " << handValue(hands.back()[0]) << endl;
        deck.pop_back();
    }

    if (handValue(hands.back()[0]) >= 17) {
        cout << "Dealer stays with " << handValue(hands.back()[0]) << endl;
    }

    if (isBust(hands.back()[0])) {
        cout << "Dealer has busted!" << endl;
    }
    cout << endl;
    return;
}

//bets are tracked as a vector, with each index corresponding to the same index in the hands 3d vector
void make_bets(vector<int>& playerMoney, vector<int>& bets, int numPlayers) {

    //reset bets to 0, mostly for new round play
    for (int i = 0; i < numPlayers; i++) {
        bets[i] = 0;
    }

    for (int i = 0; i < numPlayers; i++) {

        //allowing a player to reload their money if they run out
        if (playerMoney[i] == 0) {
            cout << "Player " << i + 1 << " has no money left, how much would you like to add?" << endl;
            int addMoney;
            cin >> addMoney;
            while (addMoney < 1) {
                cin.clear();
                cout << "Invalid amount. Please enter a number greater than 0: ";
                cin >> addMoney;
            }
            playerMoney[i] += addMoney;
        }

        //show player how much money they have, and take their bet
        cout << "Player " << i + 1 << ", you have $" << playerMoney[i] << "." << endl;
        cout << "How much would you like to bet? ";
        int bet;
        cin >> bet;

        //check for invalid bet
        while (bet < 1 || bet > playerMoney[i]) {
            cin.clear();
            cout << "Invalid bet. Please enter a number between 1 and $" << playerMoney[i] << ": ";
            cin >> bet;
        }

        bets[i] = bet;

        //subtract bet from player's money, to be paid back later via winners function
        playerMoney[i] -= bet;
    }

    //debug print all bets
    for (int i = 0; i < numPlayers; i++) {
        cout << "Player " << i + 1 << " bet $" << bets[i] << endl;
    }
}


//check for winner, paying out if player wins
//first makes a simple int from dealer's hand to check against
//then checks each player's index, hand by hand if there are multiple hands, and pays out accordingly per the hand value - blackjack, bust, beat dealer, etc.
void checkWinner(vector<vector<vector<Card>>> hands, vector<int>& playerMoney, vector<int>& bets) {

    int dealerValue = handValue(hands.back()[0]);

    //there was some odd functionality occasionally with a busted dealer's hand, so this makes sure that if the dealer busts, any player's hand value that doesn't also bust will win
    if (isBust(hands.back()[0])) {
        dealerValue = 1;
    }

    for (int i = 0; i < hands.size() - 1; i++) {
        for (int j = 0; j < hands[i].size(); j++) {

            if (isBlackjack(hands[i][j])) {
                cout << "Player " << i + 1 << ", hand " << j + 1 << " has blackjack!" << endl;
                cout << "Player " << i + 1 << " wins $" << (bets[i] * 1.5) << endl;
                playerMoney[i] += (bets[i] * 2.5);
            }

            else if (handValue(hands[i][j]) > dealerValue && !isBust(hands[i][j])) {
                cout << "Player " << i + 1 << ", hand " << j + 1 << " wins!" << endl;
                playerMoney[i] += bets[i] * 2;
            }

            else if (handValue(hands[i][j]) == dealerValue) {
                cout << "Player " << i + 1 << ", hand " << j + 1 << " pushes." << endl;
                playerMoney[i] += bets[i];
            }

            else {
                cout << "Player " << i + 1 << ", hand " << j + 1 << " loses." << endl;
            }
        }
    }

    //show each player's new total
    for (int i = 0; i < playerMoney.size(); i++) {
        cout << "Player " << i + 1 << " now has: $" << playerMoney[i] << endl;
    }

    //clears all bets, readying for next round
    for (int i = 0; i < bets.size(); i++) {
        bets[i] = 0;
    }

    //nice format spacing
    cout << endl;
    return;
}

//function for a single player taking a full turn
void singleTurn(vector<vector<Card>>& playerHands, int& playerMoney, int bet, vector<Card>& deck) {

    //check for blackjack, and no further action to take if yes
    for (int i = 0; i < playerHands.size(); i++) {
        if (isBlackjack(playerHands[i])) {
            cout << "Blackjack!" << endl;
            return;
        }

        //show hand again before player makes decision
        printHand(playerHands[i]);

        //check for pair, and ask if player wants to split
        while (isPair(playerHands[i])) {
            cout << "Hand " << i + 1 << " has a pair of " << playerHands[i][0].rank << "s." << endl;
            cout << "Would you like to split? (y/n): " << endl;
            char split;
            cin >> split;

            if (split == 'y') {

                //if player doesn't have enough money to cover a split, break from this and move on to hitStand
                if (playerMoney < bet) {
                    cout << "You don't have enough money to split" << endl;
                    break;
                }

                //split the cards into two hands, deal a new card to each, and go back to square one (check for split again)
                //also take additional money from the player for the split
                else {
                    playerMoney -= bet;
                    //temporarily store the first card in the hand
                    vector<Card> newHand;

                    newHand.push_back(playerHands[i][1]);
                    playerHands[i].pop_back();
                    playerHands.push_back(newHand);
                    playerHands[i].push_back(deck.back());
                    deck.pop_back();
                    playerHands[i + 1].push_back(deck.back());
                    deck.pop_back();
                    cout << "New hand after split: " << endl;
                    printHand(playerHands[i]);
                    continue;
                }
            }
            else {
                break;
            }
        }
        hitStand(playerHands[i], deck, playerMoney, bet);
    }
    return;
}

//function, can be recursive, for hitting or standing
//double down option is there and functional, will subtract money from player, but at the moment i don't know where to account for the extra part of the bet, as it's not a new hand, which i can already account for using the 3d vector
void hitStand(vector<Card>& hand, vector<Card>& deck, int& playerMoney, int bet) {
    cout << "Hand is: " << handValue(hand) << endl;
    cout << "Would you like to hit? (y for yes, d for double-down, anything else to stand): " << endl;
    char hit;
    cin >> hit;

    if (hit == 'd') {
        //if player doesn't have enough money, recursively call hitstand
        if (playerMoney < bet) {
            cout << "You don't have enough money to double down, please choose again." << endl;
            hitStand(hand, deck, playerMoney, bet);
        }

        //if player has already hit, double down not allowed, call htistand recursively
        else if (hand.size() > 2) {
            cout << "You have already hit and cannot double down now, please choose again." << endl;
            hitStand(hand, deck, playerMoney, bet);
        }

        //hits card, ends hitstand function, takes additional money from palyer
        else {
            cout << "Doubling down:" << endl;
            playerMoney -= bet;
            cout << "Hit: " << deck.back().rank << " of " << deck.back().suit << endl << endl;
            hand.push_back(deck.back());
            deck.pop_back();
            printHand(hand);
            return;
        }
    }

    //hits new card, recursively calls hitstand
    else if (hit == 'y') {

        //shows card hit, pops card from deck, shows new hand, checks for bust, calls hitstand recursively
        cout << "Hit: " << deck.back().rank << " of " << deck.back().suit << endl << endl;
        hand.push_back(deck.back());
        deck.pop_back();

        printHand(hand);

        if (isBust(hand)) {
            cout << "Hand has busted!" << endl << endl;
            return;
        }
        else {
            hitStand(hand, deck, playerMoney, bet);
        }
    }
    //anything other than 'd' for double or 'y' for hit will stand
    else {
        return;
    }
}


//check if player wants to play again
bool playAgain() {
    cout << "Would you like to play again? (y/n): ";
    char again;
    cin >> again;
    cout << endl << endl;
    return again == 'y';
}

//debug print deck
void showDeck(vector<Card> deck) {
    for (int i = 0; i < deck.size(); i++) {
        cout << deck[i].rank << " of " << deck[i].suit << ": worth " << deck[i].value << endl;
    }
    cout << "######################################" << endl << endl;
}

//WOOOO here we go
int main() {

    //start with how many decks to use and initialize deck vector
    int deckCount = chooseDecks();
    vector<Card> deck;

    //initialize deck using deckCount
    buildDeck(deckCount, deck);

    //debug print deck
    //showDeck(deck);

    //shuffle and print again for debug
    shuffleDeck(deck);
    //showDeck(deck);

    //initialize players
    int numPlayers = choosePlayers();

    //initialize player money
    vector<int> playerMoney;
    playerMoney.resize(numPlayers);
    chooseMoney(numPlayers, playerMoney);

    //initialize vector for tracking player bets
    vector<int> bets;
    bets.resize(numPlayers);

    //initialize vector for tracking player hands, plus one for dealer
    vector<vector<vector<Card>>> hands;
    hands.resize(numPlayers + 1);

    //play game
    bool playing = true;
    while (playing) {

        make_bets(playerMoney, bets, numPlayers);

        dealCards(deck, numPlayers, hands);

        playerTurns(hands, deck, playerMoney, bets, numPlayers);

        dealerTurn(deck, hands);

        checkWinner(hands, playerMoney, bets);

        //clear hands and ready for new round
        hands.clear();
        hands.resize(numPlayers + 1);

        playing = playAgain();
    }







    return 0;
}
