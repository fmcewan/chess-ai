// Standard includes
#include <iostream>

// Third party includes
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Game function includes
#include "game/Game.hpp"
#include "board/Board.hpp"
#include "board/Move.hpp"
#include "pieces/Piece.hpp"


int main(int argc, char *argv[]) {

    // Initialising board

    auto boardObject = std::make_unique<Board>("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");

    // Game window initialisation

    Game game("Chess", 800, 800);

    // Initialise board

    game.initialiseBoard(boardObject->getBoard());

    // Game loop

    bool running = true;
    bool leftMouseButtonDown = false;
    SDL_Point mousePosition;
    SDL_Point clickOffset;
    int initialPiecePositionX;
    int initialPiecePositionY;
    int finalPiecePositionX;
    int finalPiecePositionY;

    while (running) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = false;
                    break;
                }
                case SDL_MOUSEMOTION: {

                    mousePosition = {event.motion.x, event.motion.y};
                   
                    if (leftMouseButtonDown) { 
                        game.dragPiece(mousePosition, clickOffset, initialPiecePositionX, initialPiecePositionY, boardObject->getBoard());
                    }

                    break;
                }                
                case SDL_MOUSEBUTTONUP: {

                    if (leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                        leftMouseButtonDown = false;
                        
                        auto initialPiecePosition = game.gamePixelToBoardPosition(initialPiecePositionX, initialPiecePositionY);
                        auto finalPiecePosition = game.gamePixelToBoardPosition(mousePosition.x, mousePosition.y);

                        Move move = Move(initialPiecePosition.first, initialPiecePosition.second, finalPiecePosition.second, finalPiecePosition.first);
                        bool moveSuccess = boardObject->makeMove(move);
                      
                        if (moveSuccess == true) {
                            Color newPlayer = (boardObject->getCurrentPlayer() == BLACK) ? WHITE : BLACK;
                            boardObject->setCurrentPlayer(newPlayer);
                        }
                        
                        game.placePiece(boardObject->getBoard());
                    }
                    
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    
                    if (!leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                        leftMouseButtonDown = true;
                        game.pickupPiece(mousePosition, clickOffset);

                        initialPiecePositionX = mousePosition.x;
                        initialPiecePositionY = mousePosition.y;
                    }


                    break;
                }
                default:
                    break;
            }

                        
        }
    } 
     
    return 0;
}
