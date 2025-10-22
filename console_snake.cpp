#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;
int a;

class Snake {
public:
	pair<int, int> body;
	char direction;

	Snake(int x, int y) {
		direction = 'R';
	}

	void move() {
		switch (direction)
		{
		case R:

		default:
			break;
		}
	}
};

void ViewGame(vector<vector<int>> ground) {
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 45; x++) {
			switch (ground.at(y).at(x)) {
			case 0:
				cout << " ";
				break;
			case 1:
				cout << "*";
				break;
			case 2:
				cout << "O";
				break;
			case 3:
				cout << "+";
				break;
			}
		}
		cout << endl;
	}
}

int main() {
	vector<vector<int>> ground(15, vector<int>(45, 0));
	for (int i = 1; i < 14; i++) {
		ground[i][0] = 1;
		ground[i][44] = 1;
	}
	ground[0] = vector<int>(45, 1);
	ground[14] = vector<int>(45, 1);

	while (true) {
		system("cls");
		ViewGame(ground);



		cout << a << endl;
		a++;
		Sleep(1000);
	}
	return 0;
}