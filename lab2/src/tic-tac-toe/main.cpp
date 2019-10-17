//
//  main.cpp
//  TicTacToe

#include <SFML/Graphics.hpp>
#include <iostream>

#include <tic-tac-toe/playMove.h>

using namespace std;
using namespace sf;

int main() {

    /************************************************************************************************************/

    /* The following variables define the state of the game                                                     */

    /************************************************************************************************************/
    // You should complete the following declarations
    // Make sure to initialize the variables  

    // The game board array
    int gameBoard[3][3] = {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty};

    // An boolean that represents the turn in the game
    bool is_turn = true;

    // A boolean to represent if the move is valid
    bool is_valid = true;

    // A boolean to represent if the game is over
    bool is_game_over = false;

    // An integer that represents the win code
    int is_winCode = 0;
    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* The loading of the X image is shown. Repeat for the rest of the images                                  */
    /************************************************************************************************************/
    //for now change values

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("X.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite X_sprite(X_texture);


    // Get the O image
    sf::Texture O_texture;
    if (!O_texture.loadFromFile("O.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite O_sprite(O_texture);


    // Get the blank image
    sf::Texture blank_texture;
    if (!blank_texture.loadFromFile("blank.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite blank_sprite(blank_texture);

    /************************************************************************************************************/
    /* Insert code that creates the window and displays it                                                      */
    /************************************************************************************************************/

    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Black) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them
    // The tile size is the size of the images

    const int tileSize = X_texture.getSize().x;

    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3 cell sizes plus 2 barWidth's

    const int barWidth = tileSize / 20;
    const int barHeight = boardSize * tileSize + (boardSize - 1) * barWidth;


    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize * tileSize + (boardSize - 1) * barWidth;

    // Create the main window: it has a title bar and a close button, but is not resizable
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "ECE244 Tic-Tac-Toe");

    // Set the Icon that appears in the task bar when the window is minimized
    // Insert you code here, see the lab handout

    sf::Image myFirstWindowIcon;
    if (!myFirstWindowIcon.loadFromFile("icon.jpg")) {
        return EXIT_FAILURE;
    }
    window.setIcon(myFirstWindowIcon.getSize().x, myFirstWindowIcon.getSize().y, myFirstWindowIcon.getPixelsPtr());


    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (barHeight and barWidth)
    // Insert your code here

    sf::RectangleShape myOwnRectangle(sf::Vector2f(barWidth, barHeight)); //horizontal lines
    myOwnRectangle.setFillColor(sf::Color::Black);
    myOwnRectangle.setPosition(tileSize, 0);


    sf::RectangleShape myOwnRectangle1(sf::Vector2f(barWidth, barHeight));
    myOwnRectangle1.setFillColor(sf::Color::Black);
    myOwnRectangle1.setPosition(tileSize * 2, 0);

    sf::RectangleShape myOwnRectangle2(sf::Vector2f(barWidth, barHeight)); //vertical lines
    myOwnRectangle2.setFillColor(sf::Color::Black);
    myOwnRectangle2.setPosition(0, tileSize);
    myOwnRectangle2.rotate(-90);


    sf::RectangleShape myOwnRectangle3(sf::Vector2f(barWidth, barHeight));
    myOwnRectangle3.setFillColor(sf::Color::Black);
    myOwnRectangle3.setPosition(0, tileSize * 2);
    myOwnRectangle3.rotate(-90);

    window.clear();

    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/
    // Start the game loop that runs as long as the window is open

    while (window.isOpen()) {
        // The event
        sf::Event event;

        // Process the events
        while (window.pollEvent(event)) {

            // This is the handling of the close window event
            // Close window: exit

            if (event.type == sf::Event::Closed) {

                window.close();

            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {

                window.close();

            }
            // Left mouse button pressed: get the click position and play the move
            // is_game_over is a variable you should define above

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
 {

                // left mouse button is pressed: get the coordinates in pixels
                // Insert your code to get the coordinates here
                // left mouse button is pressed
                // Get the coordinates in pixels.

                sf::Vector2i localPosition = Mouse::getPosition(window);

                // The Vector2i is a type defined in SFML that defines a
                // two element integer vector (x,y). This is how the
                // elements of the vector are accessed

                int xPosition = localPosition.x;
                int yPosition = localPosition.y;

                int row, col;


                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                // Also make sure that row and column values are valid
                // Insert your code below
                
                if (xPosition > barWidth && xPosition <= tileSize && yPosition > barWidth && yPosition <= tileSize) {
                    row = 0;
                    col = 0;
                }
                else if (xPosition > (barWidth * 2 + tileSize) && xPosition <= (barWidth * 3 + tileSize * 2) && yPosition > barWidth && yPosition <= tileSize) {
                    row = 0;
                    col = 1;
                } else if (xPosition > (barWidth * 3 + tileSize * 2) && xPosition <= (barWidth * 4 + tileSize * 3) && yPosition > barWidth && yPosition <= tileSize) {
                    row = 0;
                    col = 2;
                } else if (xPosition > barWidth && xPosition <= tileSize && yPosition > (barWidth * 2 + tileSize) && yPosition <= (barWidth * 3 + tileSize * 2)) {
                    row = 1;
                    col = 0;
                } else if (xPosition > (barWidth * 2 + tileSize) && xPosition <= (barWidth * 3 + tileSize * 2) && yPosition > (barWidth * 2 + tileSize) && yPosition <= (barWidth * 3 + tileSize * 2)) {
                    row = 1;
                    col = 1;
                } else if (xPosition > (barWidth * 3 + tileSize * 2) && xPosition <= (barWidth * 4 + tileSize * 3) && yPosition > (barWidth * 2 + tileSize) && yPosition <= (barWidth * 3 + tileSize * 2)) {
                    row = 1;
                    col = 2;
                } else if (xPosition > barWidth && xPosition <= tileSize && yPosition > (barWidth * 3 + tileSize * 2) && yPosition <= (barWidth * 4 + tileSize * 3)) {
                    row = 2;
                    col = 0;
                } else if (xPosition > (barWidth * 2 + tileSize) && xPosition <= (barWidth * 3 + tileSize * 2) && yPosition > (barWidth * 3 + tileSize * 2) && yPosition <= (barWidth * 4 + tileSize * 3)) {
                    row = 2;
                    col = 1;
                } else if (xPosition > (barWidth * 3 + tileSize * 2) && xPosition <= (barWidth * 4 + tileSize * 3) && yPosition > (barWidth * 3 + tileSize * 2) && yPosition <= (barWidth * 4 + tileSize * 3)) {
                    row = 2;
                    col = 2;
                } else {
                    continue;
                }

                // Play the move by calling the playMove function
                // Insert your code below

                playMove(gameBoard, row, col, is_turn, is_valid, is_game_over, is_winCode);

            }

        }

        int sizeI[3] = {0, tileSize + barWidth, (tileSize * 2)+(barWidth * 2)};
        int sizeJ[3] = {0, tileSize + barWidth, (tileSize * 2)+(barWidth * 2)};

        for (int i = 0; i < 3; i++) //draws the tiles
        {
            for (int j = 0; j < 3; j++) {
                if (gameBoard[i][j] == 0) //all blanks
                {
                    blank_sprite.setPosition(sizeI[i], sizeJ[j]);
                    window.draw(blank_sprite);
                }
                else if (gameBoard[i][j] == 1 && is_valid == true) {
                    X_sprite.setPosition(sizeI[i], sizeJ[j]);
                    window.draw(X_sprite);
                }
                else if (gameBoard[i][j] == -1 && is_valid == true) {
                    O_sprite.setPosition(sizeI[i], sizeJ[j]);
                    window.draw(O_sprite);
                }
            }
        }
        if (is_game_over == true) 
        {
            sf::RectangleShape winRectangle(sf::Vector2f(10, barHeight * 3)); //for white lines when winning

            winRectangle.setFillColor(sf::Color::White);
            int colPos, rowPos, angle;
            if (is_winCode == 1) {
                colPos = tileSize / 2;
                rowPos = 0;
                angle = -90;
            } else if (is_winCode == 2) {
                colPos = tileSize / 2 + barWidth + tileSize;
                rowPos = 0;
                angle = -90;
            } else if (is_winCode == 3) {
                colPos = tileSize / 2 + (barWidth * 2)+(tileSize * 2);
                rowPos = 0;
                angle = -90;
            } else if (is_winCode == 4) {
                rowPos = tileSize / 2;
                colPos = 0;
                angle = 0;
            } else if (is_winCode == 5) {
                rowPos = tileSize / 2 + barWidth + tileSize;
                colPos = 0;
                angle = 0;
            } else if (is_winCode == 6) {
                rowPos = tileSize / 2 + (barWidth * 2)+(tileSize * 2);
                colPos = 0;
                angle = 0;
            } else if (is_winCode == 7) {
                colPos = 0;
                rowPos = 0;
                angle = -45;
            } else if (is_winCode == 8) {
                colPos = 0;
                rowPos = barHeight - barWidth;
                angle = +45;
            }
            winRectangle.setPosition(rowPos, colPos);

            winRectangle.rotate(angle);
            window.draw(winRectangle);
        }


        window.display(); //displays window

    }

    return 0;

}

