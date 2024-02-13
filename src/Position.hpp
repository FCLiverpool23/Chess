#include "ZobristHashing.hpp"
#include "Move.hpp"

class Position {
	Pieces pieces;
	ZobristHash hash;
	Repetition repetition;

	std::vector<Move> ListAllMove;
	
	int enPassant;
	bool wLCastling, wSCastling, bLCastling, bSCastling;
	float countMove, countMoveDraw;

	uint8_t yourColor;

	void addPiece(int pos, int figure, uint8_t side);
	void removePiece(int pos, int figure, uint8_t side);

	void changeEnPassant(int enPassant);

public:
	Position();
	Position(uint8_t yourColor, int enPassant, bool wLCastling, bool wSCastling, bool bLCastling, bool bSCastling, float countMove);

	void move(Move move);

	void removeWLCastling();
	void removeWSCastling();
	void removeBLCastling();
	void removeBSCastling();

	void updateCountMove();
	void updateCountMoveDraw(bool break_event);

	bool getWLCastling() { return wLCastling; }
	bool getWSCastling() { return wSCastling; }
	bool getBLCastling() { return bLCastling; }
	bool getBSCastling() { return bSCastling; }

	float getCountMove() { return countMove; }
	std::vector<Move> getListAllMove() { return ListAllMove; }
	
	uint8_t getYourColor() { return yourColor; }

	Pieces getPieces() { return this->pieces; }
};