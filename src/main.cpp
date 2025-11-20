// Standard includes
#include <iostream>
#include <memory>

// Third party includes
#include <SDL2/SDL.h>
#include <SDL_image.h>

// Game function includes
#include "game/Game.hpp"
#include "board/Board.hpp"
#include "board/Move.hpp"
#include "pieces/Piece.hpp"


int main(int argc, char *argv[]) {

    // Initialising board

    auto boardObject = std::make_unique<Board>("rnb1kbnr/ppp1pppp/8/3p4/3PPq2/7N/PPP2PPP/RNBQKB1R w KQkq - 0 1");

    // Game window initialisation

    Game game("Chess", 1000, 1000);

    // Initialise board

    game.initialiseBoard(boardObject->getBoard());

    // Game loop

    bool running = true;
    bool leftMouseButtonDown = false;
    SDL_Point mousePosition;
    SDL_Point clickOffset;
    int initialPiecePositionX;
    int initialPiecePositionY;

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
                        
                        auto initialPiecePositionBoard = game.gamePixelToBoardPosition(initialPiecePositionX, initialPiecePositionY);
                        auto finalPiecePositionBoard = game.gamePixelToBoardPosition(mousePosition.x, mousePosition.y);
                        
                        Move move = Move(boardObject->getBoard(), boardObject->getCurrentPlayer(), initialPiecePositionBoard.first, initialPiecePositionBoard.second, finalPiecePositionBoard.first, finalPiecePositionBoard.second); 
                        boardObject->makeMove(move);
                      
                        game.placePiece(boardObject->getBoard());
                    }
                    
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    
                    if (!leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                        leftMouseButtonDown = true;
                        game.pickupPiece(mousePosition, clickOffset, boardObject->getCurrentPlayer());

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
