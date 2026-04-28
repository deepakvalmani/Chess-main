#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Piece.h"

// A simple package to hold a complete move instructions
struct AIMove {
    sf::Vector2i start;
    sf::Vector2i target;
};

class Board {
private:
    // An 8x8 grid holding pointers to Pieces. 
    // If a square is empty, the pointer is simply null.
    std::unique_ptr<Piece> grid[8][8]; 
    
    // The visual tiles (light and dark squares)
    sf::RectangleShape tiles[8][8];
    const float tileSize = 100.f; // 800x800 window

public:
    //For checking if king can move or not
    bool isInCheck(bool whiteKing) const;
    
    Board();
    void draw(sf::RenderWindow& window);
    
    // Helper function for pieces to "look" at the board
    Piece* getPieceAt(int x, int y) const;
    
    //for moving the piece from one position to another
    void movePiece(sf::Vector2i start, sf::Vector2i target);
    
    //For simulating the move if it causes checkmate
    bool isMoveSafe(sf::Vector2i start, sf::Vector2i target);
    
    //Check if the player has valid moves or the game has ended
    bool hasValidMoves(bool whitePlayer);
    
    void makeRandomAIMove(bool isWhite);

    // Reset the board to initial state
    void reset();
};

