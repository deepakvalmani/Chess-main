#include "knight.h"
#include "board.h"
#include <iostream>

Knight::Knight(bool white) : Piece(white)
{
    //load a placeholder texture
    // it is loaded from the following files  assets/Knight.png  and  assets/Knight_Black.png 
    std::string filename = white ? "assets/Knight.png" : "assets/Knight_Black.png";


    static sf::Texture texWhite;
    static sf::Texture texBlack;
    sf::Texture &tex = white ? texWhite : texBlack;
    if (tex.getSize().x == 0)
    { // oad once only
        tex.loadFromFile(filename);
    }
    if (tex.getSize().x > 0)
    {
        sprite.emplace(tex);
        // set scale of the sprite so it fits perfectly in the 100x100 tile
        sprite->setScale({60.f / tex.getSize().x, 85.f / tex.getSize().y});
    }
}

std::vector<sf::Vector2i> Knight::getValidMoves(const Board &board, sf::Vector2i currentPos) const
{
    std::vector<sf::Vector2i> validMoves;

    // 8 possible  moves for a Knight
    int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};

    for (int i = 0; i < 8; ++i)
    {
        int newX = currentPos.x + dx[i];
        int newY = currentPos.y + dy[i];

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
        {

            Piece *targetPiece = board.getPieceAt(newX, newY);

            // If it is empty or have an enemy piece it is a valid step
            if (targetPiece == nullptr || targetPiece->getIsWhite() != this->isWhite)
            {
                
                validMoves.push_back({newX, newY});
            }
        }
    }

    return validMoves;
}

void Knight::draw(sf::RenderWindow &window)
{
    if (sprite)
    {
        window.draw(*sprite);
    }
}
