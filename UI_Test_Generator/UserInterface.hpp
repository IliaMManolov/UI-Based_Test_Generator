#ifndef UI_HPP
#define UI_HPP

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"

#include "UI/Button.hpp"

#include <string>
#include <vector>
#include <fstream>


//This is the User Interface class. It's meant to be one big thing, which loads information from its respective design file
//and creates Buttons, Text fields, Scrollable views and displays images. It also handles their functions.

class UserInterface : public sf::Drawable, public sf::Transformable
{

    private:

        std::vector<UI::Button> mButtons;       //The list of all the current view's Buttons
                                                //TO-DO: create all other things

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;         //the draw function

        void getParameters(std::wifstream &stream, std::vector<std::wstring> &parameters);      //a function for getting all parameters from a file stream
                                                                                                //the only error checking it does is empty-line skipping

    public:
        UserInterface()                 //temporary empty constructor for the App constructor, since I need to load the font before calling loadFile
        {
        }
        UserInterface(const sf::Font& testFont, std::string path = "Resources/Default_UI.txt");     //a legit constructor for future use


        void loadFile(const sf::Font& testFont, std::string path);      //a function for loading a file and setting all elements' fonts to testFont

};





#endif // UI_HPP
