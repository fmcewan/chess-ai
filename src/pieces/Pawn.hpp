#pragma once
#include "Piece.hpp"
#include "../board/Move.hpp"

class Pawn : public Piece {
    
    public:
        // Constructor
        Pawn(Color color_input);
};