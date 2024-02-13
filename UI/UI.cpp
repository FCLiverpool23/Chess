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

	Storage::getPtr()->addFont("2409-font.ttf");
	Storage::getPtr()->addCross("sprites/RedCross.png");

	

	this->position = { SIDE::WHITE, Move::NONE, true, true, true, true, 1 };

	this->window.create(sf::VideoMode(1300, 1000), "Chess");
}

void UI::start() {
	while (true) {
		while (this->window.pollEvent(this->event)) {
			if (this->event.type == sf::Event::Closed) return;

			if (this->event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mouse = sf::Mouse::getPosition(this->window);
				sf::Vector2i cell = sf::Vector2i(INT_MAX, INT_MAX);

				for (int x = 0; x < 8; x++) {
					for (int y = 0; y < 8; y++) {

						int result = getArgsTexture(x, y);

						if (mouse.x > (int)getPositionCell(x, y).x && mouse.y > (int)getPositionCell(x, y).y && mouse.x < (int)(getPositionCell(x, y).x + SizeCell)
							&& mouse.y < (int)(getPositionCell(x, y).y + SizeCell) && (result != Move::NONE || SelectedCell != sf::Vector2i(INT_MAX, INT_MAX))) cell = sf::Vector2i(x, y);
					}
				}


				if (SelectedCell == sf::Vector2i(INT_MAX, INT_MAX)) SelectedCell = cell;
				else {

					for (int i = 0; i < actualMoves.size(); i++) {
						if (actualMoves[i].GetFinalPosition() == cell.y * 8 + cell.x) position.move(actualMoves[i]);
					}

					SelectedCell = sf::Vector2i(INT_MAX, INT_MAX);
				}

			}
			this->update();
		}
	}
} 

void UI::update() {
	this->window.clear();
	drawCells();
	drawFigures();
	drawAttackedCell();
	this->window.display();
}

void UI::drawCells() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			sf::RectangleShape cell(sf::Vector2f(SizeCell, SizeCell));
			cell.setPosition(getPositionCell(x, y));

			if (SelectedCell == sf::Vector2i(x, y)) {
				cell.setOutlineThickness(2);
				cell.setOutlineColor(sf::Color(124, 252, 0));
			}

			if ((x + y) % 2 == 0) cell.setFillColor(sf::Color(214, 174, 1));
			else cell.setFillColor(sf::Color(77, 34, 14));

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
			sprite.setPosition(getPositionCell(x, y));

			this->window.draw(sprite);
		}
	}
}

void UI::drawAttackedCell() {

	if (SelectedCell == sf::Vector2i(INT_MAX, INT_MAX)) return;
	Bitboard allFigure = position.getPieces().getAllFigure();
	sf::Sprite redCross;
	redCross.setTexture(*Storage::getPtr()->getCross());
	redCross.setScale(PointStartBoard.x / redCross.getLocalBounds().width, PointStartBoard.y / redCross.getLocalBounds().height);

	int result = getArgsTexture(SelectedCell.x, SelectedCell.y);
	if (result == Move::NONE) return;
	
	uint8_t side = result / 6;
	int figure = result % 6;

	std::vector<Move> moves = LegalMove::generate(position, side, figure, SelectedCell.y * 8 + SelectedCell.x);

	actualMoves = moves;

	for (int i = 0; i < moves.size(); i++) {
		int x = moves[i].GetFinalPosition() % 8;
		int y = moves[i].GetFinalPosition() / 8;

		if (BOp::getBit(allFigure, moves[i].GetFinalPosition())) {
			redCross.setPosition(getPositionCell(x, y));
			this->window.draw(redCross);
		}
		else {
			sf::CircleShape shape(SizeCell / 6);
			shape.setPosition(sf::Vector2f(PointStartBoard.x + 2 * SizeCell / 6 + (SizeCell + 2) * x, PointStartBoard.y + 2 * SizeCell / 6 + (SizeCell + 2) * y));
			shape.setFillColor(sf::Color(124, 252, 0));

			this->window.draw(shape);
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