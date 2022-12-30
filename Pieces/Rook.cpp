#include <string>
#include <Piece.h>

class Rook : public Piece {

    bool can_castle;
    int castle_side;

    public:

    Rook(Color color_input, bool can_castle_input, int castle_side_input): Piece(QUEEN, color_input, 5), can_castle{can_castle_input}, castle_side{castle_side_input} {}

};