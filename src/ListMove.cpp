#include "ListMove.hpp"

ListMove::ListMove() {
	size = 0;
}

Move ListMove::operator[](int index) {
	return moves[index];
}

void ListMove::push(Move move) {
	moves[size] = move;
	size++;
}

int ListMove::getSize() {
	return size;
}