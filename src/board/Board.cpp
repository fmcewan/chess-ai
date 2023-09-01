// Standard library includes
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <utility>

// Personal includes
#include "Board.hpp"
#include "Move.hpp"
#include "../pieces/Piece.hpp"
#include "../pieces/Rook.hpp"
#include "../pieces/Pawn.hpp"
#include "../pieces/Bishop.hpp"
#include "../pieces/Knight.hpp"
#include "../pieces/King.hpp"
#include "../pieces/Queen.hpp"



// Constructors
Board::Board(): height(8), width(8), board(this->height, std::vector<Piece>(this->width, Piece(EMPTY, NONE, 0))) {
    createBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq b2 0 1");
}

Board::Board(std::string FEN): height(8), width(8), board(this->height, std::vector<Piece>(this->width, Piece(EMPTY, NONE, 0))) {
    createBoard(FEN);
}

// Getters
int Board::getHeight() {
    return this->height;
}

int Board::getWidth() {
    return this->width;
}

int Board::getHalfmoves() {
    return this->halfmoves;
}

int Board::getFullmoves() {
    return this->fullmoves;
}

std::pair<int, int> Board::getEnPassantSquare() {
    return this->enPassantSquare;
}

Color Board::getCurrentPlayer() {
    return this->currentPlayer;
}

std::vector< std::vector<Piece> > Board::getBoard() {
    return this->board;
} 

// Setters


void Board::setHeight(int setHeight) {
    this->height = setHeight;
}

void Board::setWidth(int setWidth) {
    this->width = setWidth;
}

void Board::setHalfmoves(int setHalfmoves) {
    this->halfmoves = setHalfmoves;
} 

void Board::setFullmoves(int setFullmoves) {
    this->fullmoves = setFullmoves;
}

void Board::setEnPassantSquare(std::pair<int, int> setEnPassantSquare) {
    this->enPassantSquare = setEnPassantSquare;
}

void Board::setCurrentPlayer(Color setCurrentPlayer) {
    this->currentPlayer = setCurrentPlayer;
}

