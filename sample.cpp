

#include <iostream>
#include <string>
using namespace std;





int main() {
	int numPlayers = 4;
	int max = 10;
	for (int i = 0; i < numPlayers; i++) {
			char a[max];
			string x = "playerTurn_";
			string name = x + itoa(i,a,i+1);
			cout << "vector " << name << " created." << endl;
	}
}