#include "UI.hpp"

UI::UI() {
	Storage::getPtr()->addTexture(SIDE::WHITE * 6 + FIGURE::KING, "wK.png");
	Storage::getPtr()->addTexture(SIDE::WHITE * 6 + FIGURE::QUEEN, "wQ.png");
	Storage::getPtr()->addTexture(SIDE::WHITE * 6 + FIGURE::ROOK, "wR.png");
	Storage::getPtr()->addTexture(SIDE::WHITE * 6 + FIGURE::KNIGHT, "wN.png");
	Storage::getPtr()->addTexture(SIDE::WHITE * 6 + FIGURE::BISHOP, "wB.png");
	Storage::getPtr()->addTexture(SIDE::WHITE * 6 + FIGURE::PAWN, "wP.png");

	Storage::getPtr()->addTexture(SIDE::BLACK * 6 + FIGURE::KING, "bK.png");
	Storage::getPtr()->addTexture(SIDE::BLACK * 6 + FIGURE::QUEEN, "bQ.png");
	Storage::getPtr()->addTexture(SIDE::BLACK * 6 + FIGURE::ROOK, "bR.png");
	Storage::getPtr()->addTexture(SIDE::BLACK * 6 + FIGURE::KNIGHT, "bN.png");
	Storage::getPtr()->addTexture(SIDE::BLACK * 6 + FIGURE::BISHOP, "bB.png");
	Storage::getPtr()->addTexture(SIDE::BLACK * 6 + FIGURE::PAWN, "bP.png");

	this->PointStartBoard = sf::Vector2f(100, 100);
	this->SelectedCell = sf::Vector2i(INT_MAX, INT_MAX);

	Storage::getPtr()->getFont("2409-font.ttf");
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
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			sf::RectangleShape cell(sf::Vector2f(SizeCell, SizeCell));
			cell.setPosition(getPositionCell(x, y));

			if (SelectedCell == sf::Vector2i(x, y)) {
				cell.setOutlineThickness(2);
				cell.setOutlineColor(sf::Color(100, 50, 50));
			}

			if ((x + y) % 2 == 0) cell.setFillColor(sf::Color(255, 255, 153));
			else cell.setFillColor(sf::Color(177, 81, 36));

			window.draw(cell);
		}
	}
}

void UI::drawFigures() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			sf::Sprite sprite;
			int result = getArgsTexture(x, y);
			if (result == Move::NONE) continue;

			sprite.setTexture(*Storage::getPtr()->getTexture(result));
			sprite.setScale(PointStartBoard.x / sprite.getLocalBounds().width, PointStartBoard.y / sprite.getLocalBounds().height);
			sprite.setPosition(this->getPositionCell(x, y));

			this->window.draw(sprite);
		}
	}
}

sf::Vector2f UI::getPositionCell(int x, int y) {
	return sf::Vector2f(PointStartBoard.x + (SizeCell + 2) * x, PointStartBoard.y + (SizeCell + 2) * y);
}

int UI::getArgsTexture(int x, int y) {
	int pos = y * 8 + x;
	std::array<std::array<Bitboard, 6>, 2> bs = position.getPieces().getBitboards();

	if (BOp::getBit(bs[SIDE::WHITE][FIGURE::KING], pos)) return (SIDE::WHITE * 6 + FIGURE::KING);
	
	if (BOp::getBit(bs[SIDE::WHITE][FIGURE::QUEEN], pos)) return (SIDE::WHITE * 6 + FIGURE::QUEEN);

	if (BOp::getBit(bs[SIDE::WHITE][FIGURE::KNIGHT], pos)) return (SIDE::WHITE * 6 + FIGURE::KNIGHT);

	if (BOp::getBit(bs[SIDE::WHITE][FIGURE::BISHOP], pos)) return (SIDE::WHITE * 6 + FIGURE::BISHOP);

	if (BOp::getBit(bs[SIDE::WHITE][FIGURE::ROOK], pos)) return (SIDE::WHITE * 6 + FIGURE::ROOK);

	if (BOp::getBit(bs[SIDE::WHITE][FIGURE::PAWN], pos)) return (SIDE::WHITE * 6 + FIGURE::PAWN);

	if (BOp::getBit(bs[SIDE::BLACK][FIGURE::KING], pos)) return (SIDE::BLACK * 6 + FIGURE::KING);

	if (BOp::getBit(bs[SIDE::BLACK][FIGURE::QUEEN], pos)) return (SIDE::BLACK * 6 + FIGURE::QUEEN);

	if (BOp::getBit(bs[SIDE::BLACK][FIGURE::KNIGHT], pos)) return (SIDE::BLACK * 6 + FIGURE::KNIGHT);

	if (BOp::getBit(bs[SIDE::BLACK][FIGURE::BISHOP], pos)) return (SIDE::BLACK * 6 + FIGURE::BISHOP);

	if (BOp::getBit(bs[SIDE::BLACK][FIGURE::ROOK], pos)) return (SIDE::BLACK * 6 + FIGURE::ROOK);

	if (BOp::getBit(bs[SIDE::BLACK][FIGURE::PAWN], pos)) return (SIDE::BLACK * 6 + FIGURE::PAWN);

	return Move::NONE;
}