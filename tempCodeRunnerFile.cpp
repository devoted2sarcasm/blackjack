if (isPair(hands[i])) {
            cout << "Player " << i+1 << " has a pair of " << hands[i][0].rank << "s." << endl;
            cout << "Would you like to split? (y/n): ";
            char split;
            cin >> split;
            //if yes, all remaining players hands, including dealer, should be pushed back one spot, so that the current player plays 2 hands before progressing to the next
            //i may not have this implemented in time, but i need to get the rest working properly before polishing. as long as i can get an additional hand to be dealt, we're good to start.

            if (split == 'y') {
                if (playerMoney[i] < bets[i]) {
                    cout << "You do not have enough money to split." << endl;
                    continue;
                }
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
            cout << "Player " << i+1 << "'s hand (value: " << handValue(hands[i]) << "):" << endl;
            printHand(hands[i]);
            if (j == 0) {
                cout << "Would you like to double down? (y/n): ";
                char doubleDown;
                cin >> doubleDown;
                if (doubleDown == 'y') {
                    if (playerMoney[i] < bets[i]) {
                        cout << "You do not have enough money to double down." << endl;
                    }
                    else {
                        playerMoney[i] -= bets[i];
                        bets[i] *= 2;
                        hands[i].push_back(deck.back());
                        deck.pop_back();
                        cout << "Player " << i+1 << "'s hand (value: " << handValue(hands[i]) << "):" << endl;
                        printHand(hands[i]);
                        if (isBust(hands[i])) {
                            cout << "Player " << i+1 << " has busted!" << endl;
                            playerMoney[i] -= bets[i];
                        }
                        break;
                    }
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
            cout << "Player " << i+1 << "'s hand (value: " << handValue(hands[i]) << "):" << endl;
            printHand(hands[i]);
            j++;
        }

        if (isBust(hands[i])) {
            cout << "Player " << i+1 << " has busted!" << endl;
            //this is handled when bets are made, this will subtract the bet from the player AGAIN
            //playerMoney[i] -= bets[i];
        }