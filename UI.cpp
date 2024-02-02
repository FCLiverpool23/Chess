#include "UI.hpp"

UI::UI() {
	this->storage.addTexture(SIDE::WHITE, FIGURE::KING, "king_white.png");
	this->storage.addTexture(SIDE::WHITE, FIGURE::QUEEN, "queen_white.png");
	this->storage.addTexture(SIDE::WHITE, FIGURE::ROOK, "rook_white.png");
	this->storage.addTexture(SIDE::WHITE, FIGURE::KNIGHT, "knight_white.png");
	this->storage.addTexture(SIDE::WHITE, FIGURE::BISHOP, "bishop_white.png");
	this->storage.addTexture(SIDE::WHITE, FIGURE::PAWN, "pawn_white.png");

	this->storage.addTexture(SIDE::BLACK, FIGURE::KING, "king_black.png");
	this->storage.addTexture(SIDE::BLACK, FIGURE::QUEEN, "queen_black.png");
	this->storage.addTexture(SIDE::BLACK, FIGURE::ROOK, "rook_black.png");
	this->storage.addTexture(SIDE::BLACK, FIGURE::KNIGHT, "knight_black.png");
	this->storage.addTexture(SIDE::BLACK, FIGURE::BISHOP, "bishop_black.png");
	this->storage.addTexture(SIDE::BLACK, FIGURE::PAWN, "pawn_black.png");

	this->storage.getFont("2409-font.ttf");
	this->position = { "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", Move::NONE, true, true, true, true, 1 };

	this->window.create(sf::VideoMode(1300, 1000), "Chess");
}

void UI::start() {
	while (true) {
		while (this->window.pollEvent(this->event)) {
			if (this->event.type == sf::Event::Closed) return;
			
		}
		this->update();
	}
}

void UI::update() {
	this->window.clear();
	this->drawCells();
	this->drawFigures();
	this->window.display();
}

void UI::drawCells() {
	int x = 100;
	int y = 100;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			sf::RectangleShape cell(sf::Vector2f(SIZE_CELL, SIZE_CELL));
			cell.setPosition(sf::Vector2f(x + x * j, y + y * i));

			if ((i + j) % 2 == 0) cell.setFillColor(sf::Color(255, 255, 153));
			else cell.setFillColor(sf::Color(177, 81, 36));

			window.draw(cell);
		}
	}
}

void UI::drawFigures() {
	std::array<std::array<Bitboard, 6>, 2> bs = this->position.getPieces().getBitboards();

	sf::Sprite sprite;
	sprite.setTexture(storage.getTexture(0, 1));
	sprite.setPosition(sf::Vector2f(SIZE_CELL, SIZE_CELL));

	window.draw(sprite);
}