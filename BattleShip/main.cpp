/*
	Created by: Omar Pena,
	Year: 2023,
	Version: 1.0 ,
	Language: C++,

*/
#include <stdio.h>
#include <Windows.h>
#include <conio.h> 
#include <vector>


#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define SHOOT_KEY 'z'


void gotoxy(int x, int y) {
	HANDLE hCon; 
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwPos; 
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}

void HideCursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(hCon, &cci);
}

class SHIP {
private:
	int x, y;
	std::vector<std::pair<int, int>> bullets; //Bullets list

public:
	SHIP(int _x, int _y) : x(_x), y(_y) {} 
	void draw();
	void remove();
	void move();
	void shoot(); 
};

void SHIP::draw() {
	gotoxy(x, y);	  printf("  T  ");
	gotoxy(x, y + 1); printf("->*<-");
	gotoxy(x, y + 2); printf("******");
}

void SHIP::remove() {
	gotoxy(x, y);	  printf("     ");
	gotoxy(x, y + 1); printf("     ");
	gotoxy(x, y + 2); printf("     ");
}

void SHIP::move() {
	if (_kbhit()) {
		char key = _getch();
		remove();
		if (key == LEFT && x > 0) x--;
		if (key == RIGHT && x < 77) x++;
		if (key == UP && y > 0) y--;
		if (key == DOWN && y < 23) y++;
		if (key == SHOOT_KEY) {
			shoot();
		}
		draw();
 	}
	for (size_t i = 0; i < bullets.size(); ++i) {
		gotoxy(bullets[i].first, bullets[i].second);
		printf(" ");
		bullets[i].second--;

		if (bullets[i].second <= 0) {
			bullets.erase(bullets.begin() + i);
			i--;
		}
		else {
			gotoxy(bullets[i].first, bullets[i].second);
			printf("^");
		}
		
	}
}

void SHIP::shoot() {
	bullets.push_back(std::make_pair(x + 2, y - 1));
}

int main() {
	HideCursor();
	SHIP n(40, 12);
	bool game_over = false;
	n.draw();
	while (!game_over) {
		n.move();
		Sleep(30);
	}
	return 0;
}
