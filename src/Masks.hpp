#include "Bitboard.hpp"
#include "Position.hpp"

enum Direction { NORTH = 0, SOUTH, WEST, EAST, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST };

class Masks {

	std::array<Bitboard, 64> kingMasks;
	std::array<Bitboard, 64> knightMasks;
	std::array<Bitboard, 64> rookMasks;
	std::array<Bitboard, 64> bishopMasks;
	std::array<Bitboard, 64> queenMasks;

	Bitboard calcSliderMask(int pos, int direction);

	std::array<Bitboard, 64> calcKingMask();
	std::array<Bitboard, 64> calcKnightMask();
	std::array<Bitboard, 64> calcRookMask();
	std::array<Bitboard, 64> calcBishopMask();
	std::array<Bitboard, 64> calcQueenMask();


public:
	Masks();

	Bitboard getKingMask(Pieces pieces, int pos, int side, bool onlyCaptures);
	Bitboard getKnightMask(Pieces pieces, int pos, int side, bool onlyCaptures);
	Bitboard getRookMask(Pieces pieces, int pos, int side, bool onlyCaptures);
	Bitboard getBishopMask(Pieces pieces, int pos, int side, bool onlyCaptures);
	Bitboard getQueenMask(Pieces pieces, int pos, int side, bool onlyCaptures);

	Bitboard getPawnShortMask(Pieces pieces, int side);
	Bitboard getPawnLongMask(Pieces pieces, int side);
	Bitboard getPawnLeftAttackMask(Pieces pieces, int side, bool onlyCaptures);
	Bitboard getPawnRightAttackMask(Pieces pieces, int side, bool onlyCaptures);

	bool figureIsAttacked(Pieces pieces, int pos, int side);
};