// Board methods
void Board::createBoard(std::string FEN) {

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

    int i=0;
    int j=0;

    for (auto character : FENcomponents[0]) {

        // If character is a number, we skip that many boxes
        if (std::find(numbers.begin(), numbers.end(), character) != numbers.end()) {
           switch (character) {
                case '1':
                    j+=1;
                    break; 
                case '2':
                    j+=2;
                    break;
                case '3':
                    j+=3;
                    break;
                case '4':
                    j+=4;
                    break;
                case '5':
                    j+=5;
                    break;
                case '6':
                    j+=6;
                    break;
                case '7':
                    j+=7;
                    break;
                case '8':
                    j+=8;
                    break;
                default:
                    break;
            } 

            // Increments line if j greater than 7 as a result of switch addition
            if (j>7) {
                i++;
                j-=8;
            } 

        }  
        // Otherwise we add the corresponding piece to that space
        else {
            switch (character) {
                case 'p': {
                    this->board[i][j] = Pawn(BLACK);
                    break;
                }
                case 'P': {
                    this->board[i][j] = Pawn(WHITE);
                    break;
                }
                case 'r': {
                    this->board[i][j] = Rook(BLACK, false);
                    break;
                }
                case 'R': {
                    this->board[i][j] = Rook(WHITE, false);
                    break;
                }
                case 'n': {
                    this->board[i][j] = Knight(BLACK);
                    break;
                }
                case 'N': {
                    this->board[i][j] = Knight(WHITE);
                    break;
                }
                case 'b': {
                    this->board[i][j] = Bishop(BLACK);
                    break;
                }
                case 'B': {
                    this->board[i][j] = Bishop(WHITE);
                    break;
                }
                case 'q': {
                    this->board[i][j] = Queen(BLACK);
                    break;
                }
                case 'Q': {
                    this->board[i][j] = Queen(WHITE);
                    break;
                }
                case 'k': {
                    this->board[i][j] = King(BLACK);
                    break;
                }
                case 'K': {
                    this->board[i][j] = King(WHITE);
                    break;
                }
                default:
                    break;
            }

            // Increments space (or line if new line required)
            if (j<7) {
                j++;
            }
        
            else {
                j=0;
                i++;
            }
        
        } 
    }

    // Starting player

    if (FENcomponents[1] == "w") {
        this->setCurrentPlayer(WHITE);
    }
    else {
        this->setCurrentPlayer(BLACK);
    }

    // Castling availability

    if (FENcomponents[2] != "-") {
        if (FENcomponents[2].find("Q") && (this->board[7][7]).getType() == ROOK && (this->board[7][7]).getColor() == WHITE) {
		auto rook = static_cast<Rook*>(&(this->board[7][7]));
        	rook->setCanCastle(true);
	}        
	else if (FENcomponents[2].find("Q") && (this->board[7][0]).getType() == ROOK && (this->board[7][0]).getColor() == WHITE) {
		auto rook = static_cast<Rook*>(&(this->board[7][0]));
        	rook->setCanCastle(true);
	}
	else if (FENcomponents[2].find("k") && (this->board[0][7]).getType() == ROOK && (this->board[0][7]).getColor() == BLACK) {
		auto rook = static_cast<Rook*>(&(this->board[0][7]));
        	rook->setCanCastle(true);
	}   
	else if (FENcomponents[2].find("q") && (this->board[0][0]).getType() == ROOK && (this->board[0][0]).getColor() == BLACK) {
		auto rook = static_cast<Rook*>(&(this->board[0][0]));
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

            Piece piece = board[i][j];

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
bool Board::isEmptyPath(Move move) {
    
    bool isEmptyPath = true;

    int initialX = move.getInitialX();
    int initialY = move.getInitialY();
    int finalX = move.getFinalX();
    int finalY = move.getFinalY();

    int diagonal = (std::abs(finalX-initialX) == std::abs(finalY-initialY)) ? 0 : 1;

    switch (diagonal) {
        case 0: {

            int directionX = (finalX > initialX) ? 1 : -1;
            int directionY = (finalY > initialY) ? 1 : -1;

            int i=initialX+directionX;
            int j=initialY+directionY;

            while (i != finalX && j != finalY) {
                if (board[j][i].getType() != EMPTY) {
                    isEmptyPath = false;
                    break;
                }
                i += 1*directionX;
                j += 1*directionY;
            }

            break;
        }
        case 1: {
 
            if (finalY == initialY) {
                for (int i=initialX+1; i<=finalX; i++) {
                    if (board[finalY][i].getType() != EMPTY) {
                        std::cout << "Piece not empty: " << i << " " << finalY << "." << "\n";
                        isEmptyPath = false;
                    }
                }   
            }

            else {
                for (int i=initialY+1; i<=finalY; i++) {
                    if (board[i][finalX].getType() != EMPTY) {
                        std::cout << "Piece not empty: " << finalX << " " << i << "." << "\n";
                        isEmptyPath = false;
                    } 
                }
            }

            break;
        }
        default:
            break;
    }

    return isEmptyPath;    
}

bool Board::isLegalMove(Move move) {

    bool isLegalMove = false;

    int initialX = move.getInitialX();
    int initialY = move.getInitialY();
    int finalX = move.getFinalX();
    int finalY = move.getFinalY();

    Piece piece = board[initialY][initialX];

    int direction = (piece.getColor() == BLACK) ? 1 : -1;

    switch (piece.getType()) {

        case PAWN: {

            // A pawn can only move 1 square forward or 2 moves forward, if it agrees to be able to be taken a space behind (en passant)
            if (finalX == initialX && finalY == initialY+direction) {
                isLegalMove = true;
            }  
            else if (finalX == initialX && finalY == initialY+2*direction && ((initialY == 1 && direction == 1) || (initialY == 6 && direction == -1))) {
                isLegalMove = true;
                this->setEnPassantSquare(std::make_pair(finalX, finalY-1*direction));
            }

            break;
        }
        case ROOK: {    
        
            // Rooks can move up to 7 squares in one direction if their path is clear
            if (finalX == initialX && isEmptyPath(move) == true) {
                isLegalMove = true;
            } 
            else if (finalY == initialY && isEmptyPath(move) == true) {
                isLegalMove = true;
            }
            
            // TODO: Implement castling
        
            break;
        }                       
        case BISHOP: {

            // Bishops can move diagonally with any length of stride
            if (std::abs(finalX-initialX) == std::abs(finalY-initialY) && isEmptyPath(move) == true) {
                isLegalMove = true;
            }  

            break;
        }
        case KNIGHT: {

            // Kings can move in an L shape from its current position, 
            // including over pieces so the path does not have to be empty
            if (finalX == initialX+2 && finalY == initialY+1) {
                isLegalMove = true;
            }
            else if (finalX == initialX+1 && finalY == initialY+2) {
                isLegalMove = true;
            }
            else if (finalX == initialX+2 && finalY == initialY-1) {
                isLegalMove = true;
            }
            else if (finalX == initialX+1 && finalY == initialY-2) {
                isLegalMove = true;
            }
            else if (finalX == initialX-1 && finalY == initialY+2) {
                isLegalMove = true;
            }
            else if (finalX == initialX-2 && finalY == initialY+1) {
                isLegalMove = true;
            }
            else if (finalX == initialX-2 && finalY == initialY-1) {
                isLegalMove = true;
            }
            else if (finalX == initialX-1 && finalY == initialY-2) {
                isLegalMove = true;
            }
        
            break;
        }
        case QUEEN: {

            std::cout << "Enters queen" << "\n";

            // Queens can move in any possible direction with any length of stride as long as it is clear
            if (finalX == initialX && isEmptyPath(move) == true) {
                isLegalMove = true;
            } 
            else if (finalY == initialY && isEmptyPath(move) == true) {
                isLegalMove = true;
            }
            else if (std::abs(finalX-initialX) == std::abs(finalY-initialY) && isEmptyPath(move) == true) {
                isLegalMove = true;
            }  

            break;
        }
        case KING: {

            std::cout << "Enters king" << "\n";
            
            // Kings can move one square at a time in any direction
            
            if (finalX == initialX+1 && finalY == initialY+1) {
                isLegalMove = true;
            }
            else if (finalX == initialX+1 && finalY == initialY) {
                isLegalMove = true;
            }
            else if (finalX == initialX+1 && finalY == initialY-1) {
                isLegalMove = true;
            }
            else if (finalX == initialX && finalY == initialY-1) {
                isLegalMove = true;
            }
            else if (finalX == initialX && finalY == initialY+1) {
                isLegalMove = true;
            }
            else if (finalX == initialX-1 && finalY == initialY+1) {
                isLegalMove = true;
            }
            else if (finalX == initialX-1 && finalY == initialY) {
                isLegalMove = true;
            }
            else if (finalX == initialX-1 && finalY == initialY-1) {
                isLegalMove = true;
            }

            // TODO: Implement checking
            
            break;
        }

        default:
            std::cout << "Enters default";
            break;
    }

    return isLegalMove;

}

bool isLegalTake(Move move) {
    return true;
}

bool Board::makeMove(Move move) {

    int initialX = move.getInitialX();
    int initialY = move.getInitialY();
    int finalX = move.getFinalX();
    int finalY = move.getFinalY();

    // TODO: Implement taking and checking

    // Going to be done in isLegalMove() as only pawn is really affected by a different taking and we'll just generate a list of legal moves and if any of them involve the king then it is in check and we have to wait until it is out of check

    if (isLegalMove(move) == true) {

        board[finalY][finalX] = board[initialY][initialX];
        board[initialY][initialX] = Piece(EMPTY, NONE, 0);
        return true;  

    }
    
    else {
        
        return false;

    }

    return false;

}
