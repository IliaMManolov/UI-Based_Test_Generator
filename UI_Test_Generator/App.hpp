//This is the main app file
//It's separated into a couple of main functions and some stats functions
//This is where the UI and all resources are saved and managed


#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Window/Event.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "UserInterface.hpp"        //for the UI


#include <string>

class App
{
    private:

        //Main functionality variables
        sf::RenderWindow mWindow;       //main window for drawing
        sf::Time mTimePerFrame;         //for managing framerate
        UserInterface mUI;              //the UI class
                                        //TO-DO: Add Resources class, which holds fonts, images and audio
                                        //TO-DO: Add Resources class, which holds functions for each button


        //Main functionality functions
        void handleEvents();
        void update(sf::Time deltaTime);
        void render();



        //Statistics stuff
        sf::Time mStatisticsUpdateTime;
        int mStatisticsNumFrames;
        sf::Text mStatisticsText;
        sf::Font mStatisticsFont;
        bool mStatisticsShowing;

        void updateStatistics(sf::Time elapsedTime);    //updates the statistics


    public:
        App();          //base constructor, TO-DO: Add environmental flags and loading settings from file

        void run();     //starts the main program cycle

};






#endif // APP_HPP
