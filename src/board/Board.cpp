// Standard library includes
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <algorithm>
#include <set>

// Personal includes
#include "Board.hpp"
#include "Move.hpp"
#include "Square.hpp"
#include "../pieces/Piece.hpp"
#include "../pieces/Rook.hpp"
#include "../pieces/Pawn.hpp"
#include "../pieces/Bishop.hpp"
#include "../pieces/Knight.hpp"
#include "../pieces/King.hpp"
#include "../pieces/Queen.hpp"

// Constructors
Board::Board(): height(8), width(8), board(std::vector<std::vector<Square>>(height, std::vector<Square>(width, Square(Piece(EMPTY, NONE, 0), 0, 0)))) {
    initialiseBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::Board(std::string FEN): height(8), width(8),  board(std::vector<std::vector<Square>>(height, std::vector<Square>(width, Square(Piece(EMPTY, NONE, 0), 0, 0)))) {
    initialiseBoard(FEN);
}

// Getters
int Board::getHeight() {
    return height;
}

int Board::getWidth() {
    return width;
}

int Board::getHalfmoves() {
    return halfmoves;
}

int Board::getFullmoves() {
    return fullmoves;
}

Square Board::getSquare(int x, int y) {
    return board[y][x];
}

Color Board::getCurrentPlayer() {
    return currentPlayer;
}

std::pair<int, int> Board::getEnPassantSquare() {
    return enPassantSquare;
}

std::vector< std::vector<Square> > Board::getBoard() {
    return board;
}

// Setters
void Board::setHeight(int setHeight) {
    height = setHeight;
}

void Board::setWidth(int setWidth) {
    width = setWidth;
}

void Board::setHalfmoves(int setHalfmoves) {
    halfmoves = setHalfmoves; 
} 

void Board::setFullmoves(int setFullmoves) {
    fullmoves = setFullmoves;
}

void Board::setSquare(Piece setPiece, int setX, int setY) {
    Square setSquare = Square(setPiece, setX, setY);
    board[setY][setX] = setSquare;
}

void Board::setCurrentPlayer(Color setCurrentPlayer) {
    currentPlayer = setCurrentPlayer;
}

void Board::setEnPassantSquare(std::pair<int, int> setEnPassantSquare) {
    enPassantSquare = setEnPassantSquare;
}

// Board methods

void Board::initialiseBoard(std::string FEN) {

    // Helper initialisations
    std::map<char, int> charLocationToIntLocation {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7},
    };

    std::vector<char> numbers{'1', '2', '3', '4', '5', '6', '7', '8'};

    /* FEN string processing */

    // Removes slashes for convenience
    FEN.erase(std::remove(FEN.begin(), FEN.end(), '/'), FEN.end());

    // Splits up FEN string into its separate parts
    std::stringstream ss(FEN); 
    std::vector<std::string> FENcomponents;
    std::string s; 
    while (std::getline(ss, s, ' ')) { 
        FENcomponents.push_back(s); 
    }

    /* Board allocation */

    // Allocating pieces to board from main FEN string

    int y=0;
    int x=0;

    for (auto character : FENcomponents[0]) {

        // If character is a number, we skip that many boxes
        if (std::find(numbers.begin(), numbers.end(), character) != numbers.end()) {
           switch (character) {
                case '1':
                    x+=1;
                    break; 
                case '2':
                    x+=2;
                    break;
                case '3':
                    x+=3;
                    break;
                case '4':
                    x+=4;
                    break;
                case '5':
                    x+=5;
                    break;
                case '6':
                    x+=6;
                    break;
                case '7':
                    x+=7;
                    break;
                case '8':
                    x+=8;
                    break;
                default:
                    break;
            } 

            // Increments line if j greater than 7 as a result of switch addition
            if (x>7) {
                y++;
                x-=8;
            } 

        }  
        // Otherwise we add the corresponding piece to that space
        else {

            switch (character) {
                case 'p': {
                    setSquare(Pawn(BLACK), x, y);
                    break;
                }
                case 'P': {
                    setSquare(Pawn(WHITE), x, y);
                    break;
                }
                case 'r': {
                    setSquare(Rook(BLACK, false), x, y);
                    break;
                }
                case 'R': {
                    setSquare(Rook(WHITE, false), x, y);
                    break;
                }
                case 'n': {
                    setSquare(Knight(BLACK), x, y);
                    break;
                }
                case 'N': {
                    setSquare(Knight(WHITE), x, y);
                    break;
                }
                case 'b': {
                    setSquare(Bishop(BLACK), x, y);
                    break;
                }
                case 'B': {
                    setSquare(Bishop(WHITE), x, y);
                    break;
                }
                case 'q': {
                    setSquare(Queen(BLACK), x, y);
                    break;
                }
                case 'Q': {
                    setSquare(Queen(WHITE), x, y);
                    break;
                }
                case 'k': {
                    setSquare(King(BLACK), x, y);
                    break;
                }
                case 'K': {
                    setSquare(King(WHITE), x, y);
                    break;
                }
                default:
                    break;
            }

            // Increments space (or line if new line required)
            if (x<7) {
                x++;
            }
        
            else {
                x=0;
                y++;
            }
        
        } 
    }

    // Starting player

    if (FENcomponents[1] == "w") {
        setCurrentPlayer(WHITE);
    }
    else {
        setCurrentPlayer(BLACK);
    }

    // Castling availability

    if (FENcomponents[2] != "-") {

        Piece piece = board[7][7].getPiece();
        
        if (FENcomponents[2].find("Q") && piece.getType() == ROOK && piece.getColor() == WHITE) {
		    auto rook = static_cast<Rook*>(&piece);
        	rook->setCanCastle(true);
    	}        

        piece = board[7][0].getPiece();

        if (FENcomponents[2].find("Q") && piece.getType() == ROOK && piece.getColor() == WHITE) {
            auto rook = static_cast<Rook*>(&piece);
            rook->setCanCastle(true);
        }

        piece = board[0][7].getPiece();

        if (FENcomponents[2].find("k") && piece.getType() == ROOK && piece.getColor() == BLACK) {
            auto rook = static_cast<Rook*>(&piece);
            rook->setCanCastle(true);
        }  

        piece = board[0][0].getPiece();

         if (FENcomponents[2].find("q") && piece.getType() == ROOK && piece.getColor() == BLACK) {
            auto rook = static_cast<Rook*>(&piece);
            rook->setCanCastle(true);
        }

   }
    
    // En passant location

    if (FENcomponents[3] != "-") {
        std::string enPassantLocation = FENcomponents[3];
        
        int X = charLocationToIntLocation[enPassantLocation[0]];
        int Y = enPassantLocation[1] - '0';

        this->setEnPassantSquare(std::make_pair(X, Y));
    }
    else {
        this->setEnPassantSquare(std::make_pair(-1, -1));
    }

    // Halfmove clock

    const char* halfmoveClock = FENcomponents[4].c_str();

    int setHalfmoves = std::atoi(halfmoveClock);

    this->setHalfmoves(setHalfmoves);

    // Fullmove number

    const char* fullmoveNumber = FENcomponents[5].c_str();

    int setFullmoves = std::atoi(fullmoveNumber);

    this->setFullmoves(setFullmoves);

}


