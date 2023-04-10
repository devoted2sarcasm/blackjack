#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Define the card values and suits
const std::vector<char> VALUES = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
const std::vector<char> SUITS = {'C', 'D', 'H', 'S'};

// Define the deck of cards
std::vector<std::string> create_deck(int num_decks) {
    std::vector<std::string> deck;
    for (int i = 0; i < num_decks; i++) {
        for (char value : VALUES) {
            for (char suit : SUITS) {
                std::string card = std::string(1, value) + suit;
                deck.push_back(card);
            }
        }
    }
    return deck;
}

// Deal the cards to the players
std::vector<std::vector<std::string>> deal_cards(int num_players, std::vector<std::string>& deck) {
    std::vector<std::vector<std::string>> hands(num_players+1);
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < num_players+1; j++) {
            hands[j].push_back(deck.back());
            deck.pop_back();
        }
    }
    return hands;
}

// Determine if two cards have the same rank
bool same_rank(std::string card1, std::string card2) {
    return (card1[0] == card2[0]);
}

int main() {
    // Get user input for number of players and number of decks
    int num_players, num_decks;
    std::cout << "Enter number of players (1-7): ";
    std::cin >> num_players;
    std::cout << "Enter number of decks (1-8): ";
    std::cin >> num_decks;
    // Create the deck
    std::vector<std::string> deck = create_deck(num_decks);
    // Deal cards to the players
    std::vector<std::vector<std::string>> hands = deal_cards(num_players, deck);
    // Print the hands
    for (int i = 0; i < hands.size(); i++) {
        std::cout << "Player " << i << " hand: ";
        for (std::string card : hands[i]) {
            std::cout << card << " ";
        }
        std::cout << std::endl;
    }
    // Player 1's turn
    std::cout << "Player 1's turn: ";
    int player1_score = 0;
    bool player1_blackjack = false;
    for (std::string card : hands[0]) {
        if (card[0] == 'A') {
            player1_score += 11;
        } else if (card[0] == 'T' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K') {
            player1_score += 10;
        } else {
            player1_score += card[0] - '0';
        }
    }
    if (hands[0][0][0] == hands[0][1][0]) {
        std::cout <<
