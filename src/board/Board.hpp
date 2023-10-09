#pragma once

// Standard library includes
#include <vector>
#include <string>
#include <utility>
    
// Header includes
#include "Square.hpp"
#include "Move.hpp"
#include "../pieces/Piece.hpp"


class Board {

    private:
        // Board statistics
        int totalPoints;
        int halfmoves;
        int fullmoves;
        int height;
        int width;
        Color currentPlayer;
        std::pair<int, int> enPassantSquare;
        std::vector< std::vector<Square>> board;

    public:
        // Constructors
        Board();
        Board(std::string FEN);

        // Getters
        int getHeight();
        int getWidth();
        int getHalfmoves();
        int getFullmoves();
        int getTotalPoints();
        Square getSquare(int x, int y);
        Color getCurrentPlayer();
        std::pair<int, int> getEnPassantSquare();
        std::vector< std::vector<Square> > getBoard();

        // Setters
        void setHeight(int setHeight);
        void setWidth(int setWidth);
        void setHalfmoves(int setHalfmoves);
        void setFullmoves(int setFullmoves);
        void setSquare(Piece setPiece, int x, int y);
        void setCurrentPlayer(Color setCurrentPlayer);
        void setEnPassantSquare(std::pair<int, int> setEnPassantSquare);

        // Board methods   
        void initialiseBoard(std::string FEN);
        void printBoard();
        
        // Move methods
        bool makeMove(Move move);

};
