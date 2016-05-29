#include "App.hpp"
#include "StringHelpers.hpp"

App::App()
: mWindow(sf::VideoMode(960, 540), "UI-Based test generator")       //window constructor
, mTimePerFrame(sf::seconds(1/60.f))                                //sets framerate
, mUI()                                                             //loads an empty UI


//Statistics stuff
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mStatisticsText()
, mStatisticsFont()
, mStatisticsShowing(true)
{


    //Statistics stuff
    mStatisticsFont.loadFromFile("Resources/Sansation.ttf");
	mStatisticsText.setFont(mStatisticsFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
	//mStatisticsText.setColor(sf::Color::White);

	mUI.loadFile(mStatisticsFont, "Resources/Default_UI.txt");          //loads the UI and forces all buttons to use the statistics font
                                                                        //(until I get the Resources classes working)
}

void App::run()
{
    sf::Clock clock;                                            //frame limiter
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > mTimePerFrame)             //keeping up with the input
		{
			timeSinceLastUpdate -= mTimePerFrame;

			handleEvents();
			update(mTimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();                                               //final rendering
	}
}




void App::handleEvents()
{
    sf::Event currentEvent;
    while (mWindow.pollEvent(currentEvent))
    {
        switch (currentEvent.type)
        {
            case sf::Event::Closed:                             //to close the window
                mWindow.close();
                break;
            case sf::Event::KeyReleased:                        //to toggle statistics
                if (currentEvent.key.code == sf::Keyboard::F3)
                    mStatisticsShowing = !mStatisticsShowing;
                                                                //TO-DO: Add mouse events
                                                                //TO-DO: Add keyboard events
            default:
                break;
        }
    }

                                                                //TO-DO: Add mouse position events
}


void App::update(sf::Time deltaTime)                            //TO-DO: Add animations
{

}


void App::render()                                              //rendering is done here and it works well as it is
{
    mWindow.clear();

    mWindow.draw(mUI);


    if (mStatisticsShowing)
        mWindow.draw(mStatisticsText);

    mWindow.display();
}






void App::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			L"Frames / Second = " + toString(mStatisticsNumFrames) + L"\n" +
			L"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + L"us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}
