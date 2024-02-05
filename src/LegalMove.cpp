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
		moves.push_back(move);
		
	}

	return moves;
}

//bool LegalMove::IsLegal(Pieces pieces, Move move) {
//	pieces.setBitboard(move.GetSideFigure(), move.GetTypeFigure(), BOp::removeBit(pieces.getBitboard(move.GetSideFigure(), move.GetTypeFigure()), move.GetInitialPosition()));
//	pieces.setBitboard(move.GetSideFigure(), move.GetTypeFigure(), BOp::addBit(pieces.getBitboard(move.GetSideFigure(), move.GetTypeFigure()), move.GetFinalPosition()));
//	if (move.GetEatFigure() != Move::NONE) {
//		pieces.setBitboard(move.GetEatFigure(), Pieces::inverseSide(move.GetSideFigure()), BOp::removeBit(pieces.getBitboard(move.GetEatFigure(), Pieces::inverseSide(move.GetSideFigure())), move.GetFinalPosition()));
//	}
//	if (move.GetTypeMove() == Type_Move::EnPassantCapture) {
//		if (move.GetSideFigure() == SIDE::WHITE) pieces.setBitboard(SIDE::BLACK, FIGURE::PAWN, BOp::removeBit(pieces.getBitboard(SIDE::BLACK, FIGURE::PAWN), move.GetFinalPosition() - 8));
//		else pieces.setBitboard(SIDE::WHITE, FIGURE::PAWN, BOp::removeBit(pieces.getBitboard(SIDE::WHITE, FIGURE::PAWN), move.GetFinalPosition() + 8));
//	}
//
//	pieces.updateBitboard();
//
//	return !Masks::figureIsAttacked(pieces, BOp::bsf(pieces.getBitboard(move.GetSideFigure(), FIGURE::KING)), move.GetSideFigure());
//}