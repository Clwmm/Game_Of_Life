#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>

#include "SFML/Graphics.hpp"

#define MOUSE_WHEEL_SPEED 0.1f

int main()
{
    sf::Vector2f screenSize = sf::Vector2f(900, 900);
    
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Game of Life");
    
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(screenSize.x, screenSize.y));
    ImGui::SFML::Init(window);


    sf::CircleShape shape(200.f, 100);
    shape.setFillColor(sf::Color(204, 77, 5)); // Color circle
    shape.setPosition(200, 200); // Center circle

    float gameZoom = 1.0f;
    bool mouseRightButoonPressed = false;
    sf::Vector2i mouseOldPos;


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


        //RENDER
        window.setView(view);
        window.clear(sf::Color(18, 33, 43)); // Color background
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}