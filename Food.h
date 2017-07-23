#pragma once
#include "Const and libs.h"



class Food
{	
public:
	sf::RectangleShape food;
	bool isEat;
	Food()
	{
		food.setSize(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE,SNAKE_PIXEL_SEGMENT_SIZE));
		food.setFillColor(Color::Red);
	}
	void fSetTexture(Texture &tex)
	{
		food.setTexture(&tex);
	}
	void spawnFood()
	{
		bool noIntersect;
		do
		{
			noIntersect = true;
			food.setPosition(rand() % 80 * 10, rand() % 60 * 10);
			for (int i = 0; i != game.sVec.size(); i++)
				for (std::list<RectangleShape*>::iterator iter = game.sVec.at(i)->snakeSegList.begin(); iter != game.sVec.at(i)->snakeSegList.end(); iter++)
				{
					if (food.getPosition() == (**iter).getPosition())
					{
						noIntersect = false;
						break;
					}
				}
		} while (!noIntersect);
	}
}food;
