#include "pawn.h"
#include "board.h"
#include <iostream>

Pawn::Pawn(bool white) : Piece(white)
{
    //load a placeholder texture
    // it is loaded from fllowing files assets/Pawn.png and assets/Pawn_Black.png
    std::string filename = white ? "assets/Pawn.png" : "assets/Pawn_Black.png";

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

std::vector<sf::Vector2i> Pawn::getValidMoves(const Board &board, sf::Vector2i currentPos) const
{
    std::vector<sf::Vector2i> moves;

    // white moves up -1 Y black moves down +1 Y
    int dir = isWhite ? -1 : 1;

    // move forward 1 step
    int nextY = currentPos.y + dir;
    if (nextY >= 0 && nextY < 8 && board.getPieceAt(currentPos.x, nextY) == nullptr)
    {
        moves.push_back({currentPos.x, nextY});

        // move Forward 2 squares only if 1st square was empty and pice is on the start row
        int startRow = isWhite ? 6 : 1;
        if (currentPos.y == startRow)
        {
            int doubleY = currentPos.y + (dir * 2);
            if (board.getPieceAt(currentPos.x, doubleY) == nullptr)
            {
                moves.push_back({currentPos.x, doubleY});
            }
        }
    }

    // capture diagonally left
    if (currentPos.x - 1 >= 0 && nextY >= 0 && nextY < 8)
    {
        Piece *p = board.getPieceAt(currentPos.x - 1, nextY);
        if (p != nullptr && p->getIsWhite() != this->isWhite)
        {
            moves.push_back({currentPos.x - 1, nextY});
        }
    }

     // capture diagonally right
    if (currentPos.x + 1 < 8 && nextY >= 0 && nextY < 8)
    {
        Piece *p = board.getPieceAt(currentPos.x + 1, nextY);
        if (p != nullptr && p->getIsWhite() != this->isWhite)
        {
            moves.push_back({currentPos.x + 1, nextY});
        }
    }

    return moves;
}

void Pawn::draw(sf::RenderWindow &window)
{
    if (sprite)
    {
        window.draw(*sprite);
    }
}
