#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Piece.h"

// simple struct to hold a complete move instructions
struct AIMove
{
    sf::Vector2i start;
    sf::Vector2i target;
};

class Board
{
private:
    // 8x8 grid for holding pointers to Pieces
    // If a square is empty the pointer is null
    std::unique_ptr<Piece> grid[8][8];

    // tiles light and dark squares
    sf::RectangleShape tiles[8][8];
    const float tileSize = 100.f;

public:
    // function for checking if king can move or not
    bool isInCheck(bool whiteKing) const;

    Board();
    void draw(sf::RenderWindow &window);

    // Helper function to get piece from any point x, y on the baord
    Piece *getPieceAt(int x, int y) const;

    // function for moving piece from start position to target position
    void movePiece(sf::Vector2i start, sf::Vector2i target);

    // function to check and validate the move that is the move safe or not
    bool isMoveSafe(sf::Vector2i start, sf::Vector2i target);

    // function to check if the player has valid moves or the game has ended
    bool hasValidMoves(bool whitePlayer);

    void makeRandomAIMove(bool isWhite);

    // reset the board to initial state
    void reset();
    void setColorAt(int x, int y);
};
