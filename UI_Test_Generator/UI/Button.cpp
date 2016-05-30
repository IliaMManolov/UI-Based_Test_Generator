#include "Button.hpp"
#include "../Utility/ColorUtility.hpp"
#include "../Data/Question.hpp"

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
    for (size_t i=0;i<parameters.size();i++)                                           //heavy error checking
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

void UI::Button::onClick()
{

}


void UI::RenderButton::setup(std::vector<std::wstring> *source, std::vector<sf::Texture> *target, sf::Font *font)
{
    mSource = source;
    mTarget = target;
    mFont = font;
}

void UI::RenderButton::onClick()
{
    renderToTarget();

}

void UI::RenderButton::renderToTarget()             //this is a complex function - it gets all text, formats it and feeds it to
{                                                   //a vector of questions, clears the sf::Textures vector and renders all the
                                                    //questions to it
    if (mSource == nullptr || mTarget == nullptr || mFont == nullptr)   //if any of the stuff is undefined, we catch the crash
    {                                                                   //and output it as an error
        std::wcout<<L"Error: RenderButton not set up..."<<std::endl;
        return ;
    }

    std::vector<Data::Question> tmpQuestions;
    Data::Question currQuestion;
    std::vector<std::wstring> tmpLines;

    for (size_t i=0;i<mSource->size();i++)          //reading all the lines
    {
        if ((*mSource)[i] == L"")                   //if we have an empty line
        {
            continue;
        }

        if ((*mSource)[i][0] == L'Q')               //if it's a statement
        {
            if (!currQuestion.incomplete())         //error handling before adding the last question
            {
                tmpQuestions.push_back(currQuestion);
            }
            currQuestion.clear();
            std::wstring tmpStatement;
            tmpStatement = (*mSource)[i].substr(3, (*mSource)[i].size()-3);
            i++;
            while (i<mSource->size() && (*mSource)[i].substr(0, 3) == L"   ")       //concatenate every line of the statement in
            {                                                                       //one
                tmpStatement += L'\n';
                tmpStatement += (*mSource)[i].substr(3, (*mSource)[i].size()-3);
            }
            i--;                                        //off-by-one error handling
            currQuestion.setStatement(0, tmpStatement);
        }
        else if ((*mSource)[i][0] == L'C' || (*mSource)[i][0] == L'F')              //adding a multiple-choice answer
        {
            currQuestion.addAnswer((*mSource)[i]);
        }
        else if ((*mSource)[i][0] == L'O')              //adding an open question
        {
            if (!currQuestion.incomplete())
            {
                tmpQuestions.push_back(currQuestion);
            }
            currQuestion.clear();

            std::wstring tmpStatement;
            tmpStatement = (*mSource)[i].substr(3, (*mSource)[i].size()-3);
            i++;
            while (i<mSource->size() && (*mSource)[i].substr(0, 3) == L"   ")
            {
                tmpStatement += L'\n';
                tmpStatement += (*mSource)[i].substr(3, (*mSource)[i].size()-3);
            }

            currQuestion.setStatement(1, tmpStatement);
        }
        else if ((*mSource)[i][0] == L'A')              //adding a open answer
        {
            currQuestion.addAnswer((*mSource)[i]);
        }
        else                                            //catching false commands
        {
            std::wcout<<"Unknown test detail, skipping..."<<std::endl;
        }
    }

    sf::RenderTexture renderTexture;                //we render on this RenderTexture and save it to the vector of Texture
    renderTexture.create(2480, 3508);

    mTarget->clear();

    sf::Vector2f drawingPosition = sf::Vector2f(160, 700);  //sets the upper-left corner of everything we draw

    for (int i=0;i<tmpQuestions.size();i++)
    {
        if (drawingPosition.y + tmpQuestions[i].expectedHeight(mFont)>3350.f)       //if we go off on a new page
        {
            drawingPosition = sf::Vector2f(160, 700);               //we reset the position
            mTarget->push_back(renderTexture.getTexture());         //add the current page to the vector
            renderTexture.clear();                                  //and clear it
        }
        tmpQuestions[i].render(drawingPosition, mFont, renderTexture);  //here we draw the current question
    }
}
