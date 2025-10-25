#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;
int a;

class Body {
public:
	pair<int, int> pos;
	//char direction--;

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

		switch (direction) {
		case 'W': pos.second -= 1; break;
		case 'S': pos.second += 1; break;
		case 'A': pos.first -= 1; break;
		case 'D': pos.first += 1; break;
		}
		ground[pos.second][pos.first] = 2;

		for (auto ptr : bodyptr) {
			temp = ptr->pos;
			ptr->pos = prev;
			prev = temp;
		}
		ground[prev.second][prev.first] = 0;
		a++;
		grow(prev);
	}

	void grow(pair<int, int> prev) {
		bodyptr.push_back(new Body(prev));
	}

	void printSnakePos() {
		cout << "Head: " 
			 << pos.first << " , " 
			 << pos.second << endl;
		int index = 0;
		for (auto ptr : bodyptr) {
			index++;
			cout << "body[" << index << "]: " 
				 << ptr->pos.first << " , " 
				 << ptr->pos.second << endl;
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
	pair<int, int> pos;
	pos.first = 22, pos.second = 7;
	Snake snake(pos);
	for (int i = 1; i < 14; i++) {
		ground[i][0] = 1;
		ground[i][44] = 1;
	}
	ground[0] = vector<int>(45, 1);
	ground[14] = vector<int>(45, 1);

	while (true) {
		system("cls");
		ViewGame(ground);

		snake.move(ground,' ');

		cout << a << endl;
		a++;
		Sleep(1000);
	}
	return 0;
}