#include <SFML/Graphics.hpp>
#include <vector>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

using namespace std;


// Function to fill a 2D vector with zeros
void fillWithZeros(vector<vector<int>>& grid) {
    for (auto& row : grid) {
        for (auto& element : row) {
            element = 0;
        }
    }
}

void drawGrid(sf::RenderWindow& window, const vector<vector<int>>& grid, int cellWidth, int cellHeight, sf::Color sandColor) {

    // loop through the vector (the grid)
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {

            // create rectangle for the element
            sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            // set position of the rectangle
            cell.setPosition(j * cellWidth, i * cellHeight);

            // set an outline so the grid is visible
//            cell.setOutlineColor(sf::Color::White);
//            cell.setOutlineThickness(1);

            // set color based on the value of the element
            if (grid[i][j] == 0) {
                cell.setFillColor(sf::Color::Black);
            } else if (grid[i][j] == 1) {
                cell.setFillColor(sandColor);
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
            if (grid[i][j] == 1) { // Aktueller Punkt ist Sand
                if (i < grid.size() -1) { // Sand ist nicht am Boden
                    if (grid[i+1][j] == 1) { // Unter dem Sand ist Sand
                        if (j != 0 && j != grid[i].size() - 1) { // Sand ist nicht an der linken oder rechten Wand
                            // generate a random number (0 or 1)
                            int randNum = rand() % 2;
                            if (randNum == 0 && grid[i+1][j-1] == 0) { // if random number is 0 and left bottom is empty
                                newGrid[i+1][j-1] = 1;
                            } else if (randNum == 1 && grid[i+1][j+1] == 0) { // if random number is 1 and right bottom is empty
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
    int windowWidth = 900;
    int windowHeight = 900;

    // grid size
    int gridWidth = 75;
    int gridHeight = 75;

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

    // Initialize ImGui for the window
    if (!ImGui::SFML::Init(window)) {
        std::cerr << "ImGui::SFML::Init failed" << std::endl;
        return -1;
    }

    ImGui::SetNextWindowSize(ImVec2(100, 350));

//    ImGuiIO& io = ImGui::GetIO();
//    io.FontGlobalScale = 1.2f;

    // Uhr für die Zeit pro Frame
    sf::Clock clock;
    // Zeit pro Frame
    sf::Time timePerFrame = sf::milliseconds(0.3f);

    // Stoppuhr für Sandplatzierung (Damit bei einem Mausklick nicht so schnell Sand platziert wird)
    sf::Clock sandClock;
    // Delay für die Sandplatzierung (in Sekunden)
    float sandDelay = 0.02f ;

    int particleType = 1;

    // color of the sand
    sf::Color sandColor = sf::Color::Yellow;

    // Multiple Sand mode on/off
    bool multipleParticles = false;

    sf::Clock deltaClock;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time deltaTime = deltaClock.restart();
        ImGui::SFML::Update(window, deltaTime);

        ImGuiIO& io = ImGui::GetIO();

        // check if the left mouse button is pressed
        if (!io.WantCaptureMouse && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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
                    grid[gridY][gridX] = particleType;

                    // if multileParticles mode is on, place additional particle blocks around the cursor
                    if (multipleParticles) {
                        vector<pair<int, int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
                        for (auto& offset : offsets) {
                            int newGridX = gridX + offset.first;
                            int newGridY = gridY + offset.second;
                            if (newGridX >= 0 && newGridX < gridWidth && newGridY >= 0 && newGridY < gridHeight) {
                                grid[newGridY][newGridX] = particleType;
                            }
                        }
                    }
                }
                // reset the clock
                sandClock.restart();
            }
        }

        // ImGui GUI
        ImGui::Begin("Controls");
        ImGui::Text("Left click to place a particle :)");
//        ImGui::RadioButton("Sand", &particleType, 1);
//        ImGui::RadioButton("Water", &particleType, 2);
        ImGui::Separator();
        ImGui::Checkbox("Multiple Particles", &multipleParticles);
        ImGui::SliderFloat("Sand generation speed", &sandDelay, 0.001f, 0.1f);

        sf::Color tempColor = sandColor;
        float color[4] = { tempColor.r / 255.f, tempColor.g / 255.f, tempColor.b / 255.f, 1.0f };
        if (ImGui::ColorButton("Sand Color", ImVec4(color[0], color[1], color[2], color[3]))) {
            ImGui::OpenPopup("Sand Color Picker");
        }
        ImGui::SameLine();
        ImGui::Text("Sand Color");
        if (ImGui::BeginPopup("Sand Color Picker")) {
            if (ImGui::ColorPicker3("##picker", color)) {
                sandColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
                sandColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
                sandColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
            }
            ImGui::EndPopup();
        }
        if (ImGui::Button("Reset")) {
            fillWithZeros(grid);
            sandDelay = 0.02f;
            multipleParticles = false;
            int particleType = 1;
            sandColor = sf::Color::Yellow;
        }
        ImGui::End();

        // Wenn Zeit für neuen Frame erreicht ist -> neuen Frame zeichnen
        if (clock.getElapsedTime() >= timePerFrame)
        {
            animateNextFrame(grid, newGrid);
            grid = newGrid;
            fillWithZeros(newGrid);

            window.clear(sf::Color::Black);
            drawGrid(window, grid, cellWidth, cellHeight, sandColor);

            // Render ImGui
            ImGui::SFML::Render(window);

            window.display();

            // reset the clock
            clock.restart();
        }
    }

    // Cleanup ImGui resources
    ImGui::SFML::Shutdown();

    return 0;
}
