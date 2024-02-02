#include "Masks.hpp"

Masks::Masks() {
	std::array<Bitboard, 64> kingMasks = calcKingMask();
	std::array<Bitboard, 64> knightMasks = calcKnightMask();
	std::array<Bitboard, 64> rookMasks = calcRookMask();
	std::array<Bitboard, 64> bishopMasks = calcBishopMask();
	std::array<Bitboard, 64> queenMasks = calcQueenMask();
}

std::array<Bitboard, 64> Masks::calcKingMask() {
	std::array<Bitboard, 64> tempMasks{};
	int x1, x2, y1, y2;

	for (int i = 0; i < 64; i++) {

		x1 = (i % 8 == 0) ? 0 : -1;
		x2 = (i % 8 == 7) ? 0 : 1;

		y1 = (i < 8) ? 0 : -8;
		y2 = (i > 55) ? 0 : 8;

		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y += 8) {
				if (x + y != 0) BOp::addBit(tempMasks[i], i + x + y);
			}
		}
	}
	return tempMasks;
}

std::array<Bitboard, 64> Masks::calcKnightMask() {
	std::array<Bitboard, 64> tempMasks{};
	int dx, dy;

	for (int x0 = 0; x0 < 8; x0++) {
		for (int y0 = 0; y0 < 8; y0++) {

			for (int x1 = 0; x1 < 8; x1++) {
				for (int y1 = 0; y1 < 8; y1++) {

					dx = (x1 < x0) ? (x0 - x1) : (x1 - x0);
					dy = (y1 < y0) ? (y0 - y1) : (y1 - y0);

					if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) BOp::addBit(tempMasks[y0 * 8 + x0], y1 * 8 + x1);
				}
			}

		}
	}
	return tempMasks;
}

Bitboard Masks::calcSliderMask(int pos, int direction) {
	Bitboard tempMasks{};

	int x = pos % 8;
	int y = pos / 8;

	do {
		switch (direction) {
		case Direction::NORTH: y++; break;
		case Direction::SOUTH: y--; break;
		case Direction::EAST: x++; break;
		case Direction::WEST: x--; break;
		case Direction::NORTH_EAST: y++; x++; break;
		case Direction::NORTH_WEST: y++; x--; break;
		case Direction::SOUTH_EAST: y--; x++; break;
		case Direction::SOUTH_WEST: y--; x--; break;
		}

		BOp::addBit(tempMasks, y * 8 + x);

	} while (x > 7 || x < 0 || y > 7 || y < 0);

	return tempMasks;
}

std::array<Bitboard, 64> Masks::calcRookMask() {
	std::array<Bitboard, 64> tempMasks{};

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 4; j++) {
			tempMasks[i] ^= calcSliderMask(i, j);
		}
	}

	return tempMasks;
}

std::array<Bitboard, 64> Masks::calcBishopMask() {
	std::array<Bitboard, 64> tempMasks{};

	for (int i = 0; i < 64; i++) {
		for (int j = 4; j < 8; j++) {
			tempMasks[i] = calcSliderMask(i, j);
		}
	}

	return tempMasks;
}

std::array<Bitboard, 64> Masks::calcQueenMask() {
	std::array<Bitboard, 64> tempMasks{};

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 8; j++) {
			tempMasks[i] ^= calcSliderMask(i, j);
		}
	}
	return tempMasks;
}

Bitboard Masks::getKingMask(Pieces pieces, int pos, int side, bool onlyCaptures) {
	if (onlyCaptures) return kingMasks[pos] & pieces.getSideBitboard(Pieces::inverseSide(side));
	else return kingMasks[pos] & pieces.getInverseSideBitboard(side);
}

Bitboard Masks::getKnightMask(Pieces pieces, int pos, int side, bool onlyCaptures) {
	if (onlyCaptures) return knightMasks[pos] & pieces.getSideBitboard(Pieces::inverseSide(side));
	else return knightMasks[pos] & pieces.getInverseSideBitboard(side);
}

Bitboard Masks::getRookMask(Pieces pieces, int pos, int side, bool onlyCaptures) {
	if (onlyCaptures) return rookMasks[pos] & pieces.getSideBitboard(Pieces::inverseSide(side));
	else return rookMasks[pos] & pieces.getInverseSideBitboard(side);
}

Bitboard Masks::getBishopMask(Pieces pieces, int pos, int side, bool onlyCaptures) {
	if (onlyCaptures) return bishopMasks[pos] & pieces.getSideBitboard(Pieces::inverseSide(side));
	else return bishopMasks[pos] & pieces.getInverseSideBitboard(side);
}

Bitboard Masks::getQueenMask(Pieces pieces, int pos, int side, bool onlyCaptures) {
	if (onlyCaptures) return queenMasks[pos] & pieces.getSideBitboard(Pieces::inverseSide(side));
	else return queenMasks[pos] & pieces.getInverseSideBitboard(side);
}

Bitboard Masks::getPawnShortMask(Pieces pieces, int side) {
	if (side == SIDE::WHITE) return (pieces.getBitboard(side, FIGURE::PAWN) << 8) & pieces.getInverseAllFigure();
	else return (pieces.getBitboard(side, FIGURE::PAWN) >> 8) & pieces.getInverseAllFigure();
}

Bitboard Masks::getPawnLongMask(Pieces pieces, int side) {
	Bitboard shortMask = getPawnShortMask(pieces, side);

	if (side == SIDE::WHITE) return ((shortMask & BRows::ROWS[2]) << 8) & pieces.getInverseAllFigure();
	else return ((shortMask & BRows::ROWS[5]) >> 8) & pieces.getInverseAllFigure();
}

Bitboard Masks::getPawnLeftAttackMask(Pieces pieces, int side, bool onlyCaptures) {
	if (side == SIDE::WHITE) {
		Bitboard mask = (pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN) << 7) & BColumns::INV_COLUMNS[7];
		if (!onlyCaptures) mask &= pieces.getSideBitboard(Pieces::inverseSide(side));
		return mask;
	}
	Bitboard mask = (pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN) >> 9) & BColumns::INV_COLUMNS[7];
	if (!onlyCaptures) mask &= pieces.getSideBitboard(Pieces::inverseSide(side));
	return mask;
}

Bitboard Masks::getPawnRightAttackMask(Pieces pieces, int side, bool onlyCaptures) {
	if (side == SIDE::WHITE) {
		Bitboard mask = (pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN) << 9) & BColumns::INV_COLUMNS[0];
		if (!onlyCaptures) mask &= pieces.getSideBitboard(Pieces::inverseSide(side));
		return mask;
	}
	Bitboard mask = (pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN) >> 7) & BColumns::INV_COLUMNS[0];
	if (!onlyCaptures) mask &= pieces.getSideBitboard(Pieces::inverseSide(side));
	return mask;
}

bool Masks::figureIsAttacked(Pieces pieces, int pos, int side) {
	if (BOp::getBit(getPawnLeftAttackMask(pieces, side, true) | getPawnRightAttackMask(pieces, side, true), pos)) return true;

	if (getKingMask(pieces, pos, side, true) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::KING)) return true;

	if (getKnightMask(pieces, pos, side, true) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::KNIGHT)) return true;

	if (getRookMask(pieces, pos, side, true) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::ROOK)) return true;

	if (getBishopMask(pieces, pos, side, true) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::BISHOP)) return true;

	if (getQueenMask(pieces, pos, side, true) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::QUEEN)) return true;

	return false;
}