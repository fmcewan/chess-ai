// Standard
#include <iostream>
#include <vector>

// Third party
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Generic
#include "Game.hpp"
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

//// Game methods

SDL_Texture* Game::loadTexture(const char* filePath) {

	SDL_Texture* texture = nullptr;

	texture = IMG_LoadTexture(renderer, filePath);

	return texture;

}

void Game::blit(SDL_Texture* texture, int x, int y) {

	SDL_Rect destination;

	destination.x = x;
	destination.y = y;

	SDL_QueryTexture(texture, nullptr, nullptr, &destination.w, &destination.h);

	SDL_RenderCopy(renderer, texture, nullptr, &destination);

}

// Board methods

void Game::loadPieceFromBoard(Piece piece) {


}

void Game::loadBoard(std::vector< std::vector<Piece> > board) {

	for (int i=0; i<board.size(); i++) {
		for (int j=0; j<board[0].size(); j++) {
			loadPieceFromBoard(board[i][j]);
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

