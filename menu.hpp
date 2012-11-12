#include <iostream>
//#include "screen.hpp"

class Menu : public cScreen
{
private:
    int alpha_max;
    int alpha_div;
    bool playing;
public:
    Menu (void);
    virtual int Run (sf::RenderWindow &App);
};

Menu::Menu (void)
{
    alpha_max = 3*255;
    alpha_div = 3;
    playing = false;
}

int Menu::Run (sf::RenderWindow &App)
{
    sf::Event Event;
    bool Running = true;
    sf::Texture Image;
    sf::Sprite Sprite;
    int alpha = 0;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    int menu = 0;

    if (!Image.loadFromFile("resources/presentation.png"))
    {
        std::cerr<<"Error loading presentation.gif"<<std::endl;
        return (-1);
    }
	Sprite.setTexture(Image);
    Sprite.setColor(sf::Color(255, 255, 255, alpha));
    if (!Font.loadFromFile("resources/verdanab.ttf"))
    {
        std::cerr<<"Error loading verdanab.ttf"<<std::endl;
        return (-1);
    }
    Menu1.setFont(Font);
	Menu1.setCharacterSize(20);
	Menu1.setString("Play");
	Menu1.setPosition(280,160);
    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Exit");
    Menu2.setPosition(280,220);
    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Continue");
    Menu3.setPosition(280,160);

    //Clearing screen
   // App.Clear();

    if (playing)
    {
        alpha = alpha_max;
    }

    while (Running)
    {
        //Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Up:
                        menu = 0;
                        break;
                    case sf::Keyboard::Down:
                        menu = 1;
                        break;
                    case sf::Keyboard::Return:
                        if (menu==0)
                        {
                            //Let's get play !
                            playing = true;
                            return (1);
                        }
                        else
                        {
                            //Let's get work...
                            return (-1);
                        }
                        break;
					case sf::Keyboard::Escape:
							  if(playing) return (1);
							  else return(-1);
						break;
                    default :
                        break;
                }
            }
        }
        //When getting at alpha_max, we stop modifying the sprite
        if (alpha<alpha_max)
        {
            alpha=alpha+10;
			if(alpha>alpha_max) alpha=alpha_max;
        }
        Sprite.setColor(sf::Color(255, 255, 255, alpha/alpha_div));
        if (menu==0)
        {
            Menu1.setColor(sf::Color(255, 0, 0, 255));
            Menu2.setColor(sf::Color(255, 255, 255, 255));
            Menu3.setColor(sf::Color(255, 0, 0, 255));
        }
        else
        {
            Menu1.setColor(sf::Color(255, 255, 255, 255));
            Menu2.setColor(sf::Color(255, 0, 0, 255));
            Menu3.setColor(sf::Color(255, 255, 255, 255));
        }

        //Drawing
        App.draw(Sprite);
        if (alpha==alpha_max)
        {
            if (playing)
            {
                App.draw(Menu3);
            }
            else
            {
                App.draw(Menu1);
            }
            App.draw(Menu2);
        }
        App.display();
		App.clear();
    }

    //Never reaching this point normally, but just in case, exit the application
    return (-1);
}