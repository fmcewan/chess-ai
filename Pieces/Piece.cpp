enum Pieces {PAWN, ROOK, BISHOP, KNIGHT, QUEEN, KING, EMPTY};
enum Color  {white, black};

class Piece {

    Pieces piece;
    Color color;
    int value;

    public:

    Piece(Pieces piece_type, Color color_input, int value_input): piece{piece_type}, color{color_input}, value{value_input} {}

};