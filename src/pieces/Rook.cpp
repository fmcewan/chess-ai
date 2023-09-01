#include "Rook.hpp"

// Constructor
Rook::Rook(Color color_input, bool can_castle_input): Piece(ROOK, color_input, 5), canCastle(can_castle_input) {}

// Getters
bool Rook::getCanCastle() {
	return this->canCastle;
}

// Setters
void Rook::setCanCastle(bool setCanCastle) {
	this->canCastle = setCanCastle;
}