#include "UserInterface.hpp"

#include <iostream>


UserInterface::UserInterface(const sf::Font& testFont, std::string path)
: mButtons()
{
    loadFile(testFont, path);

}


void UserInterface::loadFile(const sf::Font& testFont, std::string path)
{
    std::wifstream file(path);
    std::wstring currLine;

    while (std::getline(file, currLine))
    {
        if (currLine == L"Button")              //loading Buttons
        {
            std::vector<std::wstring> buttonParameters;
            getParameters(file, buttonParameters);

            mButtons.push_back(UI::Button(testFont, buttonParameters));
        }
                                                //TO-DO: add loading of other elements
        else                                    //if there's a typo, the element is skipped
        {
            std::wcout<<"Invalid element: "<<currLine<<std::endl;
            std::vector<std::wstring> errorParameters;
            getParameters(file, errorParameters);

            std::wcout<<"Invalid parameters: "<<std::endl;
            for (size_t i=0;i<errorParameters.size();i++)
                std::wcout<<errorParameters[i]<<std::endl;
        }
    }
}

void UserInterface::getParameters(std::wifstream &stream, std::vector<std::wstring> &parameters)    //pretty obvious
{
    std::wstring currLine;

    std::getline(stream, currLine);
    while (currLine != L"end")
    {
        if (currLine != L"")
            parameters.push_back(currLine);

        std::getline(stream, currLine);
    }
}

void UserInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const       //draws all UI elements
{
    states.transform *= getTransform();

    for (int i=0;i<mButtons.size();i++)             //this draws all Buttons
        target.draw(mButtons[i], states);

                                                    //TO-DO: add drawing Text Fields and other elements

}
