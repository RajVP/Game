#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;
const int width = 20, height = 20;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail; 
enum eDirection { STOP = 0, LEFT, RIGHT, DOWN, UP };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	//Randomly places the food for the snake
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
}
void Draw()
{
	//Clear the console window
	system("cls");
	//Prints the top wall
	for (int i = 0; i < width + 2; i++)
	{
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < height; j++)
		{
			//Prints the left wall
			if (j == 0)
				cout << "|";
			if (i == y && j == x)
				cout << "O";
			//Prints the food tile
			else if (i == foodY && j == foodX)
				cout << "F";
			else
			{
				//Prints the tail
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{					
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				//Prints the spaces in between the walls
				if (!print)
					cout << " ";
			}
			//Print out the sides
			if (j == width - 1)
				cout << "|";
			
		}
		cout << endl;
	}
	//Print bottom row
	for (int i = 0; i < width + 2; i++)
	{
		cout << "-";
	}
	cout << endl;
	//Print score
	cout << "Score: " << score;
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
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	//Tail is put in the position of the head
	tailX[0] = x;
	tailY[0] = y;
	//Constantly update the tail and head position
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	//Switch cases for character input
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
	//If you want the walls to count as game over
	//if (x > width || x < 0 || y > height || y < 0)
		//gameOver = true;

	//Pass through walls
	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == foodX && y == foodY)
	{
		score += 1;
		foodX = rand() % width;
		foodY = rand() % height;
		nTail++;
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
		//Slows down the game
		Sleep(75);
	}

	return 0;
}