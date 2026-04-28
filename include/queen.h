#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(bool white);
    std::vector<sf::Vector2i> getValidMoves(const Board& board, sf::Vector2i currentPos) const override;
    void draw(sf::RenderWindow& window) override;
};