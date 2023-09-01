#pragma once 

// SDL2 includes
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Personal includes
#include "../pieces/Piece.hpp"

class Game {

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

	public:
		//// Constructor and destructor
		
		Game(const char* title, int height, int width);
		~Game();

		//// Game methods

		SDL_Texture* loadTexture(const char* filePath);
		void blit(SDL_Texture* texture, int x, int y);

		// Board methods
		void loadPieceFromBoard(Piece piece);
		void loadBoard(std::vector< std::vector<Piece> > board);
		void prepareBoard();
		void presentBoard();
};
