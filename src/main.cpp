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

    //Getting ImGUI IO for changing font
    ImGuiIO& io = ImGui::GetIO();
    //adding font
    io.FontDefault = io.Fonts->AddFontFromFileTTF("../resources/fonts/Helvetica.ttf", 18.0f);
    ImGui::SFML::UpdateFontTexture();

    //Styling ImGUi
    ImGuiStyle& style = ImGui::GetStyle();
    
    //MenuBar
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(17/255.0f, 17/255.0f, 17/255.0f, 1.0f); // BG
    style.Colors[ImGuiCol_Text] = ImVec4(220/255.0f, 224/255.0f, 245/255.0f, 1.0f); //TEXT
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(180/255.0f, 190/255.0f, 254/255.0f, 1.0f); // HOVER

    //-----MAIN LOOP-----
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

        //IMGUI
        ImGui::SFML::Update(window, deltaClock.restart());

        //-----DRAWING IMGUI-----
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("Open"))
                {
                    //TODO
                    //Implement OPEN
                }

                if(ImGui::MenuItem("Save"))
                {
                    //TODO
                    //Implement SAVE
                }

                if(ImGui::MenuItem("Exit"))
                {
                    //TODO
                    //Implement EXIT
                }

                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Help"))
            {
                if(ImGui::MenuItem("About"))
                {
                    //TODO
                    //Implement ABOUT
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::Begin("TEST01");
        ImGui::Text("TEST01");
        ImGui::End();

        //END ImGUI-----

        //-----UPDATE-----
        
        
        //----DRAWING-----
        window.clear(sf::Color::Black);
        


        //-----DRAWING WINDOWS-----
        ImGui::SFML::Render(window);
        window.display();
    }

    //CleanUP
    ImGui::SFML::Shutdown();
    return 0;
}