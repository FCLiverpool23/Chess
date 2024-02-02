#include <bit>
#include <cstdint>
#include <array>
#pragma once

typedef uint64_t Bitboard;

namespace BOp {
    static constexpr std::array<int, 64> BIT_SCAN_TABLE = {
            0, 47,  1, 56, 48, 27,  2, 60,
            57, 49, 41, 37, 28, 16,  3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11,  4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30,  9, 24,
            13, 18,  8, 12,  7,  6,  5, 63
    };

    static constexpr Bitboard addBit(Bitboard bb, int square) {
        bb = bb | (1ull << square);
        return bb;
    }

    static constexpr Bitboard removeBit(Bitboard bb, int square) {
        bb = bb & (~(1ull << square));
        return bb;
    }

    static constexpr bool getBit(Bitboard bb, int square) {
        return (bb & (1ull << square));
    }

    static constexpr int count(Bitboard bb) {
        return std::popcount(bb);
    }

    static constexpr int bsf(Bitboard bb) {
        return BIT_SCAN_TABLE[((bb ^ (bb - 1)) * 0x03f79d71b4cb0a89) >> 58];
    }
    static constexpr int bsr(Bitboard bb) {
        bb = bb | (bb >> 1);
        bb = bb | (bb >> 2);
        bb = bb | (bb >> 4);
        bb = bb | (bb >> 8);
        bb = bb | (bb >> 16);
        bb = bb | (bb >> 32);
        return BIT_SCAN_TABLE[(bb * 0x03f79d71b4cb0a89) >> 58];
    }
}

namespace BRows {
    static consteval std::array<Bitboard, 8> calcRows() {
        std::array<Bitboard, 8> rows{};
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                rows[y] = BOp::addBit(rows[y], y * 8 + x);
            }
        }
        return rows;
    }
    static constexpr std::array<Bitboard, 8> ROWS = calcRows();
    static consteval std::array<Bitboard, 8> calcInvRows() {
        std::array<Bitboard, 8> invRows{};
        for (int i = 0; i < 8; i++) {
            invRows[i] = ~ROWS[i];
        }
        return invRows;
    }
    static constexpr std::array<Bitboard, 8> INV_ROWS = BRows::calcInvRows();
}


namespace BColumns {
    static consteval std::array<Bitboard, 8> calcColumns() {
        std::array<Bitboard, 8> columns{};
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                columns[x] = BOp::addBit(columns[x], y * 8 + x);
            }
        }
        return columns;
    }
    static constexpr std::array<Bitboard, 8> COLUMNS = BColumns::calcColumns();
    static consteval std::array<Bitboard, 8> calcInvColumns() {
        std::array<Bitboard, 8> invColumns{};
        for (int i = 0; i < 8; i++) {
            invColumns[i] = ~COLUMNS[i];
        }
        return invColumns;
    }
    static constexpr std::array<Bitboard, 8> INV_COLUMNS = BColumns::calcInvColumns();
}