void Board::printBoard() {
 
    for (int i=0; i<this->getHeight(); i++) {
        for (int j=0; j<this->getWidth(); j++) {

            Piece piece = board[i][j].getPiece();

            switch (piece.getType()) {
                case PAWN: {
                    if (piece.getColor() == BLACK) {
                        std::cout << "p";
                    }
                    else {
                        std::cout << "P";
                    }
                    break;
                }

                case ROOK: {
                    if (piece.getColor() == BLACK) {
                        std::cout << "r";
                    }
                    else {
                        std::cout << "R";
                    }
                    break;
                }
                case BISHOP: {
                    if (piece.getColor() == BLACK) {
                        std::cout << "b";
                    }
                    else {
                        std::cout << "B";
                    }
                    break;
                }
                case KNIGHT: {
                    if (piece.getColor() == BLACK) {
                        std::cout << "n";
                    }
                    else {
                        std::cout << "N";
                    }
                    break;
                }
                case KING: {
                    if (piece.getColor() == BLACK) {
                        std::cout << "k";
                    }
                    else {
                        std::cout << "K";
                    }
                    break;
                }
                case QUEEN: {
                    if (piece.getColor() == BLACK) {
                        std::cout << "q";
                    }
                    else {
                        std::cout << "Q";
                    }
                    break;
                }
                case EMPTY:
                    std::cout << "E";
                    break;
                default:
                    break;
            }
        }
        std::cout << std::endl;
    }
}

/* Move methods */

 
bool Board::makeMove(Move move) {

    // Move information
    int initialX = move.getInitialX();
    int initialY = move.getInitialY();
    int finalX = move.getFinalX();
    int finalY = move.getFinalY();
    
    Square initialSquare = board[initialY][initialX];
    Square finalSquare = board[finalY][finalX];
    
    Piece emptyPiece = Piece(EMPTY, NONE, 0);
    Piece initialPiece = initialSquare.getPiece();
    Piece finalPiece = finalSquare.getPiece();

    int direction = (initialPiece.getColor() == BLACK) ? 1 : -1;

    // Getting en Passant square
    int enPassantX = getEnPassantSquare().first;
    int enPassantY = getEnPassantSquare().second;

    std::cout << move.isLegalMove() << "\n";

    // Regular taking
    if (move.isLegalMove() == true) {
         
        std::cout << "in move loop";            
        board[finalY][finalX].setPiece(initialPiece);
        
        if (finalY == enPassantY && finalX == enPassantX) { 
            board[enPassantY-1*direction][enPassantX].setPiece(Piece(EMPTY, NONE, 0));
        }
        else {
            board[initialY][initialX].setPiece(emptyPiece);
        }

        // Setting enPassant
        setEnPassantSquare({move.getEnPassantSquare().x, move.getEnPassantSquare().y});

        // Switching color
        Color newPlayer = (getCurrentPlayer() == BLACK) ? WHITE : BLACK;
        setCurrentPlayer(newPlayer);

        return true;  
        
       
    }
     
    return false;

}
