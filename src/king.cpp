#include "king.h"
#include "board.h"
#include <iostream>

King::King(bool white) : Piece(white) {
    // For now, load a placeholder texture. 
    // You'll need "assets/King.png" and "assets/King_Black.png"
    std::string filename = white ? "assets/King.png" : "assets/King_Black.png";
    
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
        sprite->setScale({55.f / tex.getSize().x, 90.f / tex.getSize().y});
    }
}

std::vector<sf::Vector2i> King::getValidMoves(const Board& board, sf::Vector2i currentPos) const {
    std::vector<sf::Vector2i> moves;
    
    // 8 Directions
    int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};
    int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};

    for (int i = 0; i < 8; ++i) {
        int x = currentPos.x + dx[i];
        int y = currentPos.y + dy[i];

        // Ensure the single step is on the board
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            Piece* p = board.getPieceAt(x, y);
            // If it's empty, or holds an enemy, it's a valid step
            if (p == nullptr || p->getIsWhite() != this->isWhite) {
                moves.push_back({x, y});
            }
        }
    }
    return moves;
}

void King::draw(sf::RenderWindow& window) { if (sprite) { window.draw(*sprite); } }
