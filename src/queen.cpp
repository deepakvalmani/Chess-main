#include "queen.h"
#include "board.h"
#include <iostream>

Queen::Queen(bool white) : Piece(white) {
    // For now, load a placeholder texture. 
    // You'll need "assets/Queen.png" and "assets/Queen_Black.png"
    std::string filename = white ? "assets/Queen.png" : "assets/Queen_Black.png";
    
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

std::vector<sf::Vector2i> Queen::getValidMoves(const Board& board, sf::Vector2i currentPos) const {
    std::vector<sf::Vector2i> moves;
    
    // 8 Directions: Combine Rook and Bishop directions
    int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};
    int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};

    for (int i = 0; i < 8; ++i) {
        int x = currentPos.x + dx[i];
        int y = currentPos.y + dy[i];

        while (x >= 0 && x < 8 && y >= 0 && y < 8) {
            Piece* p = board.getPieceAt(x, y);
            if (p == nullptr) {
                moves.push_back({x, y});
            } else {
                if (p->getIsWhite() != this->isWhite) {
                    moves.push_back({x, y});
                }
                break;
            }
            x += dx[i];
            y += dy[i];
        }
    }
    return moves;
}
void Queen::draw(sf::RenderWindow& window) { if (sprite) { window.draw(*sprite); } }

