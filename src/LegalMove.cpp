#include "LegalMove.hpp"

std::vector<Move> LegalMove::generate(Position position, uint8_t side, int figure, int pos) {
	std::vector<Move> moves;
	Bitboard maskSelectedFigure = 0;

	switch (figure)
	{
	case FIGURE::KING: maskSelectedFigure = Masks::getKingMask(position.getPieces(), pos, side); break;
	case FIGURE::QUEEN: maskSelectedFigure = Masks::getQueenMask(position.getPieces(), pos, side); break;
	case FIGURE::ROOK: maskSelectedFigure = Masks::getRookMask(position.getPieces(), pos, side); break;
	case FIGURE::KNIGHT: maskSelectedFigure = Masks::getKnightMask(position.getPieces(), pos, side); break;
	case FIGURE::BISHOP: maskSelectedFigure = Masks::getBishopMask(position.getPieces(), pos, side); break;
	case FIGURE::PAWN: maskSelectedFigure = Masks::getPawnMask(position.getPieces(), side, pos); break;
	}

	while (maskSelectedFigure) {
		int defenderP = BOp::bsf(maskSelectedFigure);
		int defenderType = Move::NONE;

		maskSelectedFigure = BOp::removeBit(maskSelectedFigure, defenderP);

		for (uint8_t i = 0; i < 6; i = i + 1) {
			if (BOp::getBit(position.getPieces().getBitboard(Pieces::inverseSide(side), i), defenderP)) {
				defenderType = i;
				break;
			}
		}

		Move move = { pos, defenderP, figure, side, defenderType, Move::NONE, Type_Move::DefaultMove };

		if ((defenderP > 55 || defenderP < 8) && figure == FIGURE::PAWN) {
			move = { pos, defenderP, figure, side, defenderType, FIGURE::BISHOP, Type_Move::Transformation_Pawn };
			move = { pos, defenderP, figure, side, defenderType, FIGURE::ROOK, Type_Move::Transformation_Pawn };
			move = { pos, defenderP, figure, side, defenderType, FIGURE::KNIGHT, Type_Move::Transformation_Pawn };
			move = { pos, defenderP, figure, side, defenderType, FIGURE::QUEEN, Type_Move::Transformation_Pawn };
		}
		else if (abs(defenderP - pos) == 16) {
			move = { pos, defenderP, figure, side, defenderType, Move::NONE, Type_Move::LongMovePawn };
		}

		moves.push_back(move);
	}

	if (figure == FIGURE::KING) {
		if (position.getWSCastling() &&
			BOp::getBit(position.getPieces().getBitboard(side, FIGURE::ROOK), pos + 3) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos + 2) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos + 1)) moves.push_back({ pos, pos + 2, figure, side, Move::NONE, Move::NONE, Type_Move::ShortCastling });

		if (position.getWLCastling() &&
			BOp::getBit(position.getPieces().getBitboard(side, FIGURE::ROOK), pos - 4) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos - 3) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos - 2) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos - 1)) moves.push_back({ pos, pos - 2, figure, side, Move::NONE, Move::NONE, Type_Move::LongCastling });

		if (position.getBSCastling() &&
			BOp::getBit(position.getPieces().getBitboard(side, FIGURE::ROOK), pos + 3) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos + 2) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos + 1)) moves.push_back({ pos, pos + 2, figure, side, Move::NONE, Move::NONE, Type_Move::ShortCastling });

		if (position.getBLCastling() &&
			BOp::getBit(position.getPieces().getBitboard(side, FIGURE::ROOK), pos - 4) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos - 3) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos - 2) &&
			BOp::getBit(position.getPieces().getInverseAllFigure(), pos - 1)) moves.push_back({ pos, pos - 2, figure, side, Move::NONE, Move::NONE, Type_Move::LongCastling });
	}

	return moves;
}
