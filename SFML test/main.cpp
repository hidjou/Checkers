#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int boardSize = 63;

Sprite playerSprites[24];

int board[8][8] =
{-1, 0,-1, 0,-1, 0,-1, 0,
 0,-1, 0,-1, 0,-1, 0,-1,
-1, 0,-1, 0,-1, 0,-1, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 1, 0, 1, 0, 1, 0, 1,
 1, 0, 1, 0, 1, 0, 1, 0,
 0, 1, 0, 1, 0, 1, 0, 1 };

void loadPosition()
{
	int k = 0;
	for(int i = 0 ; i < 8 ; i++)
		for (int j = 0; j < 8; j++)
		{
			int n = board[i][j];
			if (!n) continue;
			if (n < 0) playerSprites[k].setTextureRect(IntRect(0,0,62,62));
			else playerSprites[k].setTextureRect(IntRect(62, 0, 62, 62));
			playerSprites[k].setPosition(boardSize*j, boardSize*i);
			k++;
		}
}

int main()
{
	RenderWindow window(VideoMode(500, 500), "Chererboard");

	Texture players, boardTex;

	boardTex.loadFromFile("images/board.jpg");
	players.loadFromFile("images/players.png");

	Sprite checkerBoard(boardTex);

	for (int i = 0; i < 24; i++) playerSprites[i].setTexture(players);

	loadPosition();

	bool isMoving = false;
	float dx = 0, dy = 0;
	int playerIndex = 0;

	while (window.isOpen())
	{
		Vector2i mousePosition = Mouse::getPosition(window);

		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
				window.close();

			if(_event.type == Event::MouseButtonPressed)
				if(_event.key.code == Mouse::Left)
					for(int i = 0; i < 24; i++)
					if (playerSprites[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						isMoving = true;
						playerIndex = i;
						dx = mousePosition.x - playerSprites[i].getPosition().x;
						dy = mousePosition.y - playerSprites[i].getPosition().y;
					}

			if (_event.type == Event::MouseButtonReleased)
				if (_event.key.code == Mouse::Left)
				{
					isMoving = false;
					// Position locking
					Vector2f position = playerSprites[playerIndex].getPosition() + Vector2f(boardSize / 2, boardSize / 2);
					Vector2f newPosition = Vector2f(boardSize*int(position.x / boardSize), boardSize*int(position.y / boardSize));
					playerSprites[playerIndex].setPosition(newPosition);
				}
		}

		if (isMoving) playerSprites[playerIndex].setPosition(mousePosition.x - dx, mousePosition.y - dy);

		// Draw window
		window.clear();
		window.draw(checkerBoard);
		for (int i = 0; i < 24; i++) window.draw(playerSprites[i]);
		window.display();
	}
	
	//system("PAUSE");
	return 0;
}
