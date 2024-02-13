#include "StaticEvaluation.hpp"

int StaticEvaluation::evaluation(Pieces pieces, uint8_t yourSide, bool wSCastling, bool wLCastling, bool bSCastling, bool bLCastling, bool commitedCastligY, bool commitedCastligO) {
	int evaluation = 0;

	evaluation += material(pieces, yourSide) + mobility(pieces, yourSide) + checkConnectedPawn(pieces, yourSide) +
		checkCrachCastling(wSCastling, wLCastling, bSCastling, bLCastling, commitedCastligY, commitedCastligO, yourSide) +
		checkDoublePawn(pieces, yourSide) + checkPawnEntrance(pieces, yourSide) + checkPawnShield(pieces, commitedCastligY, commitedCastligO, yourSide) +
		checkTwoBishop(pieces, yourSide); 
	if (material(pieces, yourSide) > 0) evaluation += endGame(pieces, yourSide, yourSide);
	else evaluation += endGame(pieces, yourSide, Pieces::inverseSide(yourSide));

	return evaluation;
}

int StaticEvaluation::material(Pieces pieces, uint8_t yourSide) {
	int material = 0;

	material += Material::Pawn * (BOp::count(pieces.getBitboard(yourSide, FIGURE::PAWN)) - BOp::count(pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::PAWN)));
	material += Material::Knight * (BOp::count(pieces.getBitboard(yourSide, FIGURE::KNIGHT)) - BOp::count(pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::KNIGHT)));
	material += Material::Bishop * (BOp::count(pieces.getBitboard(yourSide, FIGURE::BISHOP)) - BOp::count(pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::BISHOP)));
	material += Material::Rook * (BOp::count(pieces.getBitboard(yourSide, FIGURE::ROOK)) - BOp::count(pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::ROOK)));
	material += Material::Queen * (BOp::count(pieces.getBitboard(yourSide, FIGURE::QUEEN)) - BOp::count(pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::QUEEN)));

	return material;
}

int StaticEvaluation::mobility(Pieces pieces, uint8_t yourSide) {
	int mobility = 0;

	std::array<std::array<Bitboard, 6>, 2> iteration = pieces.getBitboards();
	
	int index = 0;
	int knightMoves = 0;
	int bishopMoves = 0;
	int rookMoves = 0;
	int queenMoves = 0;

	while (iteration[yourSide][FIGURE::KNIGHT]) {
		index = BOp::bsf(iteration[yourSide][FIGURE::KNIGHT]);
		BOp::removeBit(iteration[yourSide][FIGURE::KNIGHT], index);
		knightMoves += BOp::count(Masks::getKnightMask(pieces, index, yourSide));
	}
	while (iteration[yourSide][FIGURE::BISHOP]) {
		index = BOp::bsf(iteration[yourSide][FIGURE::BISHOP]);
		BOp::removeBit(iteration[yourSide][FIGURE::BISHOP], index);
		bishopMoves += BOp::count(Masks::getBishopMask(pieces, index, yourSide));
	}
	while (iteration[yourSide][FIGURE::ROOK]) {
		index = BOp::bsf(iteration[yourSide][FIGURE::ROOK]);
		BOp::removeBit(iteration[yourSide][FIGURE::ROOK], index);
		rookMoves += BOp::count(Masks::getRookMask(pieces, index, yourSide));
	}
	while (iteration[yourSide][FIGURE::QUEEN]) {
		index = BOp::bsf(iteration[yourSide][FIGURE::QUEEN]);
		BOp::removeBit(iteration[yourSide][FIGURE::QUEEN], index);
		queenMoves += BOp::count(Masks::getQueenMask(pieces, index, yourSide));
	}

	while (iteration[Pieces::inverseSide(yourSide)][FIGURE::KNIGHT]) {
		index = BOp::bsf(iteration[Pieces::inverseSide(yourSide)][FIGURE::KNIGHT]);
		BOp::removeBit(iteration[Pieces::inverseSide(yourSide)][FIGURE::KNIGHT], index);
		knightMoves -= BOp::count(Masks::getKnightMask(pieces, index, Pieces::inverseSide(yourSide)));
	}
	while (iteration[Pieces::inverseSide(yourSide)][FIGURE::BISHOP]) {
		index = BOp::bsf(iteration[Pieces::inverseSide(yourSide)][FIGURE::BISHOP]);
		BOp::removeBit(iteration[Pieces::inverseSide(yourSide)][FIGURE::BISHOP], index);
		bishopMoves -= BOp::count(Masks::getBishopMask(pieces, index, Pieces::inverseSide(yourSide)));
	}
	while (iteration[Pieces::inverseSide(yourSide)][FIGURE::ROOK]) {
		index = BOp::bsf(iteration[Pieces::inverseSide(yourSide)][FIGURE::ROOK]);
		BOp::removeBit(iteration[Pieces::inverseSide(yourSide)][FIGURE::ROOK], index);
		rookMoves -= BOp::count(Masks::getRookMask(pieces, index, Pieces::inverseSide(yourSide)));
	}
	while (iteration[Pieces::inverseSide(yourSide)][FIGURE::QUEEN]) {
		index = BOp::bsf(iteration[Pieces::inverseSide(yourSide)][FIGURE::QUEEN]);
		BOp::removeBit(iteration[Pieces::inverseSide(yourSide)][FIGURE::QUEEN], index);
		queenMoves -= BOp::count(Masks::getQueenMask(pieces, index, Pieces::inverseSide(yourSide)));
	}

	mobility += Mobility::Knight * knightMoves;
	mobility += Mobility::Bishop * bishopMoves;
	mobility += Mobility::Rook * rookMoves;
	mobility += Mobility::Queen * queenMoves;

	return mobility;
}

