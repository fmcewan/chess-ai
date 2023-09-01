#pragma once

// Standard library includes
#include <vector>
#include <string>
#include <utility>
    
// Header includes
#include "../pieces/Piece.hpp"
#include "Move.hpp"

class Board {

    private:
        // Piece statistics
        std::vector<Piece> blackPiecesOut;
        std::vector<Piece> whitePiecesOut;
        int totalPoints;

        // Board statistics
        int halfmoves;
        int fullmoves;
        int height;
        int width;
        std::pair<int, int> enPassantSquare;
        Color currentPlayer;
        std::vector< std::vector<Piece> > board;

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
        std::pair<int, int> getEnPassantSquare();
        Color getCurrentPlayer();
        std::vector< std::vector<Piece> > getBoard();

        // Setters
        void setHeight(int setHeight);
        void setWidth(int setWidth);
        void setHalfmoves(int setHalfmoves);
        void setFullmoves(int setFullmoves);
        void setEnPassantSquare(std::pair<int, int> setEnPassantSquare);
        void setCurrentPlayer(Color setCurrentPlayer);
        
        // Board methods   
        void createBoard(std::string FEN);
        void printBoard();

        // Move methods
        bool isEmptyPath(Move move);
        bool isLegalTake(Move move);
        bool isLegalMove(Move move);
        bool  makeMove(Move move);

};
