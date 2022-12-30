#include <Piece.h>

class King : public Piece {
    public:

    King(Color color_input): Piece(KING, color_input, 0) {}

};