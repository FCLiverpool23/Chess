#include "LegalMove.hpp"

ListMove LegalMove::generateMove(Position position, int side, int figure) {
	ListMove moves;

	if (figure == FIGURE::PAWN) {
		Bitboard pawnLeftAttack = Masks::getPawnLeftAttackMask(position.getPieces(), side, false);
		Bitboard pawnRightAttack = Masks::getPawnRightAttackMask(position.getPieces(), side, false);


	}
	
}