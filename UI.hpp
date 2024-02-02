#include "Storage.hpp"
#include "Masks.hpp"
#include <iostream>
#include <math.h>

enum STATUS { MoveWhite, MoveBlack, WonWhite, WonBlack, Draw };

class UI {

	sf::RenderWindow window;
	sf::Event event{};
	Storage storage;
	Position position;

	float SIZE_CELL = 99;

	//���������� ������ �����
	float START_OF_BOARD_X = 0;
	float START_OF_BOARD_Y = 0;

	//���������� ������ �������
	static constexpr int START_OF_TABLE_X = 1000;
	static constexpr int START_OF_TABLE_Y = 0;

	void update();
	void drawCells();
	void drawFigures();

public:
	UI();
	void start();
	//int getStatus();
};