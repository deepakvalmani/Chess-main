#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "board.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include <exception>

Board::Board()
{
    // standard chess board colors:
    // light squares: cream color RGB: 238, 238, 210
    // dark squares: dark brown RGB: 118, 150, 86

    sf::Color lightColor(238, 238, 210); // Classic chess board light
    sf::Color darkColor(118, 150, 86);   // Classic chess board dark

    // loop through the 8x8 grid to set up the visual tiles
    for (int file = 0; file < 8; ++file)
    { 
        for (int rank = 0; rank < 8; ++rank)
        { 

            tiles[file][rank].setSize({tileSize, tileSize});
            tiles[file][rank].setPosition({file * tileSize, rank * tileSize});

            // standard chess logic for alternating colors
            if ((file + rank) % 2 == 0)
            {
                tiles[file][rank].setFillColor(lightColor); // light square
            }
            else
            {
                tiles[file][rank].setFillColor(darkColor); // dark square
            }
            // Remove texture reference use solid colors
            tiles[file][rank].setTexture(nullptr);
        }
    }

// board setup
    for (int i = 0; i < 8; ++i)
    {
        grid[i][1] = std::make_unique<Pawn>(false); // Black pawns
        grid[i][1]->setPosition(i, 1);
        grid[i][6] = std::make_unique<Pawn>(true); // White pawns
        grid[i][6]->setPosition(i, 6);
    }

    // Black pieces
    grid[0][0] = std::make_unique<Rook>(false);
    grid[7][0] = std::make_unique<Rook>(false);
    grid[1][0] = std::make_unique<Knight>(false);
    grid[6][0] = std::make_unique<Knight>(false);
    grid[2][0] = std::make_unique<Bishop>(false);
    grid[5][0] = std::make_unique<Bishop>(false);
    grid[3][0] = std::make_unique<Queen>(false);
    grid[4][0] = std::make_unique<King>(false);

    for (int i = 0; i < 8; ++i)
        if (grid[i][0])
            grid[i][0]->setPosition(i, 0);

    // White pieces
    grid[0][7] = std::make_unique<Rook>(true);
    grid[7][7] = std::make_unique<Rook>(true);
    grid[1][7] = std::make_unique<Knight>(true);
    grid[6][7] = std::make_unique<Knight>(true);
    grid[2][7] = std::make_unique<Bishop>(true);
    grid[5][7] = std::make_unique<Bishop>(true);
    grid[3][7] = std::make_unique<Queen>(true);
    grid[4][7] = std::make_unique<King>(true);

    for (int i = 0; i < 8; ++i)
        if (grid[i][7])
            grid[i][7]->setPosition(i, 7);
}

void Board::reset()
{
  
    sf::Color lightColor(238, 238, 210);
    sf::Color darkColor(118, 150, 86);

    // clear the grid
    for (int file = 0; file < 8; ++file)
    {
        for (int rank = 0; rank < 8; ++rank)
        {
            grid[file][rank].reset();
            // Reset tile colors as well 
            if ((file + rank) % 2 == 0)
            {
                tiles[file][rank].setFillColor(lightColor);
            }
            else
            {
                tiles[file][rank].setFillColor(darkColor);
            }
            tiles[file][rank].setTexture(nullptr);
        }
    }

    // again setup the complete board same as constructor
    for (int i = 0; i < 8; ++i)
    {
        grid[i][1] = std::make_unique<Pawn>(false);
        grid[i][1]->setPosition(i, 1);
        grid[i][6] = std::make_unique<Pawn>(true);
        grid[i][6]->setPosition(i, 6);
    }

    grid[0][0] = std::make_unique<Rook>(false);
    grid[7][0] = std::make_unique<Rook>(false);
    grid[1][0] = std::make_unique<Knight>(false);
    grid[6][0] = std::make_unique<Knight>(false);
    grid[2][0] = std::make_unique<Bishop>(false);
    grid[5][0] = std::make_unique<Bishop>(false);
    grid[3][0] = std::make_unique<Queen>(false);
    grid[4][0] = std::make_unique<King>(false);

    for (int i = 0; i < 8; ++i)
        if (grid[i][0])
            grid[i][0]->setPosition(i, 0);

    grid[0][7] = std::make_unique<Rook>(true);
    grid[7][7] = std::make_unique<Rook>(true);
    grid[1][7] = std::make_unique<Knight>(true);
    grid[6][7] = std::make_unique<Knight>(true);
    grid[2][7] = std::make_unique<Bishop>(true);
    grid[5][7] = std::make_unique<Bishop>(true);
    grid[3][7] = std::make_unique<Queen>(true);
    grid[4][7] = std::make_unique<King>(true);

    for (int i = 0; i < 8; ++i)
        if (grid[i][7])
            grid[i][7]->setPosition(i, 7);
}

void Board::draw(sf::RenderWindow &window)
{
    // draw all the squares first
    for (int file = 0; file < 8; ++file)
    {
        for (int rank = 0; rank < 8; ++rank)
        {
            window.draw(tiles[file][rank]);
        }
    }

    // draw all the pieces on top
    for (int file = 0; file < 8; ++file)
    {
        for (int rank = 0; rank < 8; ++rank)
        {
            if (grid[file][rank] != nullptr)
            {
                grid[file][rank]->draw(window);
            }
        }
    }
}

Piece *Board::getPieceAt(int x, int y) const
{
    // Make sure not to check outside the board
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        return grid[x][y].get();
    }
    return nullptr;
}

