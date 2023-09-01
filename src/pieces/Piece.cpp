#include "Piece.hpp"
#include <utility>

// Constructor

Piece::Piece(Pieces pieceInput, Color colorInput, int valueInput): piece(pieceInput), color(colorInput), value(valueInput){}

// Getters
Pieces Piece::getType() {
    return this->piece;
}

Color Piece::getColor() {
    return this->color;
}

int Piece::getValue() {
    return this->value;
}

// Setters
void Piece::setPiece(Pieces piece_input) {
    this->piece = piece_input;
}

void Piece::setColor(Color color_input) {
    this->color = color_input;
}

void Piece::setValue(int value_input) {
    this->value = value_input;
}


