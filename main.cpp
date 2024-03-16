#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

// Function to fill a 2D vector with zeros
void fillWithZeros(vector<vector<int>>& grid) {
    for (auto& row : grid) {
        for (auto& element : row) {
            element = 0;
        }
    }
}

void drawGrid(sf::RenderWindow& window, const vector<vector<int>>& grid, int cellWidth, int cellHeight) {

    // loop through the vector (the grid)
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {

            // create rectangle for the element
            sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            // set position of the rectangle
            cell.setPosition(j * cellWidth, i * cellHeight);

            // set an outline so the grid is visible
            //cell.setOutlineColor(sf::Color::White);
            //cell.setOutlineThickness(1);

            // set color based on the value of the element
            if (grid[i][j] == 0) {
                cell.setFillColor(sf::Color::Black);
            } else if (grid[i][j] == 1) {
                cell.setFillColor(sf::Color::Yellow);
            } else if (grid[i][j] == 2) {
                cell.setFillColor(sf::Color::Blue);
            }

            //draw the rectangle to the window
            window.draw(cell);
        }
    }
}

void animateNextFrame(vector<vector<int>>& grid, vector<vector<int>>& newGrid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
//            if (grid[i][j] == 1 && i < grid.size() - 1) { // Wenn der Sand nicht am Boden ist
//                if (grid[i+1][j] == 0) { // Unter dem Sand ist kein Sand
//                    newGrid[i+1][j] = 1;
//                } else if (grid[i+1][j] == 1) { // Unter dem Sand ist Sand
//                    if (j != 0 && j != grid[i].size() - 1) {
//                        if (grid[i+1][j-1] == 0) { // Links unten ist kein Sand
//                            grid[i+1][j-1] = 1;
//                        } else if (grid[i+1][j+1] == 0) { // Rechts unten ist kein Sand
//                            grid [i+1][j+1] = 1;
//                        }
//                    } else if (j == 0) { // Wenn der Sand an der linken Wand ist
//                        if (grid[i+1][j+1] == 0) { // Rechts unten ist kein Sand
//                            grid [i+1][j+1] = 1;
//                        }
//                    } else if (j == grid[i].size() -1) { // Wenn der Sand an der rechten Wand ist
//                        if (grid[i+1][j-1] == 0) { // Links unten ist kein Sand
//                            grid[i+1][j-1] = 1;
//                        }
//                    } else { // Wenn der Sand nicht fällt
//                        newGrid[i][j] = 1;
//                    }
//                }
//            } else if (grid[i][j] == 1 && i == grid.size() - 1) { // Wenn der Sand am Boden ist
//                newGrid[i][j] = 1;
//
//            }

            if (grid[i][j] == 1) {
                if (i < grid.size() -1) { // Sand ist nicht am Boden
                    if (grid[i+1][j] == 1) { // Unter dem Sand ist Sand
                        if (j != 0 && j != grid[i].size() - 1) { // Sand ist nicht an der linken oder rechten Wand
                            if (grid[i+1][j-1] == 0) { // Links unten ist kein Sand
                                newGrid[i+1][j-1] = 1;
                            } else if (grid[i+1][j+1] == 0) { // Rechts unten ist kein Sand
                                newGrid[i+1][j+1] = 1;
                            } else {
                                newGrid[i][j] = 1;
                            }
                        } else if (j == 0) { // Sand ist an der linken Wand
                            if (grid[i+1][j+1] == 0) { // Rechts unten ist kein Sand
                                newGrid[i+1][j+1] = 1;
                            } else {
                                newGrid[i][j] = 1;
                            }
                        } else if (j == grid[i].size() - 1) { // Sand ist an der rechten Wand
                            if (grid[i+1][j-1] == 0) { // Links unten ist kein Sand
                                newGrid[i+1][j-1] = 1;
                            } else {
                                newGrid[i][j] = 1;
                            }
                        }
                    } else { // Unter dem Sand ist kein Sand
                        newGrid[i+1][j] = 1;
                    }
                } else if (i == grid.size() - 1) { // Sand ist am Boden
                    newGrid[i][j] = 1;
                }
            }

        }
    }
}

int main()
{
    // window settings
    int windowWidth = 700;
    int windowHeight = 700;

    // grid size
    int gridWidth = 50;
    int gridHeight = 50;

    // calculate cell size
    int cellWidth = windowWidth / gridWidth;
    int cellHeight = windowHeight / gridHeight;

    // initialize grid and fill with zeros
    vector<vector<int>> grid(gridWidth, vector<int>(gridHeight));
    fillWithZeros(grid);

    // initialize the grid of the new frame and fill with zeros
    vector<vector<int>> newGrid(gridWidth, vector<int>(gridHeight));
    fillWithZeros(newGrid);

    // create the window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Falling sand simulator", sf::Style::Close);

    // Uhr für die Zeit pro Frame
    sf::Clock clock;
    // Zeit pro Frame
    sf::Time timePerFrame = sf::milliseconds(16);

    // Stoppuhr für Sandplatzierung (Damit bei einem Mausklick nicht so schnell Sand platziert wird)
    sf::Clock sandClock;
    // Delay für die Sandplatzierung (in Sekunden)
    float sandDelay = 0.05f ;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // check if the left mouse button is pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // check if the delay has passed
            if (sandClock.getElapsedTime().asSeconds() >= sandDelay) {
                // get the current mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // convert the mouse position to grid coordinates
                int gridX = mousePos.x / cellWidth;
                int gridY = mousePos.y / cellHeight;
                // check if the grid coordinates are within the grid boundaries
                if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight) {
                    // set the corresponding grid cell to 1
                    grid[gridY][gridX] = 1;
                }
                // reset the clock
                sandClock.restart();
            }
        }

        // Wenn Zeit für neuen Frame erreicht ist -> neuen Frame zeichnen
        if (clock.getElapsedTime() >= timePerFrame)
        {
            animateNextFrame(grid, newGrid);
            grid = newGrid;
            fillWithZeros(newGrid);

            window.clear(sf::Color::Black);
            drawGrid(window, grid, cellWidth, cellHeight);
            window.display();

            // reset the clock
            clock.restart();
        }
    }

    return 0;
}