#include <Piece.h>

class Pawn : public Piece {
    public:

    Pawn(Color color_input): Piece(PAWN, color_input, 1) {}

};