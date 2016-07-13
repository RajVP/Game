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
bool foodPlaceable;

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
		foodPlaceable = true;

		while (foodPlaceable) {
			randomPosition = Vector2f((rand() % int(width / food.getSize().x))*food.getSize().x, (rand() % int(height / food.getSize().y))*food.getSize().y);
			for (i = 0; i < tails.size(); i++)
				if (randomPosition == tails.at(i).getPosition()) {
					foodPlaceable = true;
					break;
				}
				else {
					foodPlaceable = false;
				}

		}		
		food.setPosition(randomPosition);
		tails.push_back(RectangleShape(rect));
		score += 1;
		if (speedInc >= 1)
			speedInc+=10;
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
		
		//move snake in pointing direction
		tails.at(0).move(x, y);
		for (i = tails.size() - 1; i >= 0; i--){
			if (i != 0) {
					tails.at(i).setPosition(tails.at(i - 1).getPosition());
			}
		}


		//draw stuff
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