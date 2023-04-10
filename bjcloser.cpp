//Ken Page
//c++2 semester project
//Cis205 - Fifer - Winter 2023

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Define the card values and suits
const vector<char> VALUES = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
const vector<char> SUITS = {'C', 'D', 'H', 'S'};

// Define the deck of cards
vector<string> create_deck(int num_decks) {
    vector<string> deck;
    for (int i = 0; i < num_decks; i++) {
        for (char value : VALUES) {
            for (char suit : SUITS) {
                string card = string(1, value) + suit;
                deck.push_back(card);
            }
        }
    }
    return deck;
}

// Deal the cards to the players
vector<vector<string>> deal_cards(int num_players, vector<string>& deck) {
    vector<vector<string>> hands(num_players+1);
    shuffle(deck.begin(), deck.end(), default_random_engine(chrono::system_clock::now().time_since_epoch().count()));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < num_players+1; j++) {
            hands[j].push_back(deck.back());
            deck.pop_back();
        }
    }
    return hands;
}

// Determine if two cards have the same rank
bool same_rank(string card1, string card2) {
    return (card1[0] == card2[0]);
}

// Calculate the value of a hand
int hand_value(vector<string> hand) {
    int value = 0;
    int num_aces = 0;
    for (string card : hand) {
        if (card[0] == 'A') {
            num_aces++;
            value += 11;
        } else if (card[0] == 'T' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K') {
            value += 10;
        } else {
            value += card[0] - '0';
        }
    }
    while (value > 21 && num_aces > 0) {
        value -= 10;
        num_aces--;
    }
    return value;
}

