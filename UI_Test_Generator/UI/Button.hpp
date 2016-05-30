#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

#include "../StringHelpers.hpp"

#include <functional>
#include <memory>
#include <string>
#include <vector>

//This is a Button class, containing some sf::Text and a Rectangle for a background
//it's supposed to scale with the window size, which is why those two are mutable(virtual void draw is const)
//has functions for loading parameters, checking if mouse is hovered and/or clicked and calls its function on its own

namespace UI
{
    class Button : public sf::Drawable, public sf::Transformable
    {
        private:
            int functionID;                     //tells what the function it calls' number is(may change this to string if necessary)
            mutable sf::Font tmpFont;           //a temporary font until the Resource classes are made
            mutable sf::Text mText;             //the text that should be displayed
            sf::FloatRect mButtonSize;          //the size of the button, compared to the entire window
            sf::Color mDefaultColor, mHoverColor, mClickColor;  //the colors of the background, depending on the state of the mouse
            mutable sf::RectangleShape mButtonRect;     //the rectangle for the background

            float mTextRelativeSize;            //tells the height of the text compared to the height of the Rectangle

            enum ButtonState
            {
                Default,
                Hovered,
                Clicked,
            } mButtonState;                 //tells the state of the button in terms of mouse usage



            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;     //draw function
            virtual void onClick();         //derived functions will call this when clicked

        public:
            Button(const sf::Font& testFont, const std::vector<std::wstring> &parameters);      //A basic constructor
            void loadParameters(const std::vector<std::wstring> &parameters);                   //and parameter loader

            void updateMouse(sf::Vector2f mousePosition, bool isClicked);                   //this function is called every time
                                                                                            //the mouse is updated and updates the button's state accordingly

    };


    class RenderButton : public Button
    {
            std::vector<std::wstring> *mSource;             //source for questions
            std::vector<sf::Texture> *mTarget;              //and a vector of Textures for it to render to
            sf::Font *mFont;                                //and a font with which to render

            void renderToTarget();                          //gets called by onClick

        public:
            void setup(std::vector<std::wstring> *source, std::vector<sf::Texture> *target, sf::Font *font);    //setup function
            void onClick();

    };
}





#endif // UI_BUTTON_HPP
