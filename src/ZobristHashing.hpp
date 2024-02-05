#include <time.h>
#include <vector>
#include "Pieces.hpp"
#pragma once

namespace ConstantsZobristHashing {
	namespace GPRN {
		static constexpr uint64_t seed = 0x98f107;
		static constexpr uint64_t mul = 0x19660D;
		static constexpr uint64_t sub = 0x3C6EF35F;
		static constexpr uint64_t mod = 0x100000000;

		static consteval uint64_t random(uint64_t number) {
			return (mul * number + sub) % mod;
		}
	}

	static consteval std::array<std::array<std::array<uint64_t, 64>, 6>, 2> CalcRandomConstants() {
		std::array<std::array<std::array<uint64_t, 64>, 6>, 2> constants{};

		uint64_t number = GPRN::seed;

		for (uint8_t side = 0; side < 2; side++) {
			for (int figure = 0; figure < 6; figure++) {
				for (int pos = 0; pos < 64; pos++) {
					number = GPRN::random(number);
					constants[side][figure][pos] = number;
				}
			}
		}

		return constants;
	}

	static constexpr std::array<std::array<std::array<uint64_t, 64>, 6>, 2> Constants = CalcRandomConstants();
	static constexpr uint64_t ConstantInvertSide = GPRN::random(Constants[1][5][63]);
	static constexpr uint64_t ConstantWLCastling = GPRN::random(ConstantInvertSide);
	static constexpr uint64_t ConstantWSCastling = GPRN::random(ConstantWLCastling);
	static constexpr uint64_t ConstantBLCastling = GPRN::random(ConstantWSCastling);
	static constexpr uint64_t ConstantBSCastling = GPRN::random(ConstantBLCastling);
}

class ZobristHash {
	uint64_t value;

public:
	ZobristHash();
	ZobristHash(Pieces pieces, bool wLCastling, bool wSCastling, bool bLCastling, bool bSCastling);
	uint64_t getValue();

	void zobrist(uint8_t side, int figure, int square);
	void zobristSide();
	void zobristWLCastling();
	void zobristWSCastling();
	void zobristBLCastling();
	void zobristBSCastling();

	friend bool operator ==(ZobristHash left, ZobristHash right);
};

class Repetition {
	std::vector<ZobristHash> hashes;

public:
	Repetition() = default;

	void addHash(ZobristHash hash) { hashes.push_back(hash); }

	void clear() { hashes.clear(); }

	uint8_t getRepetitionNumber(ZobristHash hash) const {
		int count = 0;
		for (auto hash1 : hashes) {
			if (hash == hash1) count++;
		}
		return count;
	}
};