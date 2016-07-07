#include <iostream>
#include <conio.h>
using namespace std;
bool gameOver;
const int width = 20, height = 20;
int x, y, foodX, foodY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, DOWN, UP };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
}
void Draw()
{
	//Clear the console window
	system("cls");
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == foodY && j == foodX)
				cout << "F";
			else
				cout << " ";
				
			if (j == width - 1)
				cout << "#";
			
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
}

void Input()
{
	//If keyboard key is pressed
	if (_kbhit())
	{
		//Get character
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}

	return 0;
}