#include "cstdint"
#pragma once

enum Type_Move { DefaultMove = 0, LongMovePawn, EnPassantCapture, ShortCastling, LongCastling, Transformation_Pawn };

class Move {
	int InitialPosition;
	int FinalPosition;

	int TypeFigure;
	uint8_t SideFigure;

	int EatFigure;

	int NewTypeFigure;

	Type_Move TypeMove;

public:
	Move();
	Move(int InitialPosition, int FinalPosition, int TypeFigure, uint8_t SideFigure, int EatFigure, int NewTypeFigure = Move::NONE, Type_Move TypeMove = Type_Move::DefaultMove);

	int GetInitialPosition();
	int GetFinalPosition();
	int GetTypeFigure();
	int GetSideFigure();
	int GetNewTypeFigure();
	int GetEatFigure();
	Type_Move GetTypeMove();

	static constexpr int NONE = 255;
};