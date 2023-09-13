// Standard
#include <iostream>
#include <vector>

// Third party
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Generic
#include "Game.hpp"
#include "../board/Board.hpp"
#include "../pieces/Piece.hpp"

//// Constructor and Destructor

Game::Game(const char* title, int height, int width): window(nullptr), renderer(nullptr) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_JPG && IMG_INIT_PNG)) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, SDL_WINDOW_SHOWN);

		if (window == nullptr) {
			std::cout << SDL_GetError();
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer == nullptr) {
			std::cout << SDL_GetError() << std::endl;
		}	
				
	}
	else {
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_RenderSetLogicalSize(renderer, 800, 800);	

}

Game::~Game() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}

// Getters

std::vector<SDL_Rect> Game::getWhitePieces() {
    return this->whitePieces;
}

std::vector<SDL_Rect> Game::getBlackPieces() {
    return this->blackPieces;
}

SDL_Rect Game::getSelectedPiece() {
    return this->selectedPiece;
}

// Setters

void Game::addWhitePiece(SDL_Rect whitePiece) {
    this->whitePieces.push_back(whitePiece);
}

void Game::addBlackPiece(SDL_Rect blackPiece) {
    this->blackPieces.push_back(blackPiece);
}

void Game::setSelectedPiece(SDL_Rect setSelectedPiece) {
    this->selectedPiece = setSelectedPiece;
}

//// Helper functions

std::pair<int, int> Game::boardPositionToPixel(int x, int y) {
    
    return std::make_pair(64+(x*87), 64+(y*87));

}

int Game::closestNumber(int target) {
    
    std::vector<int> numbers = {64, 151, 238, 325, 412, 499, 586, 673};
    
    int closest = numbers[0];

    for (int i=0; i<numbers.size(); i++) {
        if (std::abs(numbers[i]-target) < std::abs(numbers[i]-closest)) {
            closest = numbers[i];
        }
    }

    closest = (closest-64)/87;

    return closest;
}

std::pair<int, int> Game::gamePixelToBoardPosition(int pixelX, int pixelY) {
    
    return std::make_pair(closestNumber(pixelY)-1, closestNumber(pixelX)-1);

}

//// Game methods

SDL_Texture* Game::loadTexture(const char* filePath) {

	SDL_Texture* texture = nullptr;

	texture = IMG_LoadTexture(renderer, filePath);

	return texture;

}

SDL_Rect Game::blit(SDL_Texture* texture, int x, int y) {

	SDL_Rect destination;

	destination.x = x;
	destination.y = y;

	SDL_QueryTexture(texture, nullptr, nullptr, &destination.w, &destination.h);

	SDL_RenderCopy(renderer, texture, nullptr, &destination);
    
    return destination;
}

// Board methods

SDL_Texture* Game::loadPieceTextureFromBoard(Piece piece) {
    
    switch(piece.getType()) {
        case PAWN: {
            if (piece.getColor() == BLACK) {  
                return loadTexture("../assets/BlackPawn.png"); 
            }
            else {
                return loadTexture("../assets/WhitePawn.png");
            }
            break;
        }
        case ROOK: {
            if (piece.getColor() == BLACK) {
                return loadTexture("../assets/BlackRook.png");
            }

            else {
                return loadTexture("../assets/WhiteRook.png");
            }
            break;
        }
        case KNIGHT: {
            if (piece.getColor() == BLACK) {
                 return loadTexture("../assets/BlackKnight.png");              
            }
            else {
                 return loadTexture("../assets/WhiteKnight.png");              
            }
            break;
        }
        case BISHOP: {
            if (piece.getColor() == BLACK) {
                 return loadTexture("../assets/BlackBishop.png");              
            }
            else {
                 return loadTexture("../assets/WhiteBishop.png");              
            }
            break;
        }
        case QUEEN: {
            if (piece.getColor() == BLACK) {
                 return loadTexture("../assets/BlackQueen.png");
            }
            else {
                 return loadTexture("../assets/WhiteQueen.png");
            }
            break;
        }
        case KING: {
            if (piece.getColor() == BLACK) {
                 return loadTexture("../assets/BlackKing.png");
            }
            else {
                 return loadTexture("../assets/WhiteKing.png");
            }
            break;
        }
        default:
            break;
    }

    return nullptr;
}

