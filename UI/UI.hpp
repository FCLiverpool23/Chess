#include "Storage.hpp"
#include "../src/LegalMove.hpp"
#include <iostream>

enum STATUS { MoveWhite, MoveBlack, WonWhite, WonBlack, Draw };

class UI {

	sf::RenderWindow window;
	sf::Event event{};
	Position position;

	float SizeCell = 99;

	sf::Vector2f PointStartBoard;
	sf::Vector2i SelectedCell;

	std::vector<Move> actualMoves;

	void update();
	void drawCells();
	void drawFigures();
	void drawAttackedCell();

	sf::Vector2f getPositionCell(int x, int y);
	int getArgsTexture(int x, int y);

public:
	UI();
	void start();
	//int getStatus();
};