int main() {
    // Get user input for number of players, number of decks, and starting money
    int num_players, num_decks, starting_money;
    std::cout << "Enter number of players (1-7): ";
    std::cin >> num_players;
    std::cout << "Enter number of decks (1-8): ";
    std::cin >> num_decks;
    std::cout << "Enter starting money: ";
    std::cin >> starting_money;

    // Create the deck
    std::vector<std::string> deck = create_deck(num_decks);

    // Shuffle the deck
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

    // Initialize player pools
    std::vector<int> pools(num_players+1, starting_money);

    // Game loop
    while (true) {
        // Check if there are enough cards remaining
        if (deck.size() < 4*(num_players+1)) {
            std::cout << "Not enough cards remaining to continue playing." << std::endl;
            std::string choice;
            std::cout << "Enter n to create a new deck, or q to quit: ";
            std::cin >> choice;
            if (choice == "n") {
                std::cout << "Enter number of decks (1-8): ";
                std::cin >> num_decks;
                deck = create_deck(num_decks);
                std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
                std::cout << "New deck created." << std::endl;
            } else {
                std::cout << "Thanks for playing!" << std::endl;
                break;
            }
        }

        // Deal cards to the players
        std::vector<std::vector<std::string>> hands = deal_cards(num_players, deck);
        std::vector<int> bets = betting(num_players, pools);

        // Play the game
        for (int i = 0; i < num_players+1; i++) {
            std::cout << "Player " << i << " hand: ";
            for (std::string card : hands[i]) {
                std::cout << card << " ";
            }
            std::cout << std::endl;

            // Offer the opportunity to double or split, if appropriate
            if (hands[i].size() == 2 && same_rank(hands[i][0], hands[i][1])) {
                // TODO: offer the opportunity to split
            }

            // Play the hand
            while (true) {
                std::string choice;
                std::cout << "Player " << i << " hand value: " << hand_value(hands[i]) << std::endl;
                std::cout << "Enter h to hit, s to stand: ";
                std::cin >> choice;
                if (choice == "h") {
                    hands[i].push_back(deck.back());
                    deck.pop_back();
                    std::cout << "Player " << i << " hand: ";
                    for (std::string card : hands[i]) {
                        std::cout << card << " ";
                    }
                    std::cout << std::endl;
                    if (hand_value(hands[i]) > 21) {
                        std::cout << "Player " << i << " busts!" << std::endl;
                        break;
                    }
                } else {
                    break;
               
