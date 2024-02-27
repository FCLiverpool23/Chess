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
	this->PointStartFigure = sf::Vector2f(PointStartBoard.x * 9, PointStartBoard.y);
	this->PointStartTable = sf::Vector2f(PointStartBoard.x * 15, PointStartBoard.y);
	this->SelectedCell = sf::Vector2i(INT_MAX, INT_MAX);

	Storage::getPtr()->addFont("2409-font.ttf");
	Storage::getPtr()->addCross("sprites/RedCross.png");
<<<<<<< HEAD
=======

	

	this->position = { SIDE::WHITE, Move::NONE, true, true, true, true, 1 };
>>>>>>> 67409e8dde24e0eae7ae7faaab30ba3fc896fe49

	this->position = { SIDE::WHITE, Move::NONE, true, true, true, true, 1 };

	this->window.create(sf::VideoMode(1800, 1000), "Chess");
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
				
				if (SelectedCell == sf::Vector2i(INT_MAX, INT_MAX)) {
					if (fabs((int)position.getCountMove() - position.getCountMove()) > 1e-7f && BOp::getBit(position.getPieces().getSideBitboard(SIDE::WHITE), cell.y * 8 + cell.x)) continue;
					if (fabs((int)position.getCountMove() - position.getCountMove()) <= 1e-7f && BOp::getBit(position.getPieces().getSideBitboard(SIDE::BLACK), cell.y * 8 + cell.x)) continue;
					SelectedCell = cell;
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
	drawTableMove();
	this->window.display();
}

void UI::drawCells() {
	sf::Text number;
	number.setFont(*Storage::getPtr()->getFont());
	number.setCharacterSize(40);
	for (char ch = 'A'; ch < 'I'; ch++) {
		number.setString(ch);
		number.setPosition(sf::Vector2f((ch - '@') * SizeCell + SizeCell / 2 - number.getLocalBounds().width / 2, 0.5 * SizeCell));
		window.draw(number);
	}
	for (int x = 0; x < 8; x++) {
		number.setString(std::to_string(x + 1));
		number.setPosition(sf::Vector2f(8 * SizeCell/10, (x + 1) * SizeCell + SizeCell / 2 - number.getLocalBounds().height / 2));
		window.draw(number);
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

	for (int i = 0; i < 2; i++) {
		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 3; y++) {
				sf::RectangleShape cell(sf::Vector2f(SizeCell, SizeCell));
				cell.setPosition(20 + PointStartFigure.x + x * SizeCell, PointStartFigure.y + y * SizeCell);
				cell.setFillColor(sf::Color(125, 77, 93));
				cell.setOutlineThickness(2);
				cell.setOutlineColor(sf::Color(255, 255, 255));
				window.draw(cell);
			}
		}
		PointStartFigure.y = PointStartBoard.y * 6;
	}
	PointStartFigure.y = PointStartBoard.y;
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

	uint8_t side = Pieces::inverseSide(position.getYourColor());
	int x = 0;
	int y = 0;

	for (int l = 0; l < 2; l++) {
		for (int i = 0; i < 6; i++) {
			sf::Sprite sprite;
			int count = BOp::count(position.getPieces().getBitboard(side, i));
			int countMax = 0;
			if (i == FIGURE::PAWN) countMax = 8;
			else if (i == FIGURE::KNIGHT) countMax = 2;
			else if (i == FIGURE::ROOK) countMax = 2;
			else if (i == FIGURE::BISHOP) countMax = 2;
			else if (i == FIGURE::QUEEN) countMax = 1;
			sprite.setTexture(*Storage::getPtr()->getTexture(side * 6 + i));
			sprite.setScale(PointStartBoard.x / sprite.getLocalBounds().width, PointStartBoard.y / sprite.getLocalBounds().height);
			for (int j = count; j < countMax; j++) {
				sprite.setPosition(20 + PointStartFigure.x + x * SizeCell, PointStartFigure.y + y * SizeCell);
				this->window.draw(sprite);
				if (x == 4) { y++; x = 0; }
				else x++;
			}
		}
		side = position.getYourColor();
		PointStartFigure.y = PointStartBoard.y * 6;
		x = 0; y = 0;
	}
	PointStartFigure.y = PointStartBoard.y;
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

	std::vector<Move> moves = LegalMove::generate(position, side, figure, SelectedCell.y * 8 + SelectedCell.x, position.getYourColor());

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

void UI::drawTableMove() {
	drawTable(0, "Белые", true);
	drawTable(0, "Черные", false);
	for (int i = 0; i < position.getListAllMove().size(); i++) {
		std::string text;

		if (position.getListAllMove()[i].GetTypeMove() == Type_Move::LongCastling) text = "0-0-0";
		else if (position.getListAllMove()[i].GetTypeMove() == Type_Move::ShortCastling) text = "0-0";
		else {
			text = positionToString(position.getListAllMove()[i].GetInitialPosition());
			if (position.getListAllMove()[i].GetEatFigure() == Move::NONE) text += " - ";
			else text += " : ";
			text += positionToString(position.getListAllMove()[i].GetFinalPosition());
		}

		drawTable(std::floor(i / 2) + 1, text, i % 2 == 0);
		
	}
}

void UI::drawTable(int number, std::string textCell, bool flag) {
	sf::Text text;
	text.setFont(*Storage::getPtr()->getFont());
	text.setCharacterSize(20);
	text.setFillColor(sf::Color(0, 0, 0));

	sf::RectangleShape cell(sf::Vector2f(SizeCell, SizeCell / 2));
	cell.setFillColor(sf::Color(255, 255, 255));
	cell.setOutlineThickness(2);
	cell.setOutlineColor(sf::Color(0, 0, 0));

	float x = (flag) ? PointStartTable.x : (PointStartTable.x + cell.getSize().x);
	
	cell.setPosition(x, PointStartTable.y + cell.getSize().y * number);
	text.setString(textCell);
	text.setPosition(x + cell.getSize().x / 2 - text.getLocalBounds().width, PointStartTable.y + cell.getSize().y * number + cell.getSize().y / 2 - text.getLocalBounds().height);
	this->window.draw(cell);
	this->window.draw(text);
}

std::string UI::positionToString(int pos) {
	int y = pos / 8;
	int x = pos % 8;

	std::string text;
	text = 'A' + x;
	text += std::to_string(y+1);
	return text;
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