# Usage: Compiling chess AI project 
# make        # compile all binary
# make clean  # remove ALL binaries and objects

all: Chess

Chess: Piece.o Square.o Pawn.o Rook.o Bishop.o Knight.o King.o Queen.o Board.o Move.o Board.o Move.o Game.o main.o
	clang++ -std=c++17 -g -Wall main.o -o Chess Square.o Piece.o Pawn.o Rook.o Bishop.o Knight.o King.o Queen.o Board.o Move.o Game.o -F/Library/Frameworks -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -I/Library/Frameworks/SDL2_image.framework -framework SDL2_image

main.o: Game.o Board.o Square.o Move.o Piece.o Pawn.o Rook.o Knight.o Knight.o King.o Queen.o 
	clang++ -g -Wall -c -std=c++17 main.cpp -F/Library/Frameworks -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -I/Library/Frameworks/SDL2_image.framework/Headers -framework SDL2_image 
Game.o: game/Game.cpp Piece.o Pawn.o Rook.o Knight.o King.o Queen.o Board.o Move.o Square.o
	clang++ -g -Wall -c -std=c++17 game/Game.cpp -F/Library/Frameworks -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -I/Library/Frameworks/SDL2_image.framework/Headers -framework SDL2_image
Board.o: board/Board.cpp Square.o Move.o Piece.o Pawn.o Rook.o Bishop.o Knight.o King.o Queen.o
	clang++ -g -Wall -c -std=c++17 board/Board.cpp
Move.o: board/Move.cpp Square.o
	clang++ -g -Wall -c -std=c++17 board/Move.cpp
Square.o: board/Square.cpp
	clang++ -g -Wall -c -std=c++17 board/Square.cpp
King.o: pieces/King.cpp Piece.o
	clang++ -g -Wall -c -std=c++17 pieces/King.cpp
Queen.o: pieces/Queen.cpp Piece.o
	clang++ -g -Wall -c -std=c++17 pieces/Queen.cpp
Knight.o: pieces/Knight.cpp Piece.o
	clang++ -g -Wall -c -std=c++17 pieces/Knight.cpp
Bishop.o: pieces/Bishop.cpp Piece.o
	clang++ -g -Wall -c -std=c++17 pieces/Bishop.cpp 
Rook.o: pieces/Rook.cpp Piece.o
	clang++ -g -Wall -c -std=c++17 pieces/Rook.cpp
Pawn.o: pieces/Pawn.cpp Piece.o
	clang++ -g -Wall -c -std=c++17 pieces/Pawn.cpp
Piece.o: pieces/Piece.cpp
	clang++ -g -Wall -c -std=c++17 pieces/Piece.cpp 

clean:
	rm *.o Chess