int StaticEvaluation::checkDoublePawn(Pieces pieces, uint8_t yourSide) {
	int doublePawn = 0;

	int yourPawn = 0;
	int opponentPawn = 0;

	for (int i = 0; i < 8; i++) {
		yourPawn = BOp::count(pieces.getBitboard(yourSide, FIGURE::PAWN) & BColumns::COLUMNS[i]);
		opponentPawn = BOp::count(pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::PAWN) & BColumns::COLUMNS[i]);

		doublePawn += std::max(yourPawn - 1, 0);
		doublePawn -= std::max(opponentPawn - 1, 0);
	}
	return DoublePawn * doublePawn;
}

int StaticEvaluation::checkConnectedPawn(Pieces pieces, uint8_t yourSide) {
	int connectedPawn = 0;

	Bitboard yourPawn = Masks::getPawnLeftAttackMask(pieces, yourSide, yourSide) | Masks::getPawnRightAttackMask(pieces, yourSide, yourSide);
	Bitboard opponentPawn = Masks::getPawnLeftAttackMask(pieces, Pieces::inverseSide(yourSide), yourSide) | Masks::getPawnRightAttackMask(pieces, Pieces::inverseSide(yourSide), yourSide);

	connectedPawn += BOp::count(yourPawn & pieces.getBitboard(yourSide, FIGURE::PAWN));
	connectedPawn -= BOp::count(opponentPawn & pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::PAWN));

	return ConnectedPawn * connectedPawn;
}

int StaticEvaluation::checkCrachCastling(bool wSCastling, bool wLCastling, bool bSCastling, bool bLCastling, bool commitedCastligY, bool commitedCastligO, uint8_t yourSide) {
	int crashCastling = 0;

	if (yourSide == SIDE::WHITE) {
		if (!commitedCastligY) {
			if (!wSCastling) crashCastling += CrashCastling;
			if (!wLCastling) crashCastling += CrashCastling;
		}

		if (!commitedCastligO) {
			if (!bSCastling) crashCastling -= CrashCastling;
			if (!bLCastling) crashCastling -= CrashCastling;
		}
	}
	else {
		if (!commitedCastligO) {
			if (!wSCastling) crashCastling -= CrashCastling;
			if (!wLCastling) crashCastling -= CrashCastling;
		}

		if (!commitedCastligY) {
			if (!bSCastling) crashCastling += CrashCastling;
			if (!bLCastling) crashCastling += CrashCastling;
		}
	}

	return crashCastling;
}

int StaticEvaluation::checkPawnEntrance(Pieces pieces, uint8_t yourSide) {
	int pawnEntrance = 0;
	int index = 0;

	Bitboard yourPawn = pieces.getBitboard(yourSide, FIGURE::PAWN);
	Bitboard opponentPawn = pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::PAWN);

	while (yourPawn) {
		index = BOp::bsf(yourPawn);
		BOp::removeBit(yourPawn, index);

		if (EntrancePawn::yourPawnEntrance[index] & pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::PAWN)) pawnEntrance += DefaultPawnEntrance[index / 8];
		else pawnEntrance += PassedPawnEntrance[index/8];
	}

	while (opponentPawn){
		index = BOp::bsf(opponentPawn);
		BOp::removeBit(opponentPawn, index);

		if (EntrancePawn::opponentPawnEntrance[index] & pieces.getBitboard(yourSide, FIGURE::PAWN)) pawnEntrance -= DefaultPawnEntrance[index / 8];
		else pawnEntrance -= PassedPawnEntrance[index / 8];
	}
}

int StaticEvaluation::checkPawnShield(Pieces pieces, bool commitedCastligY, bool commitedCastligO, uint8_t yourSide) {
	int pawnShield = 0;

	if (commitedCastligY) {
		Bitboard yourPawn = pieces.getBitboard(yourSide, FIGURE::PAWN);
		Bitboard yourPawnShield = PawnShield::yourPawnSheild[BOp::bsf(pieces.getBitboard(yourSide, FIGURE::KING))];
		pawnShield += BOp::count(yourPawnShield & yourPawn);
	}

	if (commitedCastligO) {
		Bitboard opponentPawn = pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::PAWN);
		Bitboard opponentPawnShield = PawnShield::opponentPawnSheild[BOp::bsf(pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::KING))];
		pawnShield -= BOp::count(opponentPawnShield & opponentPawn);
	}

	return pawnShield * PawnInShield;
}

int StaticEvaluation::checkTwoBishop(Pieces pieces, uint8_t yourSide) {
	int twoBishop = 0;
	if (BOp::count(pieces.getBitboard(yourSide, FIGURE::BISHOP)) >= 2) twoBishop += TwoBishops;
	if (BOp::count(pieces.getBitboard(Pieces::inverseSide(yourSide), FIGURE::BISHOP)) >= 2) twoBishop -= TwoBishops;

	return twoBishop;
}

int StaticEvaluation::endGame(Pieces pieces, uint8_t yourColor, uint8_t colorAttaking) {
	int endGame = 0;
	if (BOp::count(pieces.getAllFigure()) > MaxFigureInEndGame) return endGame;

	int kingAttakingPos = BOp::bsf(pieces.getBitboard(colorAttaking, FIGURE::KING));

	int kingDefenderPos = BOp::bsf(pieces.getBitboard(Pieces::inverseSide(colorAttaking), FIGURE::KING));

	endGame += DistanceAttakingKing * (abs((kingDefenderPos - kingAttakingPos) / 8));
	endGame += DistanceMidlle * (abs((kingDefenderPos - 35) / 8));

	if (colorAttaking != yourColor) endGame = -endGame;

	return endGame;
}