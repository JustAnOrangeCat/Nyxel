#include <iostream>

#include <imgui.h> // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include <imgui-SFML.h> // for ImGui::SFML::* functions and SFML-specific overloads
#include <SFML/Graphics.hpp>

int main()
{

    unsigned int SCREEN_WIDTH = 800;
    unsigned int SCREEN_HEIGHT = 600;

    //-----INIT WINDOW-----
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "OHH MYY GAAAHH!!");
    window.setVerticalSyncEnabled(true);
    
    sf::View view = window.getDefaultView();

    //-----INIT IMGUI-----
    if(!ImGui::SFML::Init(window))
    {
        std::cout<<"ERROR::IMGUI::FAILED_TO_INIT_IMGUI-SFML"<<'\n';
    }

    //-----CIRCLE-----

    bool circleExists = true;
    float circleRadius = 100.0f;

    float color3[3] = {1/255,1/255,1/255};

    sf::CircleShape circle(circleRadius);
    circle.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - circle.getRadius(), SCREEN_HEIGHT/2 - circle.getRadius()));

    //-----GAME LOOP-----
    sf::Clock deltaClock;
    while(window.isOpen())
    {
        //-----EVENTS-----
        while(const auto event = window.pollEvent())
        {

            ImGui::SFML::ProcessEvent(window, *event);

            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                view.setSize(sf::Vector2f(resized->size.x, resized->size.y));
                window.setView(view);
            }

        } //END EVENT

        ImGui::SFML::Update(window, deltaClock.restart());

        //-----DRAWING IMGUI-----
        ImGui::Begin("MY GAAH!");
        
        ImGui::GetIO().FontGlobalScale = 1.5;
        ImGui::Checkbox("CIRCLE", &circleExists);
        ImGui::SliderFloat("RADIUS", &circleRadius, 10.0f, 500.0f);
        ImGui::ColorEdit3("COLOR", color3);

        ImGui::End();

        //-----UPDATE-----
        circle.setRadius(circleRadius);

        
        sf::Color circleColor = sf::Color(color3[0] * 255, color3[1] * 255, color3[2] * 255);
        circle.setFillColor(circleColor);

        //----DRAWING STUFF-----
        window.clear(sf::Color::Black);
        if(circleExists)
        {
            window.draw(circle);
        }

        //-----DRAWING WINDOWS-----
        ImGui::SFML::Render(window);
        window.display();
    }

}