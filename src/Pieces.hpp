#include "Bitboard.hpp"
#include <string>
#pragma once

enum FIGURE { PAWN = 0, KNIGHT = 1, BISHOP = 2, ROOK = 3, QUEEN = 4, KING = 5 };

enum SIDE { WHITE = 0, BLACK = 1 };

class Pieces {
    std::array<std::array<Bitboard, 6>, 2> Bitboards{};
    std::array<Bitboard, 2> SideBitboards{};
    std::array<Bitboard, 2> InverseSideBitboards{};
    Bitboard AllFigure;
    Bitboard InverseAllFigure;

public:
    Pieces();
    Pieces(const std::string& fen);
    void updateBitboard();
    static int inverseSide(uint8_t side);

    std::array<std::array<Bitboard, 6>, 2> getBitboards() ;
    Bitboard getBitboard(uint8_t side, int figure);
    Bitboard getSideBitboard(uint8_t side);
    Bitboard getInverseSideBitboard(uint8_t side);
    Bitboard getAllFigure();
    Bitboard getInverseAllFigure();

    void setBitboard(uint8_t side, int figure, Bitboard bb);
};