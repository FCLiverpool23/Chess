#include "Move.hpp"

Move::Move() = default;

Move::Move(int InitialPosition, int FinalPosition, int TypeFigure, uint8_t SideFigure, int EatFigure, int NewTypeFigure, Type_Move TypeMove) {
	this->InitialPosition = InitialPosition;
	this->FinalPosition = FinalPosition;
	this->TypeFigure = TypeFigure;
	this->SideFigure = SideFigure;
	this->EatFigure = EatFigure;
	this->NewTypeFigure = NewTypeFigure;
	this->TypeMove = TypeMove;
}

int Move::GetInitialPosition() { return InitialPosition; }
int Move::GetFinalPosition() { return FinalPosition; }
int Move::GetTypeFigure() { return TypeFigure; }
int Move::GetSideFigure() { return SideFigure; }
int Move::GetNewTypeFigure() { return NewTypeFigure; }
int Move::GetEatFigure() { return EatFigure; }
Type_Move Move::GetTypeMove() { return TypeMove; }