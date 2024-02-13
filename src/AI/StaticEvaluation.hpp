#include "../Masks.hpp"
#pragma once

class StaticEvaluation {

	int material(Pieces pieces, uint8_t yourSide);
	int mobility(Pieces pieces, uint8_t yourSide);
	int checkDoublePawn(Pieces pieces, uint8_t yourSide);
	int checkConnectedPawn(Pieces pieces, uint8_t yourSide);
	int checkCrachCastling(bool wSCastling, bool wLCastling, bool bSCastling, bool bLCastling, bool commitedCastligY, bool commitedCastligO, uint8_t yourSide);
	int checkPawnEntrance(Pieces pieces, uint8_t yourSide);
	int checkPawnShield(Pieces pieces, bool commitedCastligY, bool commitedCastligO, uint8_t yourSide);
	int checkTwoBishop(Pieces pieces, uint8_t yourSide);
	int endGame(Pieces pieces, uint8_t yourSide, uint8_t colorAttaking);

	struct Material{
		static constexpr int Pawn = 100;
		static constexpr int Knight = 305;
		static constexpr int Bishop = 333;
		static constexpr int Rook = 563;
		static constexpr int Queen = 950;
	};

	struct Mobility {
		static constexpr int Knight = 9;
		static constexpr int Bishop = 4;
		static constexpr int Rook = 3;
		static constexpr int Queen = 3;
	};

	static constexpr int DoublePawn = -25;
	static constexpr int CrashCastling = -50;

	static constexpr int ConnectedPawn = 15;
	static constexpr int PawnInShield= 30;
	static constexpr int TwoBishops = 50;

	static constexpr std::array<int, 8> DefaultPawnEntrance = { 0, 0, 0, 0, 10, 20, 30, 0 };
	static constexpr std::array<int, 8> PassedPawnEntrance = { 0, 50, 50, 50, 70, 90, 110, 0 };

	static constexpr int DistanceMidlle = 10;
	static constexpr int DistanceAttakingKing = 10;

	static constexpr int MaxFigureInEndGame = 8;

public:
	int evaluation(Pieces pieces, uint8_t yourSide, bool wSCastling, bool wLCastling, bool bSCastling, bool bLCastling, bool commitedCastligY, bool commitedCastligO);
};