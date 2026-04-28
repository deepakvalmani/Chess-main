#include "pawn.h"
#include "board.h"
#include <iostream>

Pawn::Pawn(bool white) : Piece(white) {
    // For now, load a placeholder texture. 
    // You'll need "assets/Pawn.png" and "assets/Pawn_Black.png"
    std::string filename = white ? "assets/Pawn.png" : "assets/Pawn_Black.png";
    
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
        sprite->setScale({60.f / tex.getSize().x, 80.f / tex.getSize().y});
    }
}

std::vector<sf::Vector2i> Pawn::getValidMoves(const Board& board, sf::Vector2i currentPos) const {
    std::vector<sf::Vector2i> moves;
    
    // White moves UP (-1 Y), Black moves DOWN (+1 Y)
    int dir = isWhite ? -1 : 1;

    // 1. Move Forward 1 Square
    int nextY = currentPos.y + dir;
    if (nextY >= 0 && nextY < 8 && board.getPieceAt(currentPos.x, nextY) == nullptr) {
        moves.push_back({currentPos.x, nextY});

        // 2. Move Forward 2 Squares (Only if 1st square was empty AND we are on the start row)
        int startRow = isWhite ? 6 : 1;
        if (currentPos.y == startRow) {
            int doubleY = currentPos.y + (dir * 2);
            if (board.getPieceAt(currentPos.x, doubleY) == nullptr) {
                moves.push_back({currentPos.x, doubleY});
            }
        }
    }

    // 3. Capture Diagonally Left
    if (currentPos.x - 1 >= 0 && nextY >= 0 && nextY < 8) {
        Piece* p = board.getPieceAt(currentPos.x - 1, nextY);
        if (p != nullptr && p->getIsWhite() != this->isWhite) {
            moves.push_back({currentPos.x - 1, nextY});
        }
    }

    // 4. Capture Diagonally Right
    if (currentPos.x + 1 < 8 && nextY >= 0 && nextY < 8) {
        Piece* p = board.getPieceAt(currentPos.x + 1, nextY);
        if (p != nullptr && p->getIsWhite() != this->isWhite) {
            moves.push_back({currentPos.x + 1, nextY});
        }
    }

    return moves;
}


void Pawn::draw(sf::RenderWindow& window) { if (sprite) { window.draw(*sprite); } }
