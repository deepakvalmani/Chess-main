#include "rook.h"
#include "board.h"
#include <iostream>

Rook::Rook(bool white) : Piece(white)
{
    // load a placeholder texture
    //  it is loaded from the following files assets/Rook.png and   assets/Rook_Black.png
    std::string filename = white ? "assets/Rook.png" : "assets/Rook_Black.png";

    static sf::Texture texWhite;
    static sf::Texture texBlack;
    sf::Texture &tex = white ? texWhite : texBlack;
    if (tex.getSize().x == 0)
    { // load once only
        tex.loadFromFile(filename);
    }
    if (tex.getSize().x > 0)
    {
        sprite.emplace(tex);
        // set scale of the sprite so it fits perfectly in the 100x100 tile
        sprite->setScale({60.f / tex.getSize().x, 80.f / tex.getSize().y});
    }
}

std::vector<sf::Vector2i> Rook::getValidMoves(const Board &board, sf::Vector2i currentPos) const
{
    std::vector<sf::Vector2i> moves;

    // 4 directions: up down left right
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; ++i)
    {
        int x = currentPos.x + dx[i];
        int y = currentPos.y + dy[i];

        while (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            Piece *p = board.getPieceAt(x, y);
            if (p == nullptr)
            {
                moves.push_back({x, y});
            }
            else
            {
                if (p->getIsWhite() != this->isWhite)
                {
                    moves.push_back({x, y}); // enemy piece can capture but must stop
                }
                break; // Hit a piece friend or foe stop sliding in this direction
            }
            x += dx[i];
            y += dy[i];
        }
    }
    return moves;
}
void Rook::draw(sf::RenderWindow &window)
{
    if (sprite)
    {
        window.draw(*sprite);
    }
}
