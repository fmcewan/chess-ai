#include <string>
#include <Piece.h>

class Rook : public Piece {

    bool can_castle;
    std::string castle_side;

    public:

    Rook(Color color_input, bool can_castle_input, int castle_side_input);

};