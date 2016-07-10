//#include <iostream>
//#include <conio.h>
//#include <Windows.h>
//using namespace std;
//bool gameOver;
//const int width = 20, height = 20;
//int x, y, foodX, foodY, score;
//int tailX[100], tailY[100];
//int nTail; 
//enum eDirection { STOP = 0, LEFT, RIGHT, DOWN, UP };
//eDirection dir;
//
//void Setup()
//{
//	gameOver = false;
//	dir = STOP;
//	x = width / 2;
//	y = height / 2;
//	//Randomly places the food for the snake
//	foodX = rand() % width;
//	foodY = rand() % height;
//	score = 0;
//}
//void Draw()
//{
//	//Clear the console window
//	system("cls");
//	//Prints the top wall
//	for (int i = 0; i < width + 2; i++)
//	{
//		cout << "-";
//	}
//	cout << endl;
//	for (int i = 0; i < height; i++)
//	{
//		for (int j = 0; j < height; j++)
//		{
//			//Prints the left wall
//			if (j == 0)
//				cout << "|";
//			if (i == y && j == x)
//				cout << "O";
//			//Prints the food tile
//			else if (i == foodY && j == foodX)
//				cout << "F";
//			else
//			{
//				//Prints the tail
//				bool print = false;
//				for (int k = 0; k < nTail; k++)
//				{					
//					if (tailX[k] == j && tailY[k] == i)
//					{
//						cout << "o";
//						print = true;
//					}
//				}
//				//Prints the spaces in between the walls
//				if (!print)
//					cout << " ";
//			}
//			//Print out the sides
//			if (j == width - 1)
//				cout << "|";
//			
//		}
//		cout << endl;
//	}
//	//Print bottom row
//	for (int i = 0; i < width + 2; i++)
//	{
//		cout << "-";
//	}
//	cout << endl;
//	//Print score
//	cout << "Score: " << score;
//}
//
//void Input()
//{
//	//If keyboard key is pressed
//	if (_kbhit())
//	{
//		//Get character
//		switch (_getch())
//		{
//		case 'a':
//			dir = LEFT;
//			break;
//		case 'd':
//			dir = RIGHT;
//			break;
//		case 'w':
//			dir = UP;
//			break;
//		case 's':
//			dir = DOWN;
//			break;
//		case 'x':
//			gameOver = true;
//			break;
//		}
//	}
//}
//void Logic()
//{
//	int prevX = tailX[0];
//	int prevY = tailY[0];
//	int prev2X, prev2Y;
//	//Tail is put in the position of the head
//	tailX[0] = x;
//	tailY[0] = y;
//	//Constantly update the tail and head position
//	for (int i = 1; i < nTail; i++)
//	{
//		prev2X = tailX[i];
//		prev2Y = tailY[i];
//		tailX[i] = prevX;
//		tailY[i] = prevY;
//		prevX = prev2X;
//		prevY = prev2Y;
//	}
//	//Switch cases for character input
//	switch (dir)
//	{
//	case LEFT:
//		x--;
//		break;
//	case RIGHT:
//		x++;
//		break;
//	case UP:
//		y--;
//		break;
//	case DOWN:
//		y++;
//		break;
//	default:
//		break;
//	}
//	//If you want the walls to count as game over
//	//if (x > width || x < 0 || y > height || y < 0)
//		//gameOver = true;
//
//	//Pass through walls
//	if (x >= width)
//		x = 0;
//	else if (x < 0)
//		x = width - 1;
//	if (y >= height)
//		y = 0;
//	else if (y < 0)
//		y = height - 1;
//	for (int i = 0; i < nTail; i++)
//		if (tailX[i] == x && tailY[i] == y)
//			gameOver = true;
//	if (x == foodX && y == foodY)
//	{
//		score += 1;
//		foodX = rand() % width;
//		foodY = rand() % height;
//		nTail++;
//	}
//}
//
//int main()
//{
//	Setup();
//	while (!gameOver)
//	{
//		Draw();
//		Input();
//		Logic();
//		//Slows down the game
//		Sleep(75);
//	}
//
//	return 0;
//}
//====================================================

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <string>
#include <SFML/System.hpp>

bool gameOver = false;
const int width = 500, height = 500;
double x = 0.0, y = 0.0;
int foodX, foodY, score = 0, i, j, k;
int nTail;
int latch = 0;
sf::Vector2f tails[100];
sf::RectangleShape head(sf::Vector2f(10, 10));
sf::RectangleShape tail(sf::Vector2f(10, 10));
sf::CircleShape food(10);
sf::Font font;
sf::Text text;

void Setup()
{
	//Randomly places the food for the snake
	foodX = rand() % width;
	foodY = rand() % height;
}

void Update()
{
	//collision between head and food: increment score and randomise food position
	if (head.getGlobalBounds().intersects(food.getGlobalBounds()))
	{
		foodX = rand() % width;
		foodY = rand() % height;
		//tail ++
		score += 1;
	}

	//Print score
	text.setString("Score: 000" + std::to_string(score));
}

void Logic()
{
//	int prevX = tailX[0];
//	int prevY = tailY[0];
	int prev2X, prev2Y;
	//Tail is put in the position of the head
//	tailX[0] = x;
//	tailY[0] = y;
	//Constantly update the tail and head position
	for (int i = 1; i < nTail; i++)
	{
//		prev2X = tailX[i];
//		prev2Y = tailY[i];
//		tailX[i] = prevX;
//		tailY[i] = prevY;
//		prevX = prev2X;
//		prevY = prev2Y;
	}
	
	//If you want the walls to count as game over
	//if (x > width || x < 0 || y > height || y < 0)
	//gameOver = true;

	//Pass through walls
	if (head.getPosition().x >= width)
		head.setPosition(sf::Vector2f(0, head.getPosition().y));
	else if (head.getPosition().x < 0)
		head.setPosition(sf::Vector2f(width - 10, head.getPosition().y));
	if (head.getPosition().y >= height)
		head.setPosition(sf::Vector2f(head.getPosition().x, 0));
	else if (head.getPosition().y < 0)
		head.setPosition(sf::Vector2f(head.getPosition().x, height - 10));
	/*for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;*/

}

void Input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		x = -0.1;
		y = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		x = 0.1;
		y = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		y = -0.1;
		x = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		y = 0.1;
		x = 0;
	}
}

int main()
{
	//////////init
	Setup();

	sf::RenderWindow window(sf::VideoMode(500, 500), "Snake!");

	head.setPosition(sf::Vector2f(250, 250));

	food.setFillColor(sf::Color::Red);
	
	if (!font.loadFromFile("brickled.ttf"))
	{
		// error...
	}
	text.setFont(font);
	text.setCharacterSize(10); // in pixels, not points!
	text.setPosition(sf::Vector2f(0, 490));
	text.setColor(sf::Color::White);
	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

	//////////update
		Input();
		Logic();
		Update();

		food.setPosition(sf::Vector2f(foodX, foodY));
		head.move(sf::Vector2f(x, y));

		/*for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				bool tailTest = false;
				for (k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						tail.setPosition(sf::Vector2f(i, j));
						tailTest = true;
					}
				}
			}
		}*/

	//////////draw
		window.clear();
		window.draw(food);
		window.draw(tail);
		window.draw(head);
		window.draw(text);
		window.display();
	}

	return 0;
}