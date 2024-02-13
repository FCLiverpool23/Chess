#include "Bitboard.hpp"
#include "Position.hpp"
#include <iostream>
#include <bitset>

namespace KnightMask {
	static consteval std::array<Bitboard, 64> calcKnightMask() {
		std::array<Bitboard, 64> tempMasks{};
		int dx, dy;

		for (int x0 = 0; x0 < 8; x0++) {
			for (int y0 = 0; y0 < 8; y0++) {

				for (int x1 = 0; x1 < 8; x1++) {
					for (int y1 = 0; y1 < 8; y1++) {

						dx = (x1 < x0) ? (x0 - x1) : (x1 - x0);
						dy = (y1 < y0) ? (y0 - y1) : (y1 - y0);

						if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) tempMasks[y0 * 8 + x0] = BOp::addBit(tempMasks[y0 * 8 + x0], y1 * 8 + x1);
					}
				}
			}
		}
		return tempMasks;
	}

	static constexpr std::array<Bitboard, 64> knightMasks = calcKnightMask();
}

namespace KingMask {
	static consteval std::array<Bitboard, 64> calcKingMask() {
		std::array<Bitboard, 64> tempMasks{};
		int dx, dy;

		int x1, x2, y1, y2;

		for (int i = 0; i < 64; i++) {

			x1 = (i % 8 == 0) ? 0 : -1;
			x2 = (i % 8 == 7) ? 0 : 1;

			y1 = (i < 8) ? 0 : -8;
			y2 = (i > 55) ? 0 : 8;

			for (int x = x1; x <= x2; x++) {
				for (int y = y1; y <= y2; y += 8) {
					if (x + y != 0) tempMasks[i] = BOp::addBit(tempMasks[i], i + x + y);
				}
			}
		}
		return tempMasks;
	}

	static constexpr std::array<Bitboard, 64> kingMasks = calcKingMask();
}

namespace SliderMask {
	enum Direction { NORTH = 0, SOUTH, WEST, EAST, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST };

	static consteval Bitboard calcSliderMask(int pos, int direction) {
		Bitboard tempMasks{};

		int x = pos % 8;
		int y = pos / 8;

		while(1) {
			switch (direction) {
			case Direction::NORTH: y--; break;
			case Direction::SOUTH: y++; break;
			case Direction::EAST: x--; break;
			case Direction::WEST: x++; break;
			case Direction::NORTH_EAST: y--; x--; break;
			case Direction::NORTH_WEST: y--; x++; break;
			case Direction::SOUTH_EAST: y++; x--; break;
			case Direction::SOUTH_WEST: y++; x++; break;
			}

			if (x > 7 || x < 0 || y > 7 || y < 0) break;

			tempMasks = BOp::addBit(tempMasks, y * 8 + x);

		};

		return tempMasks;
	}

	static consteval std::array<std::array<Bitboard, 4>, 64> calcMasks(int col) {
		std::array<std::array<Bitboard, 4>, 64> masks{};
		for (int i = 0; i < 64; i++) {
			for (int j = col; j < col + 4; j++) {
				masks[i][j - col] = calcSliderMask(i, j);
			}
		}
		return masks;
	}

	static constexpr std::array<std::array<Bitboard, 4>, 64> rookMasks = calcMasks(0);
	static constexpr std::array<std::array<Bitboard, 4>, 64> bishopMasks = calcMasks(4);
}

namespace EntrancePawn {
	static consteval std::array<Bitboard, 64> calcYourPawnEntrance() {
		std::array<Bitboard, 64> masks{};

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				for (int y1 = y - 1; y1 >= 0; y1--) {
					if (x != 0) BOp::addBit(masks[y * 8 + x], y1 * 8 + x - 1);
					if (x != 7) BOp::addBit(masks[y * 8 + x], y1 * 8 + x + 1);
					BOp::addBit(masks[y * 8 + x], y1 * 8 + x);
				}
			}
		}
		return masks;
	}

	static consteval std::array<Bitboard, 64> calcOpponentPawnEntrance() {
		std::array<Bitboard, 64> masks{};

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				for (int y1 = y + 1; y1 < 8; y1++) {
					if (x != 0) BOp::addBit(masks[y * 8 + x], y1 * 8 + x - 1);
					if (x != 7) BOp::addBit(masks[y * 8 + x], y1 * 8 + x + 1);
					BOp::addBit(masks[y * 8 + x], y1 * 8 + x);
				}
			}
		}
		return masks;
	}
	
	static constexpr std::array<Bitboard, 64> yourPawnEntrance = calcYourPawnEntrance();
	static constexpr std::array<Bitboard, 64> opponentPawnEntrance = calcOpponentPawnEntrance();
}

namespace PawnShield {
	static consteval std::array<Bitboard, 64> calcYourPawnShield() {
		std::array<Bitboard, 64> masks{};

		for (int x = 0; x < 8; x++) {
			for (int y = 1; y < 8; y++) {
				if (x != 0) BOp::addBit(masks[y * 8 + x], (y - 1) * 8 + x - 1);
				if (x != 7) BOp::addBit(masks[y * 8 + x], (y - 1) * 8 + x + 1);
				BOp::addBit(masks[y * 8 + x], (y - 1) * 8 + x);
				
				if (y != 1) {
					if (x != 0) BOp::addBit(masks[y * 8 + x], (y - 2) * 8 + x - 1);
					if (x != 7) BOp::addBit(masks[y * 8 + x], (y - 2) * 8 + x + 1);
					BOp::addBit(masks[y * 8 + x], (y - 2) * 8 + x);
				}
			}
		}
		return masks;
	}

	static consteval std::array<Bitboard, 64> calcOpponentPawnShield() {
		std::array<Bitboard, 64> masks{};

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 7; y++) {
				if (x != 0) BOp::addBit(masks[y * 8 + x], (y + 1) * 8 + x - 1);
				if (x != 7) BOp::addBit(masks[y * 8 + x], (y + 1) * 8 + x + 1);
				BOp::addBit(masks[y * 8 + x], (y + 1) * 8 + x);

				if (y != 6) {
					if (x != 0) BOp::addBit(masks[y * 8 + x], (y + 2) * 8 + x - 1);
					if (x != 7) BOp::addBit(masks[y * 8 + x], (y + 2) * 8 + x + 1);
					BOp::addBit(masks[y * 8 + x], (y + 2) * 8 + x);
				}
			}
		}
		return masks;
	}

	static constexpr std::array<Bitboard, 64> yourPawnSheild = calcYourPawnShield();
	static constexpr std::array<Bitboard, 64> opponentPawnSheild = calcOpponentPawnShield();
}

class Masks {
	static Bitboard getMask(Pieces pieces, Bitboard bitboard, uint8_t side, bool root);
public:
	static Bitboard getKingMask(Pieces pieces, int pos, uint8_t side);
	static Bitboard getKnightMask(Pieces pieces, int pos, uint8_t side);
	static Bitboard getRookMask(Pieces pieces, int pos, uint8_t side);
	static Bitboard getBishopMask(Pieces pieces, int pos, uint8_t side);
	static Bitboard getQueenMask(Pieces pieces, int pos, uint8_t side);

	static Bitboard getPawnLeftAttackMask(Pieces pieces, uint8_t side, uint8_t yourSide);
	static Bitboard getPawnRightAttackMask(Pieces pieces, uint8_t side, uint8_t yourSide);

	static Bitboard getPawnMask(Pieces pieces, uint8_t side, int pos, uint8_t yourSide);

	static bool figureIsAttacked(Pieces pieces, int pos, uint8_t side, uint8_t yourSide);
};