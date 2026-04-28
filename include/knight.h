#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(bool white);
    
    // The Knight's specific L-shape movement logic
    std::vector<sf::Vector2i> getValidMoves(const Board& board, sf::Vector2i currentPos) const override;
    
    void draw(sf::RenderWindow& window) override;
};