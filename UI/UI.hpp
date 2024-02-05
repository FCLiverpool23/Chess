#include "Storage.hpp"
#include "../src/Masks.hpp"
#include <iostream>

enum STATUS { MoveWhite, MoveBlack, WonWhite, WonBlack, Draw };

class UI {

	sf::RenderWindow window;
	sf::Event event{};
	Position position;

	float SizeCell = 99;

	sf::Vector2f PointStartBoard;
	sf::Vector2i SelectedCell;

	void update();
	void drawCells();
	void drawFigures();

	sf::Vector2f getPositionCell(int x, int y);
	int getArgsTexture(int x, int y);


public:
	UI();
	void start();
	//int getStatus();
};