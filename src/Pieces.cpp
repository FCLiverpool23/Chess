#include "Pieces.hpp"

Pieces::Pieces() = default;

Pieces::Pieces(const std::string& fen) {
	int x = 0;
	int y = 7;

	int side = 0;

	for (auto ch : fen) {
		if (ch == '/') {
			x = 0; y--;
		}
		else if (std::isdigit(ch)) x += ch - '0';
		else {
			if (std::isupper(ch)) {
				side = SIDE::BLACK;
				ch = std::tolower(ch);
			}
			else side = SIDE::BLACK;

			switch (ch)
			{
			case 'r': Bitboards[side][FIGURE::ROOK] = BOp::addBit(Bitboards[side][FIGURE::ROOK], y * 8 + x); break;
			case 'n': Bitboards[side][FIGURE::KNIGHT] = BOp::addBit(Bitboards[side][FIGURE::KNIGHT], y * 8 + x); break;
			case 'b': Bitboards[side][FIGURE::BISHOP] = BOp::addBit(Bitboards[side][FIGURE::BISHOP], y * 8 + x); break;
			case 'k': Bitboards[side][FIGURE::KING] = BOp::addBit(Bitboards[side][FIGURE::KING], y * 8 + x); break;
			case 'q': Bitboards[side][FIGURE::QUEEN] = BOp::addBit(Bitboards[side][FIGURE::QUEEN], y * 8 + x); break;
			case 'p': Bitboards[side][FIGURE::PAWN] = BOp::addBit(Bitboards[side][FIGURE::PAWN], y * 8 + x); break;
			default:break;
			}
			x++;
		}
	}
	updateBitboard();
}	

void Pieces::updateBitboard() {
	SideBitboards[SIDE::WHITE] = Bitboards[SIDE::WHITE][FIGURE::KING] |
		Bitboards[SIDE::WHITE][FIGURE::QUEEN] |
		Bitboards[SIDE::WHITE][FIGURE::ROOK] |
		Bitboards[SIDE::WHITE][FIGURE::KNIGHT] |
		Bitboards[SIDE::WHITE][FIGURE::BISHOP] |
		Bitboards[SIDE::WHITE][FIGURE::PAWN];

	SideBitboards[SIDE::BLACK] = Bitboards[SIDE::BLACK][FIGURE::KING] |
		Bitboards[SIDE::BLACK][FIGURE::QUEEN] |
		Bitboards[SIDE::BLACK][FIGURE::ROOK] |
		Bitboards[SIDE::BLACK][FIGURE::KNIGHT] |
		Bitboards[SIDE::BLACK][FIGURE::BISHOP] |
		Bitboards[SIDE::BLACK][FIGURE::PAWN];

	InverseSideBitboards[SIDE::WHITE] = ~SideBitboards[SIDE::WHITE];
	InverseSideBitboards[SIDE::BLACK] = ~SideBitboards[SIDE::BLACK];

	AllFigure = SideBitboards[SIDE::BLACK] | SideBitboards[SIDE::WHITE];
	InverseAllFigure = ~AllFigure;
}

int Pieces::inverseSide(int side) {
	return ~side;
}

std::array<std::array<Bitboard, 6>, 2> Pieces::getBitboards() {
	return Bitboards;
}

Bitboard Pieces::getBitboard(int side, int figure) {
	return Bitboards[side][figure];
}

Bitboard Pieces::getSideBitboard(int side) {
	return SideBitboards[side];
}

Bitboard Pieces::getInverseSideBitboard(int side) {
	return InverseSideBitboards[side];
}

Bitboard Pieces::getAllFigure() {
	return AllFigure;
}

Bitboard Pieces::getInverseAllFigure() {
	return InverseAllFigure;
}

void Pieces::setBitboard(int side, int figure, Bitboard bb) {
	Bitboards[side][figure] = bb;
}