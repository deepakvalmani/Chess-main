#include "knight.h"
#include "board.h"
#include <iostream>

Knight::Knight(bool white) : Piece(white) {
    // For now, load a placeholder texture. 
    // You'll need "assets/Knight.png" and "assets/Knight_Black.png"
    std::string filename = white ? "assets/Knight.png" : "assets/Knight_Black.png";
    
    // Note: To do this properly, the texture should be stored elsewhere so it 
    // doesn't go out of scope, but we'll keep it simple for this step!
    static sf::Texture texWhite;
    static sf::Texture texBlack;
    sf::Texture& tex = white ? texWhite : texBlack;
    if (tex.getSize().x == 0) { // only load once
        tex.loadFromFile(filename);
    }
    if (tex.getSize().x > 0) {
        sprite.emplace(tex);
        // Scale the sprite so it fits perfectly in the 100x100 tile
        sprite->setScale({60.f / tex.getSize().x, 85.f / tex.getSize().y});
    }
}

std::vector<sf::Vector2i> Knight::getValidMoves(const Board& board, sf::Vector2i currentPos) const {
    std::vector<sf::Vector2i> validMoves;

    // The 8 possible mathematical offsets for a Knight
    int dx[] = { 1,  2, 2, 1, -1, -2, -2, -1};
    int dy[] = {-2, -1, 1, 2,  2,  1, -1, -2};

    for (int i = 0; i < 8; ++i) {
        int newX = currentPos.x + dx[i];
        int newY = currentPos.y + dy[i];

        // RULE 1: Is the destination actually on the 8x8 board?
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            
            // Look at what is currently on that square
            Piece* targetPiece = board.getPieceAt(newX, newY);

            // RULE 2: Is the square empty, OR is it an enemy piece?
            if (targetPiece == nullptr || targetPiece->getIsWhite() != this->isWhite) {
                // SFML 3 syntax for pushing a Vector2i
                validMoves.push_back({newX, newY}); 
            }
        }
    }

    return validMoves;
}

void Knight::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
    }
}
