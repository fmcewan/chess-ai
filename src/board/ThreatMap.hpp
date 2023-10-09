// Header includes
#include "Square.hpp"
#include "Move.hpp"

class ThreatMap {
    
    private:

        std::vector< std::vector<Square> > board;
        std::vector<Location> threatMap; 
        Color color;

    public:
        
        // Constructors
        ThreatMap(std::vector< std::vector<Square> > board, Color color);
        ThreatMap(std::vector< std::vector<Square> > board, std::vector<Location> setThreatMap, Color color);

        // Getters
        std::vector<Location> getThreatMap();
        
        // Setters
        void setThreatMap(std::vector<Location> setThreatMap);

        // Possible moves for pieces
            
        std::vector<Move> possibleMovesPawn(int x, int y);
        std::vector<Move> possibleMovesRook(int x, int y);
        std::vector<Move> possibleMovesBishop(int x, int y);
        std::vector<Move> possibleMovesKnight(int x, int y);
        std::vector<Move> possibleMovesQueen(int x, int y);
        std::vector<Move> possibleMovesKing(int x, int y);

        // ThreatMap methods
        std::vector<Move> getPossibleMoves();
        std::vector<Location> buildThreatMap(std::vector<Move> possibleMoves);

};


