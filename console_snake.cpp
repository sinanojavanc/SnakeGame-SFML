#include <iostream>
#include <Windows.h>
#include <vector>
#include <random>
using namespace std;

random_device rd; 
mt19937 gen(rd());
uniform_int_distribution<> distY(1, 19);
uniform_int_distribution<> distX(1, 29);
pair<int, int> randomAppleMaker(vector<vector<int>>& ground) {
	pair<int, int> apple;
	do
	{
		apple.first = distX(gen);
		apple.second = distY(gen);
	} while (ground[apple.second][apple.first] != 0);
	return apple;
}

class Body {
public:
	pair<int, int> pos;

	Body(pair<int, int> p) {
		pos = p;
	}
};

class Snake {
public:
	pair<int, int> pos;
	char direction;
	vector<Body*> bodyptr;

	Snake(pair<int, int> head) {
		direction = 'A';
		pos = head;
	}	
	~Snake() {
		for (auto ptr : bodyptr)
			delete ptr;
	}

	void move(vector<vector<int>>& ground, char dir) {
		if (dir != ' ')
			direction = dir;

		pair<int, int> prev = pos;
		pair<int, int> temp;
		bool is_growing = false;

		switch (direction) {
		case 'W': pos.second -= 1; break;
		case 'S': pos.second += 1; break;
		case 'A': pos.first -= 1; break;
		case 'D': pos.first += 1; break;
		}

		if (ground[pos.second][pos.first] == 3) {
			is_growing = true;
			pair<int, int> newapple = randomAppleMaker(ground);
			ground[newapple.second][newapple.first] = 3;
		}

		ground[pos.second][pos.first] = 2;
		for (auto ptr : bodyptr) {
			ground[ptr->pos.second][ptr->pos.first] = 2;
		}

		for (auto ptr : bodyptr) {
			temp = ptr->pos;
			ptr->pos = prev;
			prev = temp;
		}
		pair<int, int> tailPos = prev;
		if (!bodyptr.empty()) {
			tailPos = prev; 
		}
		ground[tailPos.second][tailPos.first] = 0;
		if (is_growing) grow(prev);
	}

	void grow(pair<int, int> prev) {
		bodyptr.push_back(new Body(prev));
	}

};


void ViewGame(const vector<vector<int>>& ground) {
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 30; x++) {
			switch (ground.at(y).at(x)) {
			case 0: { cout << "  "; break; }
			case 1: { cout << "* "; break; }
			case 2: { cout << "\033[32mo\033[0m "; break; }
			case 3: { cout << "\033[31mx\033[0m "; break; }
			}
		}
		cout << endl;
	}
}

bool isKeyPressed(int vKey) {
	return (GetAsyncKeyState(vKey) & 0x8000) != 0;
}

int main() {
	vector<vector<int>> ground(20, vector<int>(30, 0));
	pair<int, int> pos;
	bool prevW = false, prevA = false, prevS = false, prevD = false;
	char dir = 'D';

	pos.first = 20, pos.second = 7;
	Snake snake(pos);

	for (int i = 1; i < 19; i++)
	{
		ground[i][0] = 1;
		ground[i][29] = 1;
	}
	ground[0] = vector<int>(30, 1);
	ground[19] = vector<int>(30, 1);
	pos = randomAppleMaker(ground);
	ground[pos.second][pos.first] = 3;

	while (true) {
		system("cls");
		ViewGame(ground);
		bool W = isKeyPressed('W');
		bool A = isKeyPressed('A');
		bool S = isKeyPressed('S');
		bool D = isKeyPressed('D');

		if (W && !prevW) snake.move(ground, 'W');
		else if (A && !prevA) snake.move(ground, 'A');
		else if (S && !prevS) snake.move(ground, 'S');
		else if (D && !prevD) snake.move(ground, 'D');
		else snake.move(ground,' ');

		Sleep(100);
	}
	return 0;
}