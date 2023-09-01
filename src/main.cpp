// Standard includes
#include <iostream>

// Third party includes
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Game function includes
#include "game/Game.hpp"
#include "board/Board.hpp"
#include "pieces/Piece.hpp"


int main(int argc, char *argv[]) {

    // Initialising board

    auto boardObject = std::make_unique<Board>();

    // Game window initialisation

    Game game("Chess", 800, 800);

    // Loading textures

    SDL_Texture* boardTexture = game.loadTexture("../assets/ChessBoard.jpg");
    
    // Game loop

    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
                
        game.prepareBoard();

        game.blit(boardTexture, 50, 50);

        game.presentBoard();
    }

    return 0;
}
