#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

// Forward declaration so Piece knows Board exists
class Board; 

class Piece {
protected:
    bool isWhite;          // True for white, false for black
    std::optional<sf::Sprite> sprite; // The visual representation

public:
    // Constructor
    Piece(bool white) : isWhite(white) {}
    
    // Virtual destructor is REQUIRED when using inheritance!
    virtual ~Piece() = default; 

    // --- PURE VIRTUAL FUNCTIONS ---
    // Every child class MUST implement its own version of these
    virtual std::vector<sf::Vector2i> getValidMoves(const Board& board, sf::Vector2i currentPos) const = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    // Getter
    bool getIsWhite() const { return isWhite; }

    void setPosition(int gridX, int gridY) {
        // Multiply by 100 (our tile size) to convert grid coordinates to pixel coordinates
        if (sprite) {
            // Get the actual scaled size of the sprite to center it perfectly
            float width = sprite->getGlobalBounds().size.x;
            float height = sprite->getGlobalBounds().size.y;
            
            float offsetX = (100.f - width) / 2.f;
            float offsetY = (100.f - height) / 2.f;
            
            sprite->setPosition({
                static_cast<float>(gridX * 100) + offsetX, 
                static_cast<float>(gridY * 100) + offsetY
            });
        }
    }
};