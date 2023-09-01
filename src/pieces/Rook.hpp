#pragma once
#include "Piece.hpp"

enum rookType {
    QUEENSIDE,
    KINGSIDE
};

class Rook : public Piece {

    private:
        bool canCastle;

    public:
        // Constructor
        Rook(Color color_input, bool can_castle_input);

        // Getters
        bool getCanCastle();

        // Setters
        void setCanCastle(bool setCanCastle);
        
};