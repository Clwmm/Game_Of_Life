#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include "Cell.h"

#include "SFML/Graphics.hpp"

#define MOUSE_WHEEL_SPEED 0.1f

bool inVector(int y, int x, std::vector<std::vector<Cell*>>& vec)
{
    if (y >= vec.size())
        return false;
    if (x >= vec[y].size())
        return false;
    return true;
}

int checkNeighbors(int y, int x, std::vector<std::vector<Cell*>>& vec)
{
    int noNeighbors = 0;

    if (inVector(y - 1, x - 1, vec))
        if (vec[y - 1][x - 1]->getState() == State::alive)
            noNeighbors++;

    if (inVector(y - 1, x, vec))
        if (vec[y - 1][x]->getState() == State::alive)
            noNeighbors++;

    if (inVector(y - 1, x + 1, vec))
        if (vec[y - 1][x + 1]->getState() == State::alive)
            noNeighbors++;

    if (inVector(y, x - 1, vec))
        if (vec[y][x - 1]->getState() == State::alive)
            noNeighbors++;

    if (inVector(y, x + 1, vec))
        if (vec[y][x + 1]->getState() == State::alive)
            noNeighbors++;

    if (inVector(y + 1, x - 1, vec))
        if (vec[y + 1][x - 1]->getState() == State::alive)
            noNeighbors++;

    if (inVector(y + 1, x, vec))
        if (vec[y + 1][x]->getState() == State::alive)
            noNeighbors++;

    if (inVector(y + 1, x + 1, vec))
        if (vec[y + 1][x + 1]->getState() == State::alive)
            noNeighbors++;

    return noNeighbors;
}

void addTopVec(std::vector<std::vector<Cell*>>& v)
{
    std::vector<Cell*> temp;
    int y_pos = v[0][0]->getPosition().y;
    int x_pos = v[0][0]->getPosition().x;
    for (int i = 0; i < v[0].size(); i++)
        temp.push_back(new Cell(sf::Vector2i(x_pos + i, y_pos -1)));
    v.insert(v.begin(), temp);
}

void addBotVec(std::vector<std::vector<Cell*>>& v)
{
    std::vector<Cell*> temp;
    int y_pos = v[v.size() - 1][0]->getPosition().y;
    int x_pos = v[v.size() - 1][0]->getPosition().x;
    for (int i = 0; i < v[0].size(); i++)
        temp.push_back(new Cell(sf::Vector2i(x_pos + i, y_pos + 1)));
    v.push_back(temp);
}

void addRightVec(std::vector<std::vector<Cell*>>& v)
{
    int y_pos = v[0][v[0].size() - 1]->getPosition().y;
    int x_pos = v[0][v[0].size() - 1]->getPosition().x;
    for (int i = 0; i < v.size(); i++)
        v[i].push_back(new Cell(sf::Vector2i(x_pos + 1, y_pos + i)));
}

void addLeftVec(std::vector<std::vector<Cell*>>& v)
{
    int y_pos = v[0][0]->getPosition().y;
    int x_pos = v[0][0]->getPosition().x;
    for (int i = 0; i < v.size(); i++)
        v[i].insert(v[i].begin(), new Cell(sf::Vector2i(x_pos -1, y_pos + i)));
}

int main()
{
    sf::Vector2f screenSize = sf::Vector2f(900, 900);
    
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Game of Life");
    window.setFramerateLimit(45);
    
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(screenSize.x, screenSize.y));
    ImGui::SFML::Init(window);


    sf::CircleShape shape(200.f, 100);
    shape.setFillColor(sf::Color(204, 77, 5)); // Color circle
    shape.setPosition(200, 200); // Center circle

    float gameZoom = 1.0f;
    bool mouseRightButoonPressed = false;
    sf::Vector2i mouseOldPos;

    std::vector<std::vector<Cell*>> vec2 = { {new Cell(sf::Vector2i(0,0))}};

    addTopVec(vec2);
    addBotVec(vec2);
    addLeftVec(vec2);
    addRightVec(vec2);

    addTopVec(vec2);
    addBotVec(vec2);
    addLeftVec(vec2);
    addRightVec(vec2);

    vec2[0][1]->setSwapReady();
    vec2[0][1]->swapState();

    vec2[0][2]->setSwapReady();
    vec2[0][2]->swapState();

    vec2[1][0]->setSwapReady();
    vec2[1][0]->swapState();

    vec2[1][1]->setSwapReady();
    vec2[1][1]->swapState();

    vec2[2][1]->setSwapReady();
    vec2[2][1]->swapState();


    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                view.setSize(sf::Vector2f(event.size.width, event.size.height));
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                default:
                    break;
                }
                break;

            case sf::Event::MouseWheelMoved:
                gameZoom *= 1.0f - (MOUSE_WHEEL_SPEED * event.mouseWheel.delta);
                view.zoom(1.0f - (MOUSE_WHEEL_SPEED * event.mouseWheel.delta));
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    mouseRightButoonPressed = true;
                    mouseOldPos.x = event.mouseButton.x;
                    mouseOldPos.y = event.mouseButton.y;
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    mouseRightButoonPressed = false;
                }
                break;
            case sf::Event::MouseMoved:
                if (mouseRightButoonPressed)
                {
                    view.move(sf::Vector2f(gameZoom*(mouseOldPos.x - event.mouseMove.x), gameZoom*(mouseOldPos.y - event.mouseMove.y)));
                    mouseOldPos.x = event.mouseMove.x;
                    mouseOldPos.y = event.mouseMove.y;
                }
                break;
            default:
                break;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Window title");
        ImGui::Text("window text");
        ImGui::End();

        for (auto i : vec2)
            for (auto x : i)
                x->swapState();


        window.setView(view);
        window.clear(sf::Color::Black); // Color background

        for (int i = 0; i < vec2.size(); i++)
        {
            for (int j = 0; j < vec2[i].size(); j++)
            {
                if (vec2[i][j]->getState() == State::alive)
                {
                    if (i == 0)
                    {
                        addTopVec(vec2);
                        if (j == 0)
                            addLeftVec(vec2);
                        else if (j == vec2[i].size() - 1)
                            addRightVec(vec2);
                    }
                    else if (i == vec2.size() - 1)
                    {
                        addBotVec(vec2);
                        if (j == 0)
                            addLeftVec(vec2);
                        else if (j == vec2[i].size() - 1)
                            addRightVec(vec2);
                    }
                    else if (j == 0)
                        addLeftVec(vec2);
                    else if (j == vec2[i].size() - 1)
                        addRightVec(vec2);
                }

                vec2[i][j]->behaviour(checkNeighbors(i, j, vec2));
                vec2[i][j]->draw(window);
            }
        }


        //RENDER
        
        /*for (auto i : vec2)
            for (auto x : i)
                x->draw(window);*/
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}