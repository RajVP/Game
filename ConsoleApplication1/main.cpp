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
//	//Tail is put in the position of the rect
//	tailX[0] = x;
//	tailY[0] = y;
//	//Constantly update the tail and rect position
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
#include <string>
#include <vector>
#include <Windows.h>

using namespace sf;

bool gameOver = false;
const int width = 500, height = 500;
double x, y, speedInc;
int score, i;
int nTail;
int latch = 0;
std::vector<RectangleShape> tails;
Vector2f randomPosition;
RectangleShape rect(Vector2f(50, 50));
RectangleShape food(Vector2f(50, 50));
RectangleShape flash(Vector2f(width, height));
Font font;
Text text;

void Setup()
{
	score = 0;
	x = 0.0;
	speedInc = 0.0;
	tails.clear();
	y= -rect.getGlobalBounds().width; //go up

	//create first snake section and centre
	for (i = 0; i <= 1; i++) {
		tails.push_back(RectangleShape(rect));
		tails.at(i).setPosition(Vector2f(400, 300+i*rect.getGlobalBounds().height));
	}
}

void Update()
{
	//collision between rect and food: increment score and randomise food position and increase speed of snake
	if (tails.at(0).getGlobalBounds().intersects(food.getGlobalBounds()))
	{
		randomPosition = Vector2f((rand() % int(width / food.getSize().x))*food.getSize().x, (rand() % int(height / food.getSize().y))*food.getSize().y);
		tails.push_back(RectangleShape(rect));
		score += 1;
		if (speedInc >= 1)
			speedInc++;
		else
			speedInc = 1;
	}

	Vector2f headPosition = tails.at(0).getPosition();

	//collision with snake
	for (i = 0; i < tails.size(); i++)
		if (tails.at(0).getGlobalBounds().intersects(tails.at(i).getGlobalBounds()) && i >= 2)
			Setup();
		/*if (headPosition == tails.at(i).getPosition() && i >= 2) //another way of doing it
			Setup();*/

	//die on collision
	if (headPosition.x >= width || headPosition.x < 0 || headPosition.y >= height || headPosition.y < 0)
		Setup();

	//Pass through walls (kinda glitchy after the snake passes the wall?)
	/*for (i = 0; i < tails.size(); i++) {
		if (tails.at(i).getPosition().x >= width)
			tails.at(i).setPosition(Vector2f(0, tails.at(i).getPosition().y));
		if (tails.at(i).getPosition().x < 0)
			tails.at(i).setPosition(Vector2f(width - tails.at(i).getGlobalBounds().width, tails.at(i).getPosition().y));
		if (tails.at(i).getPosition().y >= height)
			tails.at(i).setPosition(Vector2f(tails.at(i).getPosition().x, 0));
		if (tails.at(i).getPosition().y < 0)
			tails.at(i).setPosition(Vector2f(tails.at(i).getPosition().x, height - tails.at(i).getGlobalBounds().height));
	}*/

	//Print score
	text.setString("Score: 000" + std::to_string(score));
}

void Input() {
	if (Keyboard::isKeyPressed(Keyboard::Left) && x<=0) {
		x = -rect.getGlobalBounds().width;
		y = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && x>=0) {
		x = rect.getGlobalBounds().width;
		y = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up) && y <= 0) {
		y = -rect.getGlobalBounds().height;
		x = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && y >= 0) {
		y = rect.getGlobalBounds().height;
		x = 0;
	}
}

int main()
{
	Setup();
	//Randomly places the food for the snake
	//randomPosition = Vector2f(rand() % width, rand() % height);
	randomPosition = Vector2f((rand() % int(width / food.getSize().x))*food.getSize().x, (rand() % int(height / food.getSize().y))*food.getSize().y);

	food.setFillColor(Color::Red);

	RenderWindow window(VideoMode(500, 500), "Snake!");
		
	if (!font.loadFromFile("brickled.ttf"))
	{
		// error...
	}
	text.setFont(font);
	text.setCharacterSize(10); // in pixels, not points!
	text.setPosition(Vector2f(0, 490));
	text.setColor(Color::White);
	
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		Input();
		Update();
		food.setPosition(randomPosition);

		tails.at(0).move(x, y);
		for (i = tails.size() - 1; i >= 0; i--){
			if (i != 0) {
					tails.at(i).setPosition(tails.at(i - 1).getPosition());
			}
		}

		window.clear();
		window.draw(food);
		window.draw(text);
		for (i = 0; i < tails.size(); i++)
			window.draw(tails.at(i));
		window.display();

		Sleep(500-speedInc);
	}

	return 0;
}