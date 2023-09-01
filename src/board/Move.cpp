#include "Move.hpp"
#include "../pieces/Piece.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>

// Constructor
Move::Move(int setInitialX, int setInitialY, int setFinalX, int setFinalY): initialX(setInitialX), initialY(setInitialY), finalX(setFinalX), finalY(setFinalY) {}

// Getters
const int Move::getInitialX() {
	return this->initialX;
}

const int Move::getInitialY() {
	return this->initialY;
}

const int Move::getFinalX() {
	return this->finalX;
}

const int Move::getFinalY() {
	return this->finalY;
}
