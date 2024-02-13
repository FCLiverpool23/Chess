#include "Masks.hpp"
#include <vector>

class LegalMove {

	//static void pieceMaskToMoves(Pieces pieces, Bitboard mask, int pos, int figure, uint8_t side, std::vector<Move>& moves);
	//static void pawnMaskToMove(Pieces pieces, Bitboard mask, int pos, uint8_t side, bool pawnAttack, Type_Move flag, std::vector<Move>& moves);

	static bool IsLegal(Pieces pieces, Move move, uint8_t yourSide);

public:
	static std::vector<Move> generate(Position position, uint8_t side, int figure, int pos, uint8_t yourSide);
};