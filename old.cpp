////#include <SFML/Graphics.hpp>
////
////void drawGrid(sf::RenderWindow& window, int gridSizeX, int gridSizeY, int cellSizeX, int cellSizeY, sf::RectangleShape grid[][50]) {
////    for (int i = 0; i < gridSizeX; ++i) {
////        for (int j = 0; j < gridSizeY; ++j) {
////            window.draw(grid[i][j]);
////        }
////    }
////}
////
////void simulateFallingSand(int gridSizeX, int gridSizeY, sf::RectangleShape grid[][50]) {
////    for (int i = 0; i < gridSizeX; ++i) {
////        for (int j = gridSizeY - 2; j >= 0; --j) { // Start from the bottom and go up
////            if (grid[i][j].getFillColor() == sf::Color::Yellow) {
////                if (grid[i][j + 1].getFillColor() == sf::Color::Black) {
////                    // Sand falls down
////                    grid[i][j].setFillColor(sf::Color::Black);
////                    grid[i][j + 1].setFillColor(sf::Color::Yellow);
////                } else if (i > 0 && j < gridSizeY - 1 && grid[i - 1][j + 1].getFillColor() == sf::Color::Black) {
////                    // Sand moves diagonally to the left
////                    grid[i][j].setFillColor(sf::Color::Black);
////                    grid[i - 1][j + 1].setFillColor(sf::Color::Yellow);
////                } else if (i < gridSizeX - 1 && j < gridSizeY - 1 && grid[i + 1][j + 1].getFillColor() == sf::Color::Black) {
////                    // Sand moves diagonally to the right
////                    grid[i][j].setFillColor(sf::Color::Black);
////                    grid[i + 1][j + 1].setFillColor(sf::Color::Yellow);
////                }
////            }
////        }
////    }
////}
////
////int main()
////{
////    int windowSizeX = 700; // Set the window width
////    int windowSizeY = 700; // Set the window height
////    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Falling Sand Simulator");
////
////    int gridSizeX = 50; // Set the grid width
////    int gridSizeY = 50; // Set the grid height
////    int cellSizeX = window.getSize().x / gridSizeX;
////    int cellSizeY = window.getSize().y / gridSizeY;
////    sf::RectangleShape grid[gridSizeX][50]; // The second dimension should be the maximum possible value of gridSizeY
////
////    int fallSpeed = 2; // The speed of falling sand
////    int counter = 0; // A counter to control the speed of falling sand
////
////    int mouseSpeed = 5; // The speed of generating sand
////    int mouseCounter = 0; // A counter to control the speed of generating sand
////
////    for (int i = 0; i < gridSizeX; ++i) {
////        for (int j = 0; j < gridSizeY; ++j) {
////            grid[i][j].setSize(sf::Vector2f(cellSizeX, cellSizeY));
////            grid[i][j].setPosition(i * cellSizeX, j * cellSizeY);
////            grid[i][j].setFillColor(sf::Color::Black);
//////            grid[i][j].setOutlineThickness(1);
//////            grid[i][j].setOutlineColor(sf::Color::White);
////        }
////    }
////
////    while (window.isOpen())
////    {
////        sf::Event event;
////        while (window.pollEvent(event))
////        {
////            if (event.type == sf::Event::Closed)
////                window.close();
////        }
////
////        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseCounter % mouseSpeed == 0) {
////            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
////            int gridX = mousePos.x / cellSizeX;
////            int gridY = mousePos.y / cellSizeY;
////            if (gridX >= 0 && gridX < gridSizeX && gridY >= 0 && gridY < gridSizeY) {
////                grid[gridX][gridY].setFillColor(sf::Color::Yellow);
////            }
////        }
////
////        window.clear();
////        if (counter % fallSpeed == 0) {
////            simulateFallingSand(gridSizeX, gridSizeY, grid);
////        }
////        drawGrid(window, gridSizeX, gridSizeY, cellSizeX, cellSizeY, grid);
////        window.display();
////
////        counter++;
////        mouseCounter++;
////    }
////
////    return 0;
////}
//
//#include <SFML/Graphics.hpp>
//
//void drawGrid(sf::RenderWindow& window, int grid[][50], int gridSizeX, int gridSizeY, int cellSizeX, int cellSizeY) {
//    for (int i = 0; i < gridSizeX; ++i) {
//        for (int j = 0; j < gridSizeY; ++j) {
//            sf::RectangleShape rectangle(sf::Vector2f(cellSizeX, cellSizeY));
//            rectangle.setPosition(i * cellSizeX, j * cellSizeY);
//            if (grid[i][j] == 0) {
//                rectangle.setFillColor(sf::Color::Black);
//            } else if (grid[i][j] == 1) {
//                rectangle.setFillColor(sf::Color::Yellow);
//            } else if (grid[i][j] == 2) {
//                rectangle.setFillColor(sf::Color::Blue);
//            }
//            rectangle.setOutlineThickness(1);
//            rectangle.setOutlineColor(sf::Color::White);
//            window.draw(rectangle);
//        }
//    }
//}
//
//int main()
//{
//    // window settings
//    int windowWidth = 700;
//    int windowHeight = 700;
//
//    // grid settings
//    int gridSizeX = 50;
//    int gridSizeY = 50;
//
//    // cell size
//    int cellSizeX = windowWidth / gridSizeX;
//    int cellSizeY = windowHeight / gridSizeY;
//
//    // initialize the grid
//    int grid[gridSizeX][gridSizeY];
//
//    // define the grid to 0
//    for (int i = 0; i < gridSizeX; ++i) {
//        for (int j = 0; j < gridSizeY; ++j) {
//            grid[i][j] = 0;
//        }
//    }
//
//    // create the window
//    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Falling sand simulator", sf::Style::Close);
//
//    // run the program as long as the window is open
//    while (window.isOpen())
//    {
//        // check all the window's events that were triggered since the last iteration of the loop
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            // "close requested" event: we close the window
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//        window.clear(sf::Color::Black);
//        drawGrid(window, grid, gridSizeX, gridSizeY, cellSizeX, cellSizeY);
//        window.display();
//    }
//
//    return 0;
//}