#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>

#include <Board.h>
#include <../Pieces/Piece.h>
#include <../Pieces/Rook.h>
#include <../Pieces/Pawn.h>
#include <../Pieces/Bishop.h>
#include <../Pieces/Knight.h>
#include <../Pieces/Queen.h>
#include <../Pieces/King.h>


class Board {

    int height;
    int width;
    std::vector<Piece> pieces;
    std::vector<std::vector<Piece>> board;
    Color current_move_color;

    public:

        Board(): height{8}, width{8} {
            
            createBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        }

        void createBoard(std::string FEN);
        void printBoard()
};

// initialiseBoard
// Takes the default FEN string as input and loads beginning 

void Board::createBoard(std::string FEN) {

    std::vector<std::string> FENcomponents;


    while

}

void Board::printBoard() {

    for(auto vector : this->board) {
        for(auto element : vector) {
            std::cout << element << " ";
        }
    }
    std::cout << "\n";
}
