#include "ZobristHashing.hpp"

ZobristHash::ZobristHash() = default;

ZobristHash::ZobristHash(Pieces pieces, bool wLCastling, bool wSCastling, bool bLCastling, bool bSCastling) {
    this->value = 0;

    if (wLCastling) zobristWLCastling();
    if (wSCastling) zobristWSCastling();
    if (bLCastling) zobristBLCastling();
    if (bSCastling) zobristBSCastling();

    int side;
    for (int pos = 0; pos < 64; pos++) {
        if (BOp::getBit(pieces.getSideBitboard(SIDE::WHITE), pos)) {
            side = SIDE::WHITE;
        }
        else if (BOp::getBit(pieces.getSideBitboard(SIDE::BLACK), pos)) {
            side = SIDE::BLACK;
        }
        else {
            continue;
        }
        for (int type = 0; type < 6; type++) {
            if (BOp::getBit(pieces.getBitboard(side, type), pos)) {
                zobrist(side, type, pos);
                break;
            }
        }
    }
}

void ZobristHash::zobrist(int side, int figure, int pos) {
    this->value ^= ConstantsZobristHashing::Constants[side][figure][pos];
}

void ZobristHash::zobristSide() {
    value ^= ConstantsZobristHashing::ConstantInvertSide;
}

void ZobristHash::zobristWLCastling() {
    this->value ^= ConstantsZobristHashing::ConstantWLCastling;
}

void ZobristHash::zobristWSCastling() {
    this->value ^= ConstantsZobristHashing::ConstantWSCastling;
}

void ZobristHash::zobristBLCastling() {
    this->value ^= ConstantsZobristHashing::ConstantBLCastling;
}

void ZobristHash::zobristBSCastling() {
    this->value ^= ConstantsZobristHashing::ConstantBSCastling;
}

uint64_t ZobristHash::getValue() {
    return this->value;
}

bool operator ==(ZobristHash left, ZobristHash right) {
    return (left.value == right.value);
}