void Game::initialiseBoard(std::vector< std::vector<Piece> > board) {
  
    SDL_Texture* boardTexture = loadTexture("../assets/ChessBoard.jpg");
 
    prepareBoard();
    blit(boardTexture, 50, 50);
    updateBoard(board);
    presentBoard();

}

void Game::updateBoard(std::vector< std::vector<Piece> > board) {

    SDL_Texture* pieceTexture = nullptr;
    int x = 0; 
    int y = 0;
       
	for (int i=0; i<board.size(); i++) {
		for (int j=0; j<board[0].size(); j++) {
			Piece piece = board[i][j];

            pieceTexture = loadPieceTextureFromBoard(piece);
            
            x = boardPositionToPixel(i, j).second;
            y = boardPositionToPixel(i, j).first;
   		    SDL_Rect pieceRect = blit(pieceTexture, x, y);

            if (piece.getColor() == WHITE) {
                addWhitePiece(pieceRect); 
            }
            else if (piece.getColor() == BLACK) {
                addBlackPiece(pieceRect);
            }
        }
	}
}

void Game::prepareBoard() {
	SDL_SetRenderDrawColor(renderer, 48, 46, 43, 255);
    SDL_RenderClear(renderer);
}

void Game::presentBoard() {
	SDL_RenderPresent(renderer);
}

// Piece methods

void Game::pickupPiece(SDL_Point mousePosition, SDL_Point& clickOffset) {
    
    std::cout << "Entered pickupPiece" << "\n";

    for (auto piece : this->whitePieces) {
        if (SDL_PointInRect(&mousePosition, &piece)) {
            selectedPiece = piece;
            clickOffset.x = mousePosition.x - piece.x;
            clickOffset.y = mousePosition.y - piece.y;   
            break;
        }
    }

}

void Game::dragPiece(SDL_Point mousePosition, SDL_Point clickOffset, const int initialPiecePositionX, const int initialPiecePositionY, std::vector< std::vector<Piece> > board) {
   
    // Gettin
    SDL_Texture* boardTexture = loadTexture("../assets/ChessBoard.jpg"); 
    auto boardPosition = gamePixelToBoardPosition(initialPiecePositionX, initialPiecePositionY);
    int x = boardPosition.first; 
    int y = boardPosition.second;
    
    Piece piece = board[y][x];
    SDL_Texture* pieceTexture = loadPieceTextureFromBoard(piece);
    board[y][x] = Piece(EMPTY, NONE, 0);
    
    selectedPiece.x = mousePosition.x - clickOffset.x;
    selectedPiece.y = mousePosition.y - clickOffset.y;

    SDL_RenderClear(renderer);
    blit(boardTexture, 50, 50);
    updateBoard(board);
    SDL_RenderDrawRect(renderer, &selectedPiece);
    SDL_RenderCopy(renderer, pieceTexture, NULL, &selectedPiece);
    SDL_RenderPresent(renderer);
    
 }

void Game::placePiece(std::vector< std::vector<Piece> > board) {
    
    SDL_Texture* boardTexture = loadTexture("../assets/ChessBoard.jpg"); 

    SDL_RenderClear(renderer);
    blit(boardTexture, 50, 50);
    updateBoard(board);
    SDL_RenderPresent(renderer);

    std::cout << "Entered place piece" << "\n";

    SDL_Rect destination;

    destination.x = 0;
    destination.y = 0;
    destination.w = 0;
    destination.h = 0;

    setSelectedPiece(destination);  

}

void Game::renderSelectedPiece() {

}
