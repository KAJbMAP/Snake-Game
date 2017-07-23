#pragma once
#include "Const and libs.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
class SnakeGame
{
private:
	SoundBuffer eatBuf;
	Sound eatSound;
	Font font;
	Text text;	
	VertexArray grid;	
	Texture backgroundTexture;
	RectangleShape background;
	Color gridColor = Color(50, 50, 50, 45);
public:	
	std::vector<Snake*> sVec;
	Texture segmentTexture;
	SnakeGame()
	{			
		//Инициализация сетки
		
		for (int x = 0; x != SCREEN_SIZE_X; x += 10)
		{
			grid.append(Vertex(Vector2f(x, 0), gridColor));
			grid.append(Vertex(Vector2f(x, SCREEN_SIZE_Y), gridColor));
		}
		for (int y = 0; y != SCREEN_SIZE_Y; y += 10)
		{
			grid.append(Vertex(Vector2f(0, y), gridColor));
			grid.append(Vertex(Vector2f(SCREEN_SIZE_X, y), gridColor));
		}

		grid.setPrimitiveType(PrimitiveType::Lines);
		
		//Конец инизиацлизации сетки
		segmentTexture.loadFromFile("Resources/Textures/segment.png");
		eatBuf.loadFromFile("Resources/Music/eat.ogg");		
		eatSound.setBuffer(eatBuf);
		eatSound.setVolume(19);
		//eatSound.setPitch(1.5f);
		backgroundTexture.loadFromFile("Resources/Textures/background2.png");		
		background.setTexture(&backgroundTexture);
		background.setSize(Vector2f(SCREEN_SIZE_X, SCREEN_SIZE_Y));		
		font.loadFromFile("Resources/Fonts/AGAalenBold Roman.ttf");
		text.setFont(font);	
		text.setFillColor(Color::Black);
		text.setScale(Vector2f(0.5, 0.5));		
	}
	
	void draw(RenderWindow &win)
	{
		win.draw(background);
	
		win.draw(grid);		
		for (int i = 0; i!= sVec.size(); i++)
			for (std::list<RectangleShape*>::iterator iter = sVec.at(i)->snakeSegList.begin(); iter != sVec.at(i)->snakeSegList.end(); iter++)
				win.draw((**iter));	
		win.draw(food.food);
		for (int i = 0; i != sVec.size(); i++)
		{
			text.setString(sVec.at(i)->name);
			text.setOrigin(text.getLocalBounds().width/2-10,0);
			text.setPosition(sVec.at(i)->snakeSegList.front()->getPosition().x, sVec.at(i)->snakeSegList.front()->getPosition().y-20);
			win.draw(text);
		}
	}

	void newGame()
	{

	}

	void update() 
	{
		for (int i = 0; i != sVec.size(); i++)
		{
			sVec.at(i)->keyControl(); //Обрабатываем управление
			switch (sVec.at(i)->dir)
			{
			case 0:
				sVec.at(i)->snakeSegList.back()->setPosition(sVec.at(i)->snakeSegList.front()->getPosition().x - SNAKE_PIXEL_SEGMENT_SIZE, sVec.at(i)->snakeSegList.front()->getPosition().y);
				sVec.at(i)->snakeSegList.push_front(sVec.at(i)->snakeSegList.back());
				sVec.at(i)->snakeSegList.pop_back();
				if (sVec.at(i)->snakeSegList.front()->getPosition().x < 0)
					sVec.at(i)->snakeSegList.front()->setPosition(SCREEN_SIZE_X - SNAKE_PIXEL_SEGMENT_SIZE, sVec.at(i)->snakeSegList.front()->getPosition().y);
				break;
			case 1:
				sVec.at(i)->snakeSegList.back()->setPosition(sVec.at(i)->snakeSegList.front()->getPosition().x + SNAKE_PIXEL_SEGMENT_SIZE, sVec.at(i)->snakeSegList.front()->getPosition().y);
				sVec.at(i)->snakeSegList.push_front(sVec.at(i)->snakeSegList.back());
				sVec.at(i)->snakeSegList.pop_back();
				if (sVec.at(i)->snakeSegList.front()->getPosition().x > SCREEN_SIZE_X-1)
					sVec.at(i)->snakeSegList.front()->setPosition(0, sVec.at(i)->snakeSegList.front()->getPosition().y);
				break;
			case 2:
				sVec.at(i)->snakeSegList.back()->setPosition(sVec.at(i)->snakeSegList.front()->getPosition().x, sVec.at(i)->snakeSegList.front()->getPosition().y - SNAKE_PIXEL_SEGMENT_SIZE);
				sVec.at(i)->snakeSegList.push_front(sVec.at(i)->snakeSegList.back());
				sVec.at(i)->snakeSegList.pop_back();
				if (sVec.at(i)->snakeSegList.front()->getPosition().y < 0)
					sVec.at(i)->snakeSegList.front()->setPosition(sVec.at(i)->snakeSegList.front()->getPosition().x, SCREEN_SIZE_Y - SNAKE_PIXEL_SEGMENT_SIZE);
				break;
			case 3:
				sVec.at(i)->snakeSegList.back()->setPosition(sVec.at(i)->snakeSegList.front()->getPosition().x, sVec.at(i)->snakeSegList.front()->getPosition().y + SNAKE_PIXEL_SEGMENT_SIZE);
				sVec.at(i)->snakeSegList.push_front(sVec.at(i)->snakeSegList.back());
				sVec.at(i)->snakeSegList.pop_back();
				if (sVec.at(i)->snakeSegList.front()->getPosition().y > SCREEN_SIZE_Y-1)
					sVec.at(i)->snakeSegList.front()->setPosition(sVec.at(i)->snakeSegList.front()->getPosition().x, 0);
				break;
			}
		}
		for (int i = 0; i != sVec.size(); i++)
		{
			for (int j = 0; j != sVec.size(); j++)
			{
				if (i == j)
				{
					for (std::list<RectangleShape*>::iterator iter = sVec.at(i)->snakeSegList.begin(); iter != sVec.at(i)->snakeSegList.end(); iter++)
					{
						if (sVec.at(i)->snakeSegList.front() == *iter)
							continue;
						else if (sVec.at(i)->snakeSegList.front()->getPosition() == (**iter).getPosition())
						{
							std::cout << "Cut myself" << std::endl;
							break;
						}
					}
					continue;
				}
					
				for (std::list<RectangleShape*>::iterator iter = sVec.at(j)->snakeSegList.begin(); iter != sVec.at(j)->snakeSegList.end(); iter++)
				{
					if (sVec.at(i)->snakeSegList.front()->getPosition() == (**iter).getPosition())
					{						
						std::cout << "Player " << sVec.at(i)->name << " was collided with " << sVec.at(j)->name << std::endl;
					}
				}
			}			
		}
		
		for (int i = 0; i != sVec.size(); i++)
		{
			if (sVec.at(i)->snakeSegList.front()->getPosition() == food.food.getPosition())
			{
				eatSound.play();
				RectangleShape* ptr = new RectangleShape(Vector2f(SNAKE_PIXEL_SEGMENT_SIZE, SNAKE_PIXEL_SEGMENT_SIZE));
				ptr->setPosition(sVec.at(i)->snakeSegList.back()->getPosition());
				ptr->setTexture(&segmentTexture);
				ptr->setFillColor((sVec.at(i)->getColor()));				
				sVec.at(i)->snakeSegList.push_back(ptr);
				food.spawnFood();
			}
		}	
		
	}
};