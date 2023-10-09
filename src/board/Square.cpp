#include "Square.hpp"

// Constructor

Square::Square(Piece setPiece, int setLocationX, int setLocationY): piece(setPiece) {
    
    location.x = setLocationX;
    location.y = setLocationY;

}

// Getters

Piece Square::getPiece() {
    return piece;
}

int Square::getLocationX() {
    return location.x;
}

int Square::getLocationY() {
    return location.y;
}

Location Square::getLocation() {
    return location; 
}

// Setters

void Square::setPiece(Piece setPiece) {
    piece = setPiece;
}

void Square::setLocationX(int setLocationX) {
    location.x = setLocationX;
}

void Square::setLocationY(int setLocationY) {
    location.y = setLocationY;
}

void Square::setLocation(int setLocationX, int setLocationY) {
    location.x = setLocationX;
    location.y = setLocationY;
}
