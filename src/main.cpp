#include <iostream>

#include <imgui.h> // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include <imgui-SFML.h> // for ImGui::SFML::* functions and SFML-specific overloads
#include <SFML/Graphics.hpp>

int main()
{

    unsigned int SCREEN_WIDTH = 1920;
    unsigned int SCREEN_HEIGHT = 1080;

    //-----INIT WINDOW-----
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Nyxel");
    window.setVerticalSyncEnabled(true);
    
    sf::View view = window.getDefaultView();

    //-----INIT IMGUI-----
    if(!ImGui::SFML::Init(window))
    {
        std::cout<<"ERROR::IMGUI::FAILED_TO_INIT_IMGUI-SFML"<<'\n';
    }

    //-----CIRCLE-----


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
        ImGui::Begin("ImGUI Window");
        


        ImGui::End();
        //-----UPDATE-----
        
        
        
        //----DRAWING STUFF-----
        window.clear(sf::Color::Black);
        


        //-----DRAWING WINDOWS-----
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}