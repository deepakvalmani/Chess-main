#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "board.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"
#include <ctime>
#include <cstdlib>

// Game states
enum class GameState
{
    MENU,
    VS_AI,
    VS_FRIEND
};

// Button class for menu
class Button
{
private:
    sf::RectangleShape shape;
    sf::Text text;
    bool isHovered = false;

public:
    Button(const std::string &label, sf::Font &font, float width, float height) : text(font, "", 32)
    {
        shape.setSize({width, height});
        shape.setFillColor(sf::Color(50, 50, 50));
        shape.setOutlineThickness(3);
        shape.setOutlineColor(sf::Color::White);

        text.setString(label);
        text.setCharacterSize(32);
        text.setFillColor(sf::Color::White);
    }

    void setPosition(float x, float y)
    {
        shape.setPosition({x, y});
        // Center text in button
        sf::FloatRect textBounds = text.getLocalBounds();
        float textX = x + (shape.getSize().x - textBounds.size.x) / 2.f;
        float textY = y + (shape.getSize().y - textBounds.size.y) / 2.f - textBounds.position.y;
        text.setPosition({textX, textY});
    }

    bool isClicked(sf::RenderWindow &window)
    {
        sf::Vector2f mousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        return shape.getGlobalBounds().contains(mousePos);
    }

