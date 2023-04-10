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
std::vector<std::vector<std::string>> deal_cards(int num_decks, int num_players) {
    std::vector<std::vector<std::string>> hands(num_players+1);
    std::vector<std::string> deck = create_deck(num_decks);
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < num_players+1; j++) {
            hands[j].push_back(deck.back());
            deck.pop_back();
        }
    }
    return hands;
}

int main() {
    // Deal cards to 1 dealer and 6 players using 6 decks
    std::vector<std::vector<std::string>> hands = deal_cards(6, 6);
    // Print the hands
    for (int i = 0; i < hands.size(); i++) {
        std::cout << "Player " << i << " hand: ";
        for (std::string card : hands[i]) {
            std::cout << card << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}


