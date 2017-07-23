#include "Food.h"
#include "Snake.h"
#include "SnakeGameClass.h"
#include <iostream>

using namespace sf;

char gameMode;
static SnakeGame game;//Плохой костыль, менять я его конечно не буду

void initGameMode()
{	
	std::cout << "Choose game mode. Enter 's' one player or 'm' two players" << std::endl;
	while (gameMode != 's' && gameMode != 'm')
	{
		std::cin >> gameMode;
		if (gameMode != 's' && gameMode != 'm')
			std::cout << "!!!ERROR!!! Wrong symbol" << std::endl;
	}
	if (gameMode == 's')
	{
		game.sVec.push_back(new Snake(Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down, Color::Green));
		std::cout << "Please, enter the nickname ";
		std::cin >> game.sVec.back()->name;
	}
	else
	{
		game.sVec.push_back(new Snake(Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down, Color::Green));
		std::cout << "Player 1, please enter the nickname ";
		std::cin >> game.sVec.back()->name;
		game.sVec.push_back(new Snake(Keyboard::Key::A, Keyboard::Key::D, Keyboard::Key::W, Keyboard::Key::S, Color::Blue));
		std::cout << "Player 2, please enter the nickname ";
		std::cin >> game.sVec.back()->name;
	}
	for (int i = 0; i != game.sVec.size(); i++)
		for (std::list<RectangleShape*>::iterator iter = game.sVec.at(i)->snakeSegList.begin(); iter != game.sVec.at(i)->snakeSegList.end(); iter++)
			(**iter).setTexture(&game.segmentTexture);
	food.fSetTexture(game.segmentTexture);
	food.spawnFood();
}


void main()	
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	
	Music backgroundMusic;
	backgroundMusic.openFromFile("Resources/Music/backgroundMusic.ogg");
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(50);
	backgroundMusic.play();
	initGameMode();


	RenderWindow window(VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Snake", Style::Close);	
	window.setFramerateLimit(15);	

	while (window.isOpen())
	{		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}	
		window.clear();
		game.update();
		game.draw(window);
		window.display();
	}
}