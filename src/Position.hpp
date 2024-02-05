#include "ZobristHashing.hpp"
#include "Move.hpp"

class Position {
	Pieces pieces;
	ZobristHash hash;
	Repetition repetition;
	
	int enPassant;
	bool wLCastling, wSCastling, bLCastling, bSCastling;
	float countMove, countMoveDraw;

	void addPiece(int pos, int figure, uint8_t side);
	void removePiece(int pos, int figure, uint8_t side);

	void changeEnPassant(int enPassant);

public:
	Position();
	Position(const std::string& fen, int enPassant, bool wLCastling, bool wSCastling, bool bLCastling, bool bSCastling, float countMove);

	void move(Move move);

	void removeWLCastling();
	void removeWSCastling();
	void removeBLCastling();
	void removeBSCastling();

	void updateCountMove();
	void updateCountMoveDraw(bool break_event);

	Pieces getPieces() { return pieces; }
};