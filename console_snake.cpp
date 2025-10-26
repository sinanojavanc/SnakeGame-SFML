#include <iostream>
#include <Windows.h>
#include <vector>
#include <random>
#include <atomic>
#include <thread>
using namespace std;

bool is_loose = false;
//--------------------------------------
// Global random generator
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distY(1, 18);
uniform_int_distribution<> distX(1, 28);
//--------------------------------------

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

		if (ground[pos.second][pos.first] == 3)
		{
			is_growing = true;
			pair<int, int> newapple = randomAppleMaker(ground);
			ground[newapple.second][newapple.first] = 3;
		}
		else if (ground[pos.second][pos.first] == 1
					|| ground[pos.second][pos.first] == 2)
			is_loose = true;

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

void inputHandler(atomic<bool>& running,
				  vector<vector<int>>& ground,
				  Snake& snake,
				  atomic<char>& dir)
{
	while (running) {
		if		(isKeyPressed('W') && dir != 'S') { dir = 'W'; Sleep(300); }
		else if (isKeyPressed('A') && dir != 'D') { dir = 'A'; Sleep(300); }
		else if (isKeyPressed('S') && dir != 'W') { dir = 'S'; Sleep(300); }
		else if (isKeyPressed('D') && dir != 'A') { dir = 'D'; Sleep(300); }
		Sleep(10);
	}
}

int main() {
	vector<vector<int>> ground(20, vector<int>(30, 0));
	atomic<bool> running(true);
	atomic<char> dir = 'A';

	pair<int, int> pos = { 22 , 10 };
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

	thread inputThread(inputHandler, ref(running), ref(ground), ref(snake), ref(dir));

	while (true) {
		system("cls");
		snake.move(ground, dir);
		ViewGame(ground);
		Sleep(300);
		if (is_loose)
			break;
	}
	cout << "* * * * * * * * *      YOU ARE DEAD     * * * * * * * * * *";
	inputThread.join();
	return 0;
}



//bool W = isKeyPressed('W');
//bool A = isKeyPressed('A');
//bool S = isKeyPressed('S');
//bool D = isKeyPressed('D');
//if (halfer) {
//	if (W && !prevW) snake.move(ground, 'W');
//	else if (A && !prevA) snake.move(ground, 'A');
//	else if (S && !prevS) snake.move(ground, 'S');
//	else if (D && !prevD) snake.move(ground, 'D');
//	else snake.move(ground, ' ');
//}