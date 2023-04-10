//Ken Page
//CIS115 - Fifer
//Fall 2022

#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

class Deck
{

public:
	char f, s;

  void filldeck(Deck x_deck[], char x_face[], char x_suit[])
  {
    for (int i = 0 ; i < 52 ; i++)
    {
      x_deck[i].f = x_face[i%13];
      x_deck[i].s = x_suit[i/13];
    }
  }

  void shuffle(Deck x_deck[])
  {
    cout << "Shuffling..." << endl;
    srand(time(0));
    for (int i = 0; i < 52; i++)
    {
      int j = rand() % 52;
      Deck temp = x_deck[ i ];
      x_deck[ i ] = x_deck[ j ];
      x_deck[ j ] = temp;
    }
    cout << "Deck shuffled." << endl;
  }

  void display(Deck x_deck[])
  {
    cout << "Displaying the deck..." << endl;
    for (int i = 0 ; i < 52 ; i++)
    {
      cout << setw(2) << x_deck[i].f << " of " << x_deck[i].s << " - " ;
      if( i==12 || i==25 || i==38 )
      {
        cout << endl;
      }
      cout << endl << "  - - - - -  " << endl;
      return;
    }
  }

  void deal(Deck x_deck[])
  {
    ofstream dataFile("stats.txt", ios::out);
    if(dataFile.fail())
    {
      cout << "Error opening file." << endl;
    }
    cout << "File opened successfully." << endl;
    cout << "This means war!" << endl << endl << endl;
    dataFile << "This means war!" << endl << endl << endl;

    int player_one_score = 0, player_two_score = 0, round = 1;

    for (int i = 0 ; i < 52 ; i+=2)
    {
      int player_one_card, player_two_card;
      cout << "Round # " << round << " beginning with card # " << i+1 << endl;
      round++;
      cout << "Player 1: " << setw(2) << x_deck[i].f << " of " << x_deck[i].s << " :: VS :: Player 2: " << x_deck[i+1].f << " of " << x_deck[i+1].s << endl;
      dataFile << "Player 1: " << setw(2) << x_deck[i].f << " of " << x_deck[i].s << " :: VS :: Player 2: " << x_deck[i+1].f << " of " << x_deck[i+1].s << endl;
      switch (x_deck[i].f)
      {
		case '2':
			player_one_card = 2;
			break;
		case '3':
			player_one_card = 3;
			break;
		case '4':
			player_one_card = 4;
			break;
		case '5':
			player_one_card = 5;
			break;
		case '6':
			player_one_card = 6;
			break;
		case '7':
			player_one_card = 7;
			break;
		case '8':
			player_one_card = 8;
			break;
		case '9':
			player_one_card = 9;
			break;
		case 'T':
			player_one_card = 10;
			break;
		case 'J':
			player_one_card = 11;
			break;
		case 'Q':
			player_one_card = 12;
			break;
		case 'K':
			player_one_card = 13;
			break;
		case 'A':
			player_one_card = 14;
			break;
		}
		switch (x_deck[i+1].f)
      	{
		case '2':
			player_two_card = 2;
			break;
		case '3':
			player_two_card = 3;
			break;
		case '4':
			player_two_card = 4;
			break;
		case '5':
			player_two_card = 5;
			break;
		case '6':
			player_two_card = 6;
			break;
		case '7':
			player_two_card = 7;
			break;
		case '8':
			player_two_card = 8;
			break;
		case '9':
			player_two_card = 9;
			break;
		case 'T':
			player_two_card = 10;
			break;
		case 'J':
			player_two_card = 11;
			break;
		case 'Q':
			player_two_card = 12;
			break;
		case 'K':
			player_two_card = 13;
			break;
		case 'A':
			player_two_card = 14;
			break;
		}

      player_two_card = x_deck[i+1].f - '0';
      if (player_one_card > player_two_card)
      {
        cout << "### Player 1 wins!" << endl;
        dataFile << "### Player 1 wins!" << endl;
        player_one_score++;
      }
      else if (player_two_card > player_one_card)
      {
        cout << "### Player 2 wins!" << endl;
        dataFile << "### Player 2 wins!" << endl;
        player_two_score++;
      }
      else
      {
        cout << "### Looks like a tie, on to the next!" << endl;
        dataFile << "### Looks like a tie, on to the next!" << endl;
      }
      cout << "Current scores --- Player1: " << player_one_score << " --- Player2: " << player_two_score << endl << endl << endl;
      dataFile << "Current scores --- Player1: " << player_one_score << " --- Player2: " << player_two_score << endl << endl << endl;
    }
    cout << "Final score, Player 1: " << player_one_score << " --- Player 2: " << player_two_score << endl;
    dataFile << "Final score, Player 1: " << player_one_score << " --- Player 2: " << player_two_score << endl;
  }
};

int main()
{
  char f, s;
  char suit[4] =	{'H', 'D', 'C', 'S'};
  char face[13] ={'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
  Deck myDeck[52];
  myDeck[52].filldeck(myDeck, face, suit);
  myDeck[52].shuffle(myDeck);
  myDeck[52].deal(myDeck);
}
