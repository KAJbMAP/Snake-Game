#pragma once
#include "Const and libs.h"


class Snake
{
protected:	
	int len;	
	sf::Color color;
	enum Direction
	{
		left, right, up, down
	};		
	struct keyboard
	{
		Keyboard::Key left, right, up, down;
	};
	

public:		
	std::string name;
	std::list<RectangleShape*> snakeSegList;
	keyboard keyCode;
	Direction dir;
	Snake()
	{		
		color = Color::White;
		RectangleShape* ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
		ptr->setPosition(rand() % 80 * 10, rand() % 60 * 10);
		ptr->setFillColor(color);
		snakeSegList.push_back(ptr);		
		for (int i = 0; i != 2; i++)
		{			
			ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));			
			ptr->setPosition(snakeSegList.back()->getPosition().x, snakeSegList.back()->getPosition().y + SNAKE_PIXEL_SEGMENT_SIZE);
			ptr->setFillColor(color);
			snakeSegList.push_back(ptr);
		}
		keyCode.left = sf::Keyboard::Left;
		keyCode.right = sf::Keyboard::Right;
		keyCode.up = sf::Keyboard::Up;
		keyCode.down = sf::Keyboard::Down;		
		len = 3;
		dir = Direction (rand()%4);
		name = "Player";
	}
	Snake(Keyboard::Key Left, Keyboard::Key Right, Keyboard::Key Up, Keyboard::Key Down, sf::Color col)
	{
		color = col;
		RectangleShape* ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
		ptr->setPosition(rand() % 80 * 10, rand() % 60 * 10);
		ptr->setFillColor(color);
		snakeSegList.push_back(ptr);
		for (int i = 0; i != 2; i++)
		{
			ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
			ptr->setPosition(snakeSegList.back()->getPosition().x, snakeSegList.back()->getPosition().y + SNAKE_PIXEL_SEGMENT_SIZE);
			ptr->setFillColor(color);
			snakeSegList.push_back(ptr);
		}
		{keyCode.left = Left;
		keyCode.right = Right;
		keyCode.up = Up;
		keyCode.down = Down;	}		
		len = 3;
		dir = Direction(rand() % 4);
	}
	Snake(Keyboard::Key Left, Keyboard::Key Right, Keyboard::Key Up, Keyboard::Key Down, sf::Color col, std::string n)
	{
		color = col;
		RectangleShape* ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
		ptr->setPosition(rand() % 80 * 10, rand() % 60 * 10);
		ptr->setFillColor(color);
		snakeSegList.push_back(ptr);
		for (int i = 0; i != 2; i++)
		{
			ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
			ptr->setPosition(snakeSegList.back()->getPosition().x, snakeSegList.back()->getPosition().y + SNAKE_PIXEL_SEGMENT_SIZE);
			ptr->setFillColor(color);
			snakeSegList.push_back(ptr);
		}
		{keyCode.left = Left;
		keyCode.right = Right;
		keyCode.up = Up;
		keyCode.down = Down;	}
		name = n;
		len = 3;
		dir = Direction(rand() % 4);
	}
	Snake(int x, int y, Direction d, int l, Keyboard::Key Left, Keyboard::Key Right, Keyboard::Key Up, Keyboard::Key Down, std::string n)
	{		
		color = Color::White;
		RectangleShape* ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
		ptr->setPosition(x, y);
		ptr->setFillColor(color);
		snakeSegList.push_back(ptr);
		for (int i = 1; i != len; i++)
		{
			ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
			ptr->setPosition(snakeSegList.back()->getPosition().x, snakeSegList.back()->getPosition().y + SNAKE_PIXEL_SEGMENT_SIZE);
			ptr->setFillColor(color);
			snakeSegList.push_back(ptr);
		}
		keyCode.left = Left;
		keyCode.right = Right;
		keyCode.up = Up;
		keyCode.down = Down;
		name = n;
		dir = d;
		
	}
	Snake(sf::Vector2f coord, Direction d, int l, Keyboard::Key Left, Keyboard::Key Right, Keyboard::Key Up, Keyboard::Key Down, std::string n)
	{
		color = Color::White;
		RectangleShape* ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
		ptr->setPosition(coord);
		ptr->setFillColor(color);
		snakeSegList.push_back(ptr);
		for (int i = 1; i != len; i++)
		{
			ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
			ptr->setPosition(snakeSegList.back()->getPosition().x, snakeSegList.back()->getPosition().y + SNAKE_PIXEL_SEGMENT_SIZE);
			ptr->setFillColor(color);
			snakeSegList.push_back(ptr);
		}
		keyCode.left = Left;
		keyCode.right = Right;
		keyCode.up = Up;
		keyCode.down = Down;	
		name = n;
		dir = d;		
	}

	void keyControl()
	{
		if (sf::Keyboard::isKeyPressed(keyCode.left) && dir != right) dir = left;
		else if (sf::Keyboard::isKeyPressed(keyCode.right) && dir != left) dir = right;
		else if (sf::Keyboard::isKeyPressed(keyCode.up) && dir != down) dir = up;
		else if (sf::Keyboard::isKeyPressed(keyCode.down) && dir != up) dir = down;
		
	}//Обработка управления

	void setControl(Keyboard::Key Left, Keyboard::Key Right, Keyboard::Key Up, Keyboard::Key Down)
	{
		keyCode.left = Left;
		keyCode.right = Right;
		keyCode.up = Up;
		keyCode.down = Down;
	}//установка клавиш управления

	void setColor(sf::Color col)
	{
		color = col;
		for (std::list<RectangleShape*>::iterator iter = snakeSegList.begin(); iter != snakeSegList.end(); iter++)
			(**iter).setFillColor(col);		
	}//Установка цвета

	sf::Color getColor()
	{
		return color;
	}//Получить цвет
};