int main() {
    // Get user input for number of players, number of decks, and starting money
    int num_players, num_decks, starting_money;
    cout << "Enter number of players (1-7): ";
    cin >> num_players;
    cout << "Enter number of decks (1-8): ";
    cin >> num_decks;
    cout << "Enter starting money: ";
    cin >> starting_money;
    // Create the deck
    vector<string> deck = create_deck(num_decks);
    // Shuffle the deck
    shuffle(deck.begin(), deck.end(), default_random_engine(chrono::system_clock::now().time_since_epoch().count()));
    // Initialize player pools
    vector<int> pools(num_players+1, starting_money);
    // Game loop
    while (true) {
    // Deal cards to the players
    vector<vector<string>> hands = deal_cards(num_players, deck);

    // Print the player hands
    cout << "Dealer: " << hands[num_players][0] << " X\n";
    for (int i = 0; i < num_players; i++) {
        cout << "Player " << i+1 << ": ";
        for (string card : hands[i]) {
            cout << card << " ";
        }
        cout << "\n";
    }

    // Player turns
    for (int i = 0; i < num_players; i++) {
        bool blackjack = false;
        bool bust = false;
        int hand_value = get_hand_value(hands[i], true);
        if (hand_value == 21) {
            blackjack = true;
            cout << "Player " << i+1 << " has blackjack!\n";
        }
        else {
            cout << "Player " << i+1 << ", what do you want to do? (h for hit, s for stand): ";
            string input;
            cin >> input;
            while (input != "h" && input != "s") {
                cout << "Invalid input. Please enter h for hit or s for stand: ";
                cin >> input;
            }
            while (input == "h") {
                hands[i].push_back(deck.back());
                deck.pop_back();
                hand_value = get_hand_value(hands[i], true);
                cout << "Player " << i+1 << "'s hand: ";
                for (string card : hands[i]) {
                    cout << card << " ";
                }
                cout << "\n";
                if (hand_value > 21) {
                    bust = true;
                    cout << "Player " << i+1 << " busts!\n";
                    break;
                }
                else if (hand_value == 21) {
                    blackjack = true;
                    cout << "Player " << i+1 << " has blackjack!\n";
                    break;
                }
                cout << "Player " << i+1 << ", what do you want to do? (h for hit, s for stand): ";
                cin >> input;
                while (input != "h" && input != "s") {
                    cout << "Invalid input. Please enter h for hit or s for stand: ";
                    cin >> input;
                }
            }
        }
        if (!blackjack && !bust) {
            cout << "Player " << i+1 << " stands with hand value of " << hand_value << "\n";
        }
    }

    // Dealer turn
    int dealer_hand_value = get_hand_value(hands[num_players], false);
    cout << "Dealer: ";
    for (string card : hands[num_players]) {
        cout << card << " ";
    }
    cout << "\n";
    while (dealer_hand_value < 17) {
        hands[num_players].push_back(deck.back());
        deck.pop_back();
        dealer_hand_value = get_hand_value(hands[num_players], false);
        cout << "Dealer hits and receives " << hands[num_players].back() << "\n";
    }
    if (dealer_hand_value > 21) {
        cout << "Dealer busts with a hand value of " << dealer_hand_value << "!\n";
    }
    else {
        cout << "Dealer stands with a hand value of " << dealer_hand_value << "\n";
    }

    // Determine the winners
    for (int i = 0; i < num_players; i++) 
        {
            int hand_value = get_hand_value(hands[i], true);
            if (hand_value > 21) 
                {
                    cout << "Player " << i + 1 << " busts with a hand value of " << hand_value << endl;
                } 
            else if (hand_value == 21 && hands[i].size() == 2) 
                {
                    cout << "Player " << i + 1 << " has blackjack!" << endl;
                } 
            else 
                {
                    int dealer_value = get_hand_value(hands[num_players], false);
                    if (dealer_value > 21 || hand_value > dealer_value) 
                        {
                            cout << "Player " << i + 1 << " wins with a hand value of " << hand_value << endl;
                            player_money[i] += player_bet[i] * 2;
                        } 
                    else if (hand_value == dealer_value) 
                        {
                            cout << "Player " << i + 1 << " pushes with a hand value of " << hand_value << endl;
                            player_money[i] += player_bet[i];
                        } 
                    else 
                        {
                            cout << "Player " << i + 1 << " loses with a hand value of " << hand_value << endl;
                        }
                }
            cout << "Player " << i + 1 << " now has " << player_money[i] << " dollars." << endl;
        }

// Check if there are fewer than 4 cards per player left
int remaining_cards = deck.size() - num_players * 2;
if (remaining_cards < num_players * 2) {
    cout << "There are fewer than 4 cards per player left in the deck." << endl;
    cout << "Do you want to continue playing with a new deck? (Y/N): ";
    string choice;
    cin >> choice;
    if (choice == "Y" || choice == "y") {
        deck = build_deck(num_decks);
        shuffle_deck(deck);
        continue;
    } else {
        break;
    }
}

// Ask if the players want to keep playing
cout << "Do you want to keep playing? (Y/N): ";
string choice;
cin >> choice;
if (choice == "N" || choice == "n") {
    break;
}

);
if (hand_value > 21) {
cout << "Player " << i + 1 << " busts with a hand value of " << hand_value << endl;
} else if (hand_value == 21 && hands[i].size() == 2) {
cout << "Player " << i + 1 << " has blackjack!" << endl;
} else {
int dealer_value = get_hand_value(hands[num_players], false);
if (dealer_value > 21 || hand_value > dealer_value) {
cout << "Player " << i + 1 << " wins with a hand value of " << hand_value << endl;
player_money[i] += player_bet[i] * 2;
} else if (hand_value == dealer_value) {
cout << "Player " << i + 1 << " pushes with a hand value of " << hand_value << endl;
player_money[i] += player_bet[i];
} else {
cout << "Player " << i + 1 << " loses with a hand value of " << hand_value << endl;
}
}
cout << "Player " << i + 1 << " now has " << player_money[i] << " dollars." << endl;
}

c
Copy code
// Check if there are fewer than 4 cards per player left
int remaining_cards = deck.size() - num_players * 2;
if (remaining_cards < num_players * 2) {
    cout << "There are fewer than 4 cards per player left in the deck." << endl;
    cout << "Do you want to continue playing with a new deck? (Y/N): ";
    string choice;
    cin >> choice;
    if (choice == "Y" || choice == "y") {
        deck = build_deck(num_decks);
        shuffle_deck(deck);
        continue;
    } else {
        break;
    }
}

// Ask if the players want to keep playing
cout << "Do you want to keep playing? (Y/N): ";
string choice;
cin >> choice;
if (choice == "N" || choice == "n") {
    break;
}
}

cout << "Thanks for playing!" << endl;

return 0;
}