#include "Move.hpp"
#include <array>

class ListMove {
	std::array<Move, 300> moves{};
	int size;

public:
	ListMove();

	Move operator[](int index);

	void push(Move move);
	int getSize();
};