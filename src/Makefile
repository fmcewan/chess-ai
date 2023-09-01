
Chess: main.o Game.o Board.o Piece.o 
	clang++ main.o -o Chess 
main.o: main.cpp
	clang++ -c -std=c++17 main.cpp -F/Library/Frameworks -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -I/Library/Frameworks/SDL2_image.framework/Headers -framework SDL2_image
Game.o: game/Game.cpp
	clang++ -c game/Game.cpp -F/Library/Frameworks -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -I/Library/Frameworks/SDL2_image.framework/Headers -framework SDL2_image
Board.o: board/Board.cpp
	clang++ -c -std=c++17 board/Board.cpp board/Move.cpp
Piece.o: pieces/Piece.cpp
	clang++ -c pieces/Piece.cpp pieces/Pawn.cpp pieces/Rook.cpp pieces/Bishop.cpp pieces/Knight.cpp pieces/Queen.cpp pieces/King.cpp

clean:
	rm *.o Chess
