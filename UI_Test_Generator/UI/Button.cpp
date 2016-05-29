#include "Button.hpp"
#include "../Utility/ColorUtility.hpp"

#include <iostream>

UI::Button::Button(const sf::Font& testFont, const std::vector<std::wstring> &parameters)
: functionID(0)                                                     //some default parameters
, tmpFont()
, mText()
, mButtonSize(0.1f, 0.1f, 0.2f, 0.1f)
, mDefaultColor(sf::Color::Red)
, mHoverColor(sf::Color::Blue)
, mClickColor(sf::Color::Green)
, mButtonRect()
, mTextRelativeSize(0.5f)
, mButtonState(ButtonState::Default)
{
    //tmpFont.loadFromFile("Resources/slicer.ttf");
    mText.setFont(testFont);                                //more default parameters
    mText.setString("Sample text");
    mText.setColor(sf::Color::White);

    mButtonRect.setFillColor(mDefaultColor);

    loadParameters(parameters);
}

void UI::Button::loadParameters(const std::vector<std::wstring>& parameters)        //speaking of parameters, this function loads
{                                                                                   //them from a vector of strings, this time with
    for (int i=0;i<parameters.size();i++)                                           //heavy error checking
    {
        std::wstring command = parameters[i].substr(0, parameters[i].find(L' '));

        if (command == L"font")
        {
            //load font from container here
        }
        else if (command == L"string")
        {
            mText.setString(parameters[i].substr(7, parameters[i].size() - 7));
        }
        else if (command == L"text-color")
        {
            std::vector<int> col;
            std::wstring tmp = parameters[i].substr(11, parameters[i].size()-11);

            if (!getColor(col, tmp))
                continue;

            if (col.size()>=4)
                mText.setColor(sf::Color(col[0], col[1], col[2], col[3]));
            else
                mText.setColor(sf::Color(col[0], col[1], col[2]));
        }
    }
}

void UI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const          //and the drawing function with scaling
{
    states.transform *= getTransform();

    sf::Vector2f tmp = sf::Vector2f(target.getView().getSize().x * mButtonSize.width, target.getView().getSize().y * mButtonSize.height);
    //the above line is fucking ridiculous, getSize should be part of RenderTarget, it should't make me go through several class functions
    mButtonRect.setSize(tmp);
    mButtonRect.setPosition(target.getView().getSize().x * mButtonSize.left, target.getView().getSize().y * mButtonSize.top);
    //this one is the same


    mText.setCharacterSize(mButtonRect.getSize().y * mTextRelativeSize);
    mText.setPosition(mButtonRect.getPosition().x + mButtonRect.getSize().x/2.f - mText.getLocalBounds().width/2.f,     //here I center the text
                      mButtonRect.getPosition().y + mButtonRect.getSize().y/2.f - mText.getLocalBounds().height/1.25f); //note: text is actually
                                                                                                                        //taller than I expected,
                                                                                                                        //so it's centered a bit
                                                                                                                        //upwards

    target.draw(mButtonRect, states);
    target.draw(mText, states);
}
