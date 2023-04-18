//new deal func

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
    for (int i = 0; i < (numPlayers+1); i++) {
        for (int j = 0; j < 2; j++) {
            players[i].push_back(deck.back());
            deck.pop_back();
        }
        hands[i] = players[i];
    }

    switch (numPlayers) {
        case 1:
            vector<vector<Card>> players;
            players.reserve(2);
            players[0].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            players[0].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            hands[0] = players[0];
            hands.back() = players.back();
            break;
        case 2:
            vector<vector<Card>> players;
            players.reserve(2);
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            hands[0] = players[0];
            hands[1] = players[1];
            hands.back() = players.back();
            break;
        case 3:
            vector<vector<Card>> players;
            players.reserve(2);
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            hands[0] = players[0];
            hands[1] = players[1];
            hands[2] = players[2];
            hands.back() = players.back();
            break;
        case 4:
            vector<vector<Card>> players;
            players.reserve(2);
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players[3].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players[3].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            hands[0] = players[0];
            hands[1] = players[1];
            hands[2] = players[2];
            hands[3] = players[3];
            hands.back() = players.back();
            break;
        case 5:
            vector<vector<Card>> players;
            players.reserve(2);
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players[3].push_back(deck.back());
            deck.pop_back();
            players[4].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players[3].push_back(deck.back());
            deck.pop_back();
            players[4].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            hands[0] = players[0];
            hands[1] = players[1];
            hands[2] = players[2];
            hands[3] = players[3];
            hands[4] = players[4];
            hands.back() = players.back();
            break;
        case 6:
            vector<vector<Card>> players;
            players.reserve(2);
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players[3].push_back(deck.back());
            deck.pop_back();
            players[4].push_back(deck.back());
            deck.pop_back();
            players[5].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players[3].push_back(deck.back());
            deck.pop_back();
            players[4].push_back(deck.back());
            deck.pop_back();
            players[5].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            hands[0] = players[0];
            hands[1] = players[1];
            hands[2] = players[2];
            hands[3] = players[3];
            hands[4] = players[4];
            hands[5] = players[5];
            hands.back() = players.back();
            break;
        case 7:
            vector<vector<Card>> players;
            players.reserve(2);
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players[3].push_back(deck.back());
            deck.pop_back();
            players[4].push_back(deck.back());
            deck.pop_back();
            players[5].push_back(deck.back());
            deck.pop_back();
            players[6].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            players[0].push_back(deck.back());
            deck.pop_back();
            players[1].push_back(deck.back());
            deck.pop_back();
            players[2].push_back(deck.back());
            deck.pop_back();
            players[3].push_back(deck.back());
            deck.pop_back();
            players[4].push_back(deck.back());
            deck.pop_back();
            players[5].push_back(deck.back());
            deck.pop_back();
            players[6].push_back(deck.back());
            deck.pop_back();
            players.back().push_back(deck.back());
            deck.pop_back();
            hands[0] = players[0];
            hands[1] = players[1];
            hands[2] = players[2];
            hands[3] = players[3];
            hands[4] = players[4];
            hands[5] = players[5];
            hands[6] = players[6];
            hands.back() = players.back();
            break;
    }