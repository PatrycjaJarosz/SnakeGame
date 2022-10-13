// Project1.cpp : Ten plik zawiera funkcje Setup, Draw, Input, Logic i main. Służy do uruchomienia gry: Snake.
//

#include <iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool  Koniec;
const int szer = 16, wys = 16;//wymiary
int x, y; //pozycja głowy
int x_fruit, y_fruit; //pozycja owoców
int x_ogon[100], y_ogon[100]; //pozycja ogona
int nogon; //dlugosc ogona
int punkty;
enum eDirection {stop = 0, LEFT, RIGHT, up, down};
eDirection dir;

void Setup() {
	Koniec = false;
	dir = stop;
	x = szer / 2; 	y = wys / 2;
	x_fruit = rand() % szer; // random number from 0 to (szer-1)
	y_fruit = rand() % wys;
	punkty = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i < szer+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < wys; i++) {
		for (int j = 0; j < szer; j++) {
			if (j == 0)
				cout << "#";
			
			if (i == y && j == x)
				cout << "O";
			else if (i == y_fruit && j == x_fruit)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nogon; k++) {
					if (x_ogon[k] == j && y_ogon[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}	
			if (j == szer - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < szer+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << punkty << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) { // keyboard controls
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = up;
			break;
		case 's':
			dir = down;
			break;
		case 'x':
			Koniec = true;
			break;
		}
	}
}

void Logic() {
	int prev_x = x_ogon[0];
	int prev_y = y_ogon[0];
	int prev_2x, prev_2y;
	x_ogon[0] = x; y_ogon[0] = y;
	
	for (int i = 1; i < nogon; i++) {
		prev_2x = x_ogon[i];
		prev_2y = y_ogon[i];
		x_ogon[i] = prev_x;
		y_ogon[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case up:
		y--;
		break;
	case down:
		y++;
		break;
	default:
		break;
	}
	//if (x > szer || x < 0 || y > wys || y< 0) //warunek na wejscie w sciane
	//	Koniec = true;

	if (x >= szer)
		x = 0;
	else if (x < 0)
		x = szer - 1;
	if (y >= wys)
		y = 0;
	else if (y < 0)
		y = wys - 1;

	for (int i = 0; i < nogon; i++) // warunek na koniec gry jeśli zjemy ogon
		if (x_ogon[i] == x && y_ogon[i] == y)
			Koniec = true;

	if (x == x_fruit && y == y_fruit) { //if we eat the fruit
		nogon++;
		punkty += 10;
		x_fruit = rand() % szer;
		y_fruit = rand() % wys;
	}
}

int main() {
	Setup();
	while (!Koniec) {
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	return 0;
}