void Board::movePiece(sf::Vector2i start, sf::Vector2i target)
{
    // move the memory pointer to the new square
    // std::move transfers ownership so  the old square automatically becomes nullptr
    // if an enemy piece was already at the target it gets destroyed automatically.
    grid[target.x][target.y] = std::move(grid[start.x][start.y]);

    // tell the piece to update its visual sprite position to match the new square
    if (grid[target.x][target.y] != nullptr)
    {
        grid[target.x][target.y]->setPosition(target.x, target.y);
    }
    //pawn promotion logic
    // dynamic_cast safely checks is this piece pointer actually pointing to a pawn?
    // if it is not a pawn then pawnPtr will automaticaly be nullptr
    Pawn *pawnPtr = dynamic_cast<Pawn *>(grid[target.x][target.y].get());

    if (pawnPtr != nullptr)
    {
        bool isWhite = pawnPtr->getIsWhite();

        // check if pawn reached the final row 0 for white moving up 7 for black moving down)
        if ((isWhite && target.y == 0) || (!isWhite && target.y == 7))
        {
            // Overwrite the Pawn with a queen
            // old awn is automatically deleted from memory by unique_ptr
            grid[target.x][target.y] = std::make_unique<Queen>(isWhite);

            // now update new Queen's visual position
            grid[target.x][target.y]->setPosition(target.x, target.y);
        }
    }
}

bool Board::isInCheck(bool whiteKing) const
{
    sf::Vector2i kingPos = {-1, -1};

    // fisrt find king
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            Piece *p = getPieceAt(x, y);

            // check that is there any piece here and is it the color we are checking?
            if (p != nullptr && p->getIsWhite() == whiteKing)
            {
                //is this specific piece the King?
                if (dynamic_cast<King *>(p) != nullptr)
                {
                    kingPos = {x, y};
                    break; // if found the king then stop searching 
                }
            }
        }
    }

    //  check in case the King was somehow deleted would not happen but better to check

    if (kingPos.x == -1)
        return false;

    // 
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            Piece *p = getPieceAt(x, y);

            // check if this piece is enemy or not
            if (p != nullptr && p->getIsWhite() != whiteKing)
            {

                // get all the squares this enemy can attack
                std::vector<sf::Vector2i> enemyMoves = p->getValidMoves(*this, {x, y});

                // check if any of those attack squares match the King's square?
                for (const sf::Vector2i &move : enemyMoves)
                {
                    if (move.x == kingPos.x && move.y == kingPos.y)
                    {
                        return true; // ALARM! The King is in check!
                    }
                }
            }
        }
    }

    return false; //this false means the king is safe 
}

bool Board::isMoveSafe(sf::Vector2i start, sf::Vector2i target)
{
    // store the piece that is about to be captured so it is not destroyed
    std::unique_ptr<Piece> tempCaptured = std::move(grid[target.x][target.y]);

    //simulate the move in memory do not update the visual positions
    grid[target.x][target.y] = std::move(grid[start.x][start.y]);

    // check weather this simulation put our own King in check?
    bool isWhite = grid[target.x][target.y]->getIsWhite();
    bool inCheck = isInCheck(isWhite);

    // put the piece back where it started
    grid[start.x][start.y] = std::move(grid[target.x][target.y]);

    // put the hidden enemy piece back on the target square
    grid[target.x][target.y] = std::move(tempCaptured);

    // if not in check the move is safe return true
    return !inCheck;
}

bool Board::hasValidMoves(bool whitePlayer)
{
    // loop through the entire board
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            Piece *p = getPieceAt(x, y);

            // check if this a piece and it belong to the current player?
            if (p != nullptr && p->getIsWhite() == whitePlayer)
            {

                // get all its moves
                std::vector<sf::Vector2i> pseudoMoves = p->getValidMoves(*this, {x, y});

                // loop alll the moves
                for (const sf::Vector2i &move : pseudoMoves)
                {
                    // if even one safe moove is possible return true
                    if (isMoveSafe({x, y}, move))
                    {
                        return true;
                    }
                }
            }
        }
    }

    //if checked every single piece and found zero safe moves then return flase
    return false;
} 

// extra added function to change color of any pice at (x, y)
void Board::setColorAt(int x, int y)
{
    sf::Color color(255, 10, 10);
    tiles[x][y].setFillColor(color);
}

void Board::makeRandomAIMove(bool isWhite)
{
    std::vector<AIMove> allPossibleMoves;

    // gather all moves
    // scan the entire board for pieces
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            Piece *p = getPieceAt(x, y);

            if (p != nullptr && p->getIsWhite() == isWhite)
            {
                // get all moves 
                std::vector<sf::Vector2i> pseudoMoves = p->getValidMoves(*this, {x, y});

                // loop through those moves 
                for (const sf::Vector2i &move : pseudoMoves)
                {
                    //check if the move is safe 
                    if (isMoveSafe({x, y}, move))
                    {
                        // if move is safe then push it to possible vlaid moves 
                        allPossibleMoves.push_back({{x, y}, move});
                    }
                }
            }
        }
    }

    // make a raandom move without any strategy 
    if (!allPossibleMoves.empty())
    {        
        int randomIndex = rand() % allPossibleMoves.size();
        AIMove chosenMove = allPossibleMoves[randomIndex];

        movePiece(chosenMove.start, chosenMove.target);
    }
}

  