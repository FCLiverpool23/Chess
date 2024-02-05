#include "Position.hpp"

Position::Position() = default;

Position::Position(const std::string& fen, int enPassant, bool wLCastling, bool wSCastling, bool bLCastling, bool bSCastling, float countMove) {
	this->pieces = { fen };
	this->hash = { pieces, wLCastling, wSCastling, bLCastling, bSCastling };
	this->repetition.addHash(hash);

	this->enPassant = enPassant;
	this->wLCastling = wLCastling;
	this->wSCastling = wSCastling;
	this->bLCastling = bLCastling;
	this->bSCastling = bSCastling;

	this->countMove = countMove;
	this->countMoveDraw = 0;
}

void Position::move(Move move) {
	removePiece(move.GetInitialPosition(), move.GetTypeFigure(), move.GetSideFigure());
	addPiece(move.GetFinalPosition(), move.GetTypeFigure(), move.GetSideFigure());

	if (move.GetEatFigure() != Move::NONE) removePiece(move.GetFinalPosition(), move.GetEatFigure(), Pieces::inverseSide(move.GetSideFigure()));

	switch (move.GetTypeFigure()){

	case Type_Move::DefaultMove: break;

	case Type_Move::LongMovePawn:
		changeEnPassant((move.GetInitialPosition() + move.GetFinalPosition()) / 2);
		break;

	case Type_Move::EnPassantCapture:
		if (move.GetSideFigure() == SIDE::WHITE) removePiece(move.GetFinalPosition() - 8, FIGURE::PAWN, SIDE::BLACK);
		else removePiece(move.GetFinalPosition() + 8, FIGURE::PAWN, SIDE::WHITE);
		break;

	case Type_Move::ShortCastling:
		removePiece(BOp::bsr(pieces.getBitboard(move.GetSideFigure(), FIGURE::ROOK)), FIGURE::ROOK, move.GetSideFigure());
		addPiece(move.GetFinalPosition() - 1, FIGURE::ROOK, move.GetSideFigure());
		break;

	case Type_Move::LongCastling:
		removePiece(BOp::bsf(pieces.getBitboard(move.GetSideFigure(), FIGURE::ROOK)), FIGURE::ROOK, move.GetSideFigure());
		addPiece(move.GetFinalPosition() + 1, FIGURE::ROOK, move.GetSideFigure());
		break;

	case Type_Move::Transformation_Pawn:
		removePiece(move.GetFinalPosition(), move.GetTypeFigure(), move.GetSideFigure());
		addPiece(move.GetFinalPosition(), move.GetTypeFigure(), move.GetSideFigure());
		break;
	}

	pieces.updateBitboard();

	if (move.GetTypeMove() != Type_Move::LongMovePawn) changeEnPassant(Move::NONE);

	switch (move.GetInitialPosition()) {
	case 0:
		removeWLCastling();
		break;
	case 4:
		removeWLCastling();
		removeWSCastling();
		break;
	case 7:
		removeWSCastling();
		break;
	case 56:
		removeBLCastling();
		break;
	case 60:
		removeBLCastling();
		removeBSCastling();
		break;
	case 63:
		removeBSCastling();
		break;
	}

	updateCountMove();
	updateCountMoveDraw(move.GetTypeFigure() == FIGURE::PAWN || move.GetEatFigure() != Move::NONE);

	if (move.GetTypeFigure() == FIGURE::PAWN || move.GetEatFigure() != Move::NONE) {
		repetition.clear();
	}
	repetition.addHash(hash);

}

void Position::addPiece(int pos, int figure, uint8_t side) {
	if (!BOp::getBit(pieces.getBitboard(side, figure), pos)) {
		pieces.setBitboard(side, figure, BOp::addBit(pieces.getBitboard(side, figure), pos));
		hash.zobrist(pos, figure, side);
	}
}

void Position::removePiece(int pos, int figure, uint8_t side) {
	if (BOp::getBit(pieces.getBitboard(side, figure), pos)) {
		pieces.setBitboard(side, figure, BOp::removeBit(pieces.getBitboard(side, figure), pos));
		hash.zobrist(pos, figure, side);
	}
}

void Position::removeWLCastling() {
	if (wLCastling) {
		wLCastling = false;
		hash.zobristWLCastling();
	}
}

void Position::removeWSCastling() {
	if (wSCastling) {
		wSCastling = false;
		hash.zobristWSCastling();
	}
}

void Position::removeBLCastling() {
	if (bLCastling) {
		bLCastling = false;
		hash.zobristBLCastling();
	}
}

void Position::removeBSCastling() {
	if (bSCastling) {
		bSCastling = false;
		hash.zobristBSCastling();
	}
}

void Position::updateCountMove() {
	countMove += 0.5f;
	hash.zobristSide();
}

void Position::updateCountMoveDraw(bool break_event) {
	if (break_event) countMoveDraw = 0;
	else countMoveDraw += 0.5f;
}

void Position::changeEnPassant(int enPassant) {
	this->enPassant = enPassant;
}