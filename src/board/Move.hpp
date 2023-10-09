#pragma once
#include "Square.hpp"
#include "../pieces/Piece.hpp"
#include <vector>


class Move {

	private:
        std::vector< std::vector<Square> > board;
        Color currentPlayer;
        Location enPassantSquare;

		int initialX;
		int initialY;
		int finalX;
		int finalY;

	public:
		// Constructor
		Move(std::vector< std::vector<Square> > board, Color currentPlayer, int setInitialX, int setInitialY, int setFinalX, int setFinalY);

		// Getters
		const int getInitialX();
		const int getInitialY();
		const int getFinalX();
		const int getFinalY();
        Location getEnPassantSquare();    

        // Move legality

        bool isLegalMove();
        
        bool isEmptyPath();
        
        bool isLegalMovePawn();
        bool isLegalMoveKnight();
        bool isLegalMoveRook();
        bool isLegalMoveBishop();
        bool isLegalMoveQueen();
        bool isLegalMoveKing();

        bool isInCheck();
        bool isInCheckmate();
};
