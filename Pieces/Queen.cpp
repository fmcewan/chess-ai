#include <Piece.h>

class Queen : public Piece {
    public:

    Queen(Color color_input): Piece(QUEEN, color_input, 9) {}

};