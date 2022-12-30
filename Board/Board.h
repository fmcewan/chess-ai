#include <vector>
#include <string>
#include <Piece.h>

class Board {

    static int height;
    static int width;
    std::vector<std::vector<Piece>> board;
    Color current_move_color;

    public:

        Board();
        void createBoard(std::string FEN);

};