    void update(sf::RenderWindow &window)
    {
        sf::Vector2f mousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        isHovered = shape.getGlobalBounds().contains(mousePos);

        if (isHovered)
        {
            shape.setFillColor(sf::Color(255, 100, 0));
        }
        else
        {
            shape.setFillColor(sf::Color(50, 50, 50));
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
        window.draw(text);
    }
};

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode({800, 800}), "Chess");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.openFromFile("assets/font.ttf"))
    {
        std::cerr << "Warning: Could not load font.ttf!\n";
    }

    // Create menu buttons
    Button btnAI("Play vs AI", font, 300.f, 80.f);
    btnAI.setPosition(250.f, 300.f);

    Button btnFriend("Play with Friend", font, 300.f, 80.f);
    btnFriend.setPosition(250.f, 420.f);

    // Title text
    sf::Text titleText(font);
    titleText.setString("CHESS");
    titleText.setCharacterSize(72);
    titleText.setFillColor(sf::Color::White);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(3);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition({400.f - titleBounds.size.x / 2.f, 150.f});

    // Subtitle
    sf::Text subtitleText(font);
    subtitleText.setString("Select Game Mode");
    subtitleText.setCharacterSize(28);
    subtitleText.setFillColor(sf::Color(200, 200, 200));
    sf::FloatRect subBounds = subtitleText.getLocalBounds();
    subtitleText.setPosition({400.f - subBounds.size.x / 2.f, 240.f});

    // Game state
    GameState gameState = GameState::MENU;
    Board myBoard;

    // Game state variables 
    Piece *selectedPiece = nullptr;
    sf::Vector2i selectedPos = {-1, -1};
    std::vector<sf::Vector2i> currentValidMoves;

    // AI timer variables
    sf::Clock aiTimer;
    bool waitingForAI = false;

    // White always goes first
    bool isWhiteTurn = true;
    std::string statusMessage = "White's Turn";

    //ui setup
    sf::Text turnText(font);
    turnText.setCharacterSize(30);
    turnText.setFillColor(sf::Color::Black);
    turnText.setOutlineColor(sf::Color::White);
    turnText.setOutlineThickness(2.f);
    turnText.setPosition({10.f, 10.f});

    sf::RectangleShape highlightBox({100.f, 100.f});
    highlightBox.setFillColor(sf::Color(0, 255, 0, 100));

    // back to menu button
    sf::RectangleShape backButton({80.f, 30.f});
    backButton.setPosition({10.f, 760.f});
    backButton.setFillColor(sf::Color(50, 50, 50));
    backButton.setOutlineColor(sf::Color::White);
    backButton.setOutlineThickness(2);

    sf::Text backText(font);
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    backText.setPosition({25.f, 765.f});

    while (window.isOpen())
    {
        if (gameState == GameState::MENU)
        { //menu loop
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }

                if (const auto *mouseBtn = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouseBtn->button == sf::Mouse::Button::Left)
                    {
                        btnAI.update(window);
                        btnFriend.update(window);

                        if (btnAI.isClicked(window))
                        {
                            gameState = GameState::VS_AI;
                            // Reset game
                            myBoard.reset();
                            isWhiteTurn = true;
                            statusMessage = "White's Turn";
                            selectedPiece = nullptr;
                            selectedPos = {-1, -1};
                            currentValidMoves.clear();
                        }
                        else if (btnFriend.isClicked(window))
                        {
                            gameState = GameState::VS_FRIEND;
                            // Reset game
                            myBoard.reset();
                            isWhiteTurn = true;
                            statusMessage = "White's Turn";
                            selectedPiece = nullptr;
                            selectedPos = {-1, -1};
                            currentValidMoves.clear();
                        }
                    }
                } 
            }

            // update button hover states
            btnAI.update(window);
            btnFriend.update(window);

            // draw menu
            window.clear(sf::Color(30, 30, 30));
            window.draw(titleText);
            window.draw(subtitleText);
            btnAI.draw(window);
            btnFriend.draw(window);
            window.display();
        }
        else
        {
            // main game loop
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }

                // Check for back to menu button
                if (const auto *mouseBtn = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouseBtn->button == sf::Mouse::Button::Left)
                    {
                        int clickX = mouseBtn->position.x;
                        int clickY = mouseBtn->position.y;
                        // Check if back button clicked
                        if (clickX >= 10 && clickX <= 160 && clickY >= 760 && clickY <= 800)
                        {
                            gameState = GameState::MENU;
                            continue;
                        }
                    }
                }

                // user input: VS_FRIEND allows both players VS_AI only White
                bool canPlay = (gameState == GameState::VS_FRIEND) ||
                               (gameState == GameState::VS_AI && isWhiteTurn);

                if (canPlay)
                {
                    if (const auto *mouseBtn = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        if (mouseBtn->button == sf::Mouse::Button::Left)
                        {
                            int gridX = mouseBtn->position.x / 100;
                            int gridY = mouseBtn->position.y / 100;

                            if (!selectedPiece)
                            {
                                Piece *clickedPiece = myBoard.getPieceAt(gridX, gridY);

                                // allow selecting piece of the current player's color
                                if (clickedPiece && clickedPiece->getIsWhite() == isWhiteTurn)
                                {
                                    selectedPiece = clickedPiece;
                                    selectedPos = {gridX, gridY};
                                    std::vector<sf::Vector2i> pseudoMoves = selectedPiece->getValidMoves(myBoard, selectedPos);
                                    currentValidMoves.clear();

                                    for (const sf::Vector2i &move : pseudoMoves)
                                    {
                                        if (myBoard.isMoveSafe(selectedPos, move))
                                        {
                                            currentValidMoves.push_back(move);
                                        }
                                    }
                                }
                            }
                        }
                        else if (mouseBtn->button == sf::Mouse::Button::Right && selectedPiece)
                        {
                            int gridX = mouseBtn->position.x / 100;
                            int gridY = mouseBtn->position.y / 100;

                            sf::Vector2i clickPos = {gridX, gridY};
                            bool isValidMove = false;
                            for (const sf::Vector2i &move : currentValidMoves)
                            {
                                if (move.x == clickPos.x && move.y == clickPos.y)
                                {
                                    isValidMove = true;
                                    break;
                                }
                            }
                            if (isValidMove)
                            {
                                myBoard.movePiece(selectedPos, clickPos);
                                isWhiteTurn = !isWhiteTurn;

                                if (!myBoard.hasValidMoves(isWhiteTurn))
                                {
                                    if (myBoard.isInCheck(isWhiteTurn))
                                    {
                                        statusMessage = isWhiteTurn ? "CHECKMATE! Black Wins!" : "CHECKMATE! White Wins!";
                                    }
                                    else
                                    {
                                        statusMessage = "STALEMATE! It's a draw.";
                                    }
                                }
                                else if (myBoard.isInCheck(isWhiteTurn))
                                {
                                    statusMessage = isWhiteTurn ? "White's Turn (IN CHECK!)" : "Black's Turn (IN CHECK!)";
                                }
                                else
                                {
                                    statusMessage = isWhiteTurn ? "White's Turn" : "Black's Turn";
                                }

                                // AI turn in vs AI mode
                                if (gameState == GameState::VS_AI && !isWhiteTurn && statusMessage.find("CHECKMATE") == std::string::npos)
                                {
                                    waitingForAI = true;
                                    aiTimer.restart();
                                }
                            }

                            selectedPiece = nullptr;
                            selectedPos = {-1, -1};
                            currentValidMoves.clear();
                        }
                    }
                }
            }

            // AI move in vs AI mode
            if (gameState == GameState::VS_AI && waitingForAI && aiTimer.getElapsedTime().asMilliseconds() > 250)
            {
                myBoard.makeRandomAIMove(false);
                waitingForAI = false;
                isWhiteTurn = true;

                if (!myBoard.hasValidMoves(isWhiteTurn))
                {
                    if (myBoard.isInCheck(isWhiteTurn))
                        statusMessage = "CHECKMATE! Black Wins!";
                    else
                        statusMessage = "STALEMATE! It's a draw.";
                }
                else if (myBoard.isInCheck(isWhiteTurn))
                {
                    statusMessage = "White's Turn (IN CHECK!)";
                }
                else
                {
                    statusMessage = "White's Turn";
                }
            }

            turnText.setString(statusMessage);

            window.clear();
            myBoard.draw(window);

            if (selectedPiece != nullptr)
            {
                highlightBox.setFillColor(sf::Color(255, 255, 0, 100));
                highlightBox.setPosition({selectedPos.x * 100.f, selectedPos.y * 100.f});
                window.draw(highlightBox);

                highlightBox.setFillColor(sf::Color(0, 255, 0, 100));
                for (const sf::Vector2i &move : currentValidMoves)
                {
                    highlightBox.setPosition({move.x * 100.f, move.y * 100.f});
                    window.draw(highlightBox);
                }
            }

            window.draw(turnText);
            window.draw(backButton);
            window.draw(backText);
            window.display();
        }
    }

    return 0;
}
