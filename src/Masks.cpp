#include "Masks.hpp"

Bitboard Masks::getKingMask(Pieces pieces, int pos, uint8_t side) {
	return KingMask::kingMasks[pos] & pieces.getInverseSideBitboard(side);
}

Bitboard Masks::getKnightMask(Pieces pieces, int pos, uint8_t side) {
	return KnightMask::knightMasks[pos] & pieces.getInverseSideBitboard(side);
}

Bitboard Masks::getRookMask(Pieces pieces, int pos, uint8_t side) {

	Bitboard rN = getMask(pieces, SliderMask::rookMasks[pos][SliderMask::Direction::NORTH], side, true);
	Bitboard rS = getMask(pieces, SliderMask::rookMasks[pos][SliderMask::Direction::SOUTH], side, false);
	Bitboard rE = getMask(pieces, SliderMask::rookMasks[pos][SliderMask::Direction::EAST], side, true);
	Bitboard rW = getMask(pieces, SliderMask::rookMasks[pos][SliderMask::Direction::WEST], side, false);

	return rN | rS | rE | rW;
}

Bitboard Masks::getBishopMask(Pieces pieces, int pos, uint8_t side) {

	Bitboard bNW = getMask(pieces, SliderMask::bishopMasks[pos][SliderMask::Direction::NORTH], side, true);
	Bitboard bNE = getMask(pieces, SliderMask::bishopMasks[pos][SliderMask::Direction::SOUTH], side, true);
	Bitboard bSW = getMask(pieces, SliderMask::bishopMasks[pos][SliderMask::Direction::EAST], side, false);
	Bitboard bSE = getMask(pieces, SliderMask::bishopMasks[pos][SliderMask::Direction::WEST], side, false);

	return bNW | bNE | bSW | bSE;
}

Bitboard Masks::getQueenMask(Pieces pieces, int pos, uint8_t side) {
	return getBishopMask(pieces, pos, side) | getRookMask(pieces, pos, side);
}

Bitboard Masks::getPawnLeftAttackMask(Pieces pieces, uint8_t side) {
	if (side == SIDE::WHITE) {
		Bitboard mask = (pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN) << 7) & BColumns::INV_COLUMNS[7];
		return mask;
	}
	Bitboard mask = (pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN) >> 9) & BColumns::INV_COLUMNS[7];
	return mask;
}

Bitboard Masks::getPawnRightAttackMask(Pieces pieces, uint8_t side) {
	if (side == SIDE::WHITE) {
		Bitboard mask = (pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN) << 9) & BColumns::INV_COLUMNS[0];
		return mask;
	}
	Bitboard mask = (pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN) >> 7) & BColumns::INV_COLUMNS[0];
	return mask;
}

Bitboard Masks::getPawnMask(Pieces pieces, uint8_t side, int pos) {
	Bitboard mask = 0;
	mask = BOp::addBit(mask, pos);
	Bitboard result = 0;

	if (side == SIDE::WHITE) {
		if (!BOp::getBit(pieces.getAllFigure(), pos - 8)) result ^= mask >> 8;
		if (!BOp::getBit(pieces.getAllFigure(), pos - 16)) result ^= (mask & BRows::ROWS[6]) >> 16;
		if (BOp::getBit(pieces.getSideBitboard(Pieces::inverseSide(side)), pos - 7)) result ^= mask >> 7;
		if (BOp::getBit(pieces.getSideBitboard(Pieces::inverseSide(side)), pos - 9)) result ^= mask >> 9;
	}
	else {
		if (!BOp::getBit(pieces.getAllFigure(), pos + 8)) result ^= mask << 8;
		if (!BOp::getBit(pieces.getAllFigure(), pos + 16)) result ^= (mask & BRows::ROWS[1]) << 16;
		if (BOp::getBit(pieces.getSideBitboard(Pieces::inverseSide(side)), pos + 7)) result ^= mask << 7;
		if (BOp::getBit(pieces.getSideBitboard(Pieces::inverseSide(side)), pos + 9)) result ^= mask << 9;
	}

	return result;
}

bool Masks::figureIsAttacked(Pieces pieces, int pos, uint8_t side) {
	if (BOp::getBit(getPawnLeftAttackMask(pieces, side) | getPawnRightAttackMask(pieces, side), pos)) return true;

	if (getKingMask(pieces, pos, side) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::KING)) return true;

	if (getKnightMask(pieces, pos, side) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::KNIGHT)) return true;

	if (getRookMask(pieces, pos, side) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::ROOK)) return true;

	if (getBishopMask(pieces, pos, side) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::BISHOP)) return true;

	if (getQueenMask(pieces, pos, side) & pieces.getBitboard(Pieces::inverseSide(side), FIGURE::QUEEN)) return true;

	return false;
}

Bitboard Masks::getMask(Pieces pieces, Bitboard bitboard, uint8_t side, bool root) {
	Bitboard mask = 0;
	Bitboard inverseSideFigure = pieces.getSideBitboard(Pieces::inverseSide(side));
	Bitboard sideFigure = pieces.getSideBitboard(side);
	while (bitboard) {
		int pos = 0;
		if (root) pos = BOp::bsr(bitboard);
		else pos = BOp::bsf(bitboard);
		if (BOp::getBit(sideFigure, pos)) break;
		mask = BOp::addBit(mask, pos);
		if (BOp::getBit(inverseSideFigure, pos)) break;
		bitboard = BOp::removeBit(bitboard, pos);
	}
	return mask;
}
