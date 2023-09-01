#pragma once
#include <utility>

enum Pieces {PAWN, ROOK, BISHOP, KNIGHT, QUEEN, KING, EMPTY};
enum Color {WHITE, BLACK, NONE};

class Piece {

    private:
        Pieces piece;
        Color color;
        int value;

    public:
        // Constructor
        Piece(Pieces piece_type, Color color_input, int value_input);

        // Getters
        Pieces getType();
        Color getColor();
        int getValue();

        // Setters
        void setPiece(Pieces piece_input);
        void setColor(Color color_input);
        void setValue(int value_input);


};
