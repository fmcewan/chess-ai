#pragma once
#include "../pieces/Piece.hpp"
#include <vector>


class Move {

	private:
		int initialX;
		int initialY;
		int finalX;
		int finalY;

	public:
		// Constructor
		Move(int setInitialX, int setInitialY, int setFinalX, int setFinalY);

		// Getters
		const int getInitialX();
		const int getInitialY();
		const int getFinalX();
		const int getFinalY();
		
};
