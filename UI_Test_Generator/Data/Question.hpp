#ifndef DATA_QUESTION_HPP
#define DATA_QUESTION_HPP


#include <vector>
#include <string>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace Data
{

    //This is a class, which holds Question data and is capable of drawing it on a RenderTexture

    class Question
    {
        private:
            std::wstring mStatement;
            std::vector<std::wstring> mAnswers;
            enum QType
            {
                Undefined,
                Multiple_Choice,
                Open,
                Final,
            } mType;

        public:
            Question();

            void setStatement(int type, const std::wstring& statement);
            void addAnswer(const std::wstring& answer);

            void clear();       //resets the question's state

            bool incomplete();      //tells whether the question is properly defined

            void render(sf::Vector2f position, sf::Font *font, sf::RenderTexture &target);      //renders the question to target
            float expectedHeight(sf::Font *font);       //tells how high the question is expected to be

    };
}




#endif // DATA_QUESTION_HPP
