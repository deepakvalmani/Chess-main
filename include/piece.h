#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

// forward declaration so Piece knows that Board exists
class Board;

class Piece
{
protected:
    bool isWhite; // true means white false means black
    std::optional<sf::Sprite> sprite;

public:
    Piece(bool white) : isWhite(white) {}

    // virtual destructor is required when using inheritance
    virtual ~Piece() = default;

    // pure virtual funcctions every child class must implement its own version of these

    virtual std::vector<sf::Vector2i> getValidMoves(const Board &board, sf::Vector2i currentPos) const = 0;

    virtual void draw(sf::RenderWindow &window) = 0;

    bool getIsWhite() const { return isWhite; }

    void setPosition(int gridX, int gridY)
    {
        // multiply by 100 our tile size to convert grid coordinates to pixel coordinates
        if (sprite)
        {
            // get the actual scaled size of the sprite to put it in center perfectly
            float width = sprite->getGlobalBounds().size.x;
            float height = sprite->getGlobalBounds().size.y;

            float offsetX = (100.f - width) / 2.f;
            float offsetY = (100.f - height) / 2.f;

            sprite->setPosition({static_cast<float>(gridX * 100) + offsetX,
                                 static_cast<float>(gridY * 100) + offsetY});
        }
    }
};