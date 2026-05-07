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
    // Standard chess board colors:
    // Light squares: Cream/Off-white (RGB: 238, 238, 210)
    // Dark squares: Dark brown (RGB: 118, 150, 86)
    sf::Color lightColor(238, 238, 210); // Classic chess board light
    sf::Color darkColor(118, 150, 86);   // Classic chess board dark

    // Loop through the 8x8 grid to set up the visual tiles
    for (int file = 0; file < 8; ++file)
    { // x-axis (columns A-H)
        for (int rank = 0; rank < 8; ++rank)
        { // y-axis (rows 1-8)

            tiles[file][rank].setSize({tileSize, tileSize});
            tiles[file][rank].setPosition({file * tileSize, rank * tileSize});

            // Standard chess logic for alternating colors
            if ((file + rank) % 2 == 0)
            {
                tiles[file][rank].setFillColor(lightColor); // Light square
            }
            else
            {
                tiles[file][rank].setFillColor(darkColor); // Dark square
            }
            // Remove texture reference - use solid colors
            tiles[file][rank].setTexture(nullptr);
        }
    }

    // --- BOARD SETUP ---
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
    // Standard chess board colors:
    sf::Color lightColor(238, 238, 210);
    sf::Color darkColor(118, 150, 86);

    // Clear the grid
    for (int file = 0; file < 8; ++file)
    {
        for (int rank = 0; rank < 8; ++rank)
        {
            grid[file][rank].reset();
            // Reset tile colors too
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

    // Re-setup the board (same as constructor)
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
    // 1. Draw all the squares first
    for (int file = 0; file < 8; ++file)
    {
        for (int rank = 0; rank < 8; ++rank)
        {
            window.draw(tiles[file][rank]);
        }
    }

    // 2. Draw all the pieces on top
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
    // Make sure we don't check outside the board!
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        return grid[x][y].get();
    }
    return nullptr;
}

void Board::movePiece(sf::Vector2i start, sf::Vector2i target)
{
    // 1. Move the underlying memory pointer to the new square.
    // std::move transfers ownership. The old square automatically becomes nullptr!
    // If an enemy piece was already at the target, it gets destroyed automatically.
    grid[target.x][target.y] = std::move(grid[start.x][start.y]);

    // 2. Tell the piece to update its visual sprite position to match the new square
    if (grid[target.x][target.y] != nullptr)
    {
        grid[target.x][target.y]->setPosition(target.x, target.y);
    }

    // --- 3. PAWN PROMOTION LOGIC ---
    // dynamic_cast safely asks: "Is this Piece pointer actually pointing to a Pawn?"
    // If it is NOT a pawn, pawnPtr will just be nullptr.
    Pawn *pawnPtr = dynamic_cast<Pawn *>(grid[target.x][target.y].get());

    if (pawnPtr != nullptr)
    {
        bool isWhite = pawnPtr->getIsWhite();

        // Check if it reached the final row (0 for White moving up, 7 for Black moving down)
        if ((isWhite && target.y == 0) || (!isWhite && target.y == 7))
        {

            // Overwrite the Pawn with a brand new Queen!
            // The old Pawn is automatically deleted from memory by unique_ptr.
            grid[target.x][target.y] = std::make_unique<Queen>(isWhite);

            // Update the new Queen's visual position
            grid[target.x][target.y]->setPosition(target.x, target.y);
        }
    }
}

bool Board::isInCheck(bool whiteKing) const
{
    sf::Vector2i kingPos = {-1, -1};

    // --- STEP 1: FIND THE KING ---
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            Piece *p = getPieceAt(x, y);

            // Is there a piece here, and is it the color we are checking?
            if (p != nullptr && p->getIsWhite() == whiteKing)
            {

                // X-Ray Scanner: Is this specific piece the King?
                if (dynamic_cast<King *>(p) != nullptr)
                {
                    kingPos = {x, y};
                    break; // Found him, stop searching this row
                }
            }
        }
    }

    // Safety check in case the King was somehow deleted (shouldn't happen in normal chess)
    if (kingPos.x == -1)
        return false;

    // --- STEP 2: CHECK ENEMY CROSSHAIRS ---
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            Piece *p = getPieceAt(x, y);

            // Is this an ENEMY piece?
            if (p != nullptr && p->getIsWhite() != whiteKing)
            {

                // Get all the squares this enemy can attack
                std::vector<sf::Vector2i> enemyMoves = p->getValidMoves(*this, {x, y});

                // Do any of those attack squares match the King's square?
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

    return false; // The King is safe.
}

bool Board::isMoveSafe(sf::Vector2i start, sf::Vector2i target)
{
    // 1. Hide the piece that is about to be captured so it isn't destroyed!
    std::unique_ptr<Piece> tempCaptured = std::move(grid[target.x][target.y]);

    // 2. Simulate the move in memory (Do NOT update the visual positions)
    grid[target.x][target.y] = std::move(grid[start.x][start.y]);

    // 3. Ring the alarm! Does this simulation put our own King in Check?
    bool isWhite = grid[target.x][target.y]->getIsWhite();
    bool inCheck = isInCheck(isWhite);

    // 4. UNDO THE MOVE: Put our piece back where it started
    grid[start.x][start.y] = std::move(grid[target.x][target.y]);

    // 5. UNDO THE CAPTURE: Put the hidden enemy piece back on the target square
    grid[target.x][target.y] = std::move(tempCaptured);

    // If we are NOT in check, the move is safe (true)
    return !inCheck;
}

bool Board::hasValidMoves(bool whitePlayer)
{
    // Loop through the entire board
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            Piece *p = getPieceAt(x, y);

            // Is it a piece, and does it belong to the current player?
            if (p != nullptr && p->getIsWhite() == whitePlayer)
            {

                // Get all its mathematical moves
                std::vector<sf::Vector2i> pseudoMoves = p->getValidMoves(*this, {x, y});

                // Run them through the filter
                for (const sf::Vector2i &move : pseudoMoves)
                {
                    // If we find even ONE safe move, they are not trapped!
                    if (isMoveSafe({x, y}, move))
                    {
                        return true;
                    }
                }
            }
        }
    }

    // If we checked every single piece and found zero safe moves:
    return false;
}

void Board::makeRandomAIMove(bool isWhite)
{
    std::vector<AIMove> allPossibleMoves;

    // 1. GATHER ALL LEGAL MOVES
    // Scan the entire board for our pieces
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            Piece *p = getPieceAt(x, y);

            if (p != nullptr && p->getIsWhite() == isWhite)
            {
                // Get the mathematical moves
                std::vector<sf::Vector2i> pseudoMoves = p->getValidMoves(*this, {x, y});

                // Filter them using our Check-Detector!
                for (const sf::Vector2i &move : pseudoMoves)
                {
                    if (isMoveSafe({x, y}, move))
                    {
                        // Package it up and add it to the master list
                        allPossibleMoves.push_back({{x, y}, move});
                    }
                }
            }
        }
    }

    // 2. MAKE A RANDOM MOVE
    if (!allPossibleMoves.empty())
    {
        // Pick a random index
        int randomIndex = rand() % allPossibleMoves.size();
        AIMove chosenMove = allPossibleMoves[randomIndex];

        // Execute the move exactly like a human player would!
        movePiece(chosenMove.start, chosenMove.target);
    }
}
