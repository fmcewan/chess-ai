#pragma once

// Standard library includes
#include <vector>

// SDL2 includes
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Personal includes
#include "../board/Board.hpp"
#include "../pieces/Piece.hpp"

class Game {

	private: 
		SDL_Window* window;
		SDL_Renderer* renderer;
        std::vector<SDL_Rect> whitePieces; 
        std::vector<SDL_Rect> blackPieces;
        SDL_Rect selectedPiece;  

	public:
        //// Constructor and destructor
		Game(const char* title, int height, int width);
		~Game();

        // Getters
        std::vector<SDL_Rect> getWhitePieces();
        std::vector<SDL_Rect> getBlackPieces();
        SDL_Rect getSelectedPiece();

        // Setters
        void addWhitePiece(SDL_Rect whitePiece);
        void addBlackPiece(SDL_Rect blackPiece);
        void setSelectedPiece(SDL_Rect setSelectedPiece);

        //// Helper functions
    
        std::pair<int, int> boardPositionToPixel(int x, int y);
        int closestNumber(int target);
        std::pair<int, int> gamePixelToBoardPosition(int pixelX, int pixelY);

		//// Game methods

		SDL_Texture* loadTexture(const char* filePath);
		SDL_Rect blit(SDL_Texture* texture, int x, int y);
 
		// Board methods
		
        SDL_Texture* loadPieceTextureFromBoard(Piece piece);
        void initialiseBoard(std::vector < std::vector<Piece> > board);
		void updateBoard(std::vector< std::vector<Piece> > board);
		void prepareBoard();
		void presentBoard();

        // Piece methods
    
        void pickupPiece(SDL_Point mousePosition, SDL_Point& clickOffset);
        void dragPiece(SDL_Point mousePosition, SDL_Point clickOffset, const int initialPiecePositionX, const int initialPiecePositionY, std::vector< std::vector<Piece> > board);
        void placePiece(std::vector< std::vector<Piece> > board);
        void renderSelectedPiece();
};
