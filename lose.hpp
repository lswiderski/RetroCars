class Lose : public cScreen
{
private:
	template <class T> std::string static ToString(const T& t) 
	{ 
		std::ostringstream oss; 
		oss << t; 
		return oss.str();
	}

public:
    Lose (void);
    virtual int Run (sf::RenderWindow &App);
};

Lose::Lose (void)
{

}

int Lose::Run (sf::RenderWindow &App)
{
	  sf::Event Event;
    bool Running = true;
    sf::Texture Image;
    sf::Sprite Sprite;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
	sf::Text pkt;
    int menu = 0;

    if (!Image.loadFromFile("resources/presentation.png"))
    {
        std::cerr<<"Error loading presentation.gif"<<std::endl;
        return (-1);
    }
	Sprite.setTexture(Image);
    Sprite.setColor(sf::Color(255, 255, 255));
    if (!Font.loadFromFile("resources/verdanab.ttf"))
    {
        std::cerr<<"Error loading verdanab.ttf"<<std::endl;
        return (-1);
    }
    Menu1.setFont(Font);
	Menu1.setCharacterSize(20);
	Menu1.setString("Restart");
	Menu1.setPosition(280,220);
    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Exit");
    Menu2.setPosition(280,280);
	pkt.setFont(Font);
	pkt.setCharacterSize(20);
	pkt.setString("Score: "+ ToString(Game::pkt));
	pkt.setPosition(280,160);
	pkt.setColor(sf::Color::White);

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
                           Game::pkt=0;
                            return (1);
                        }
                        else
                        {
                            //Let's get work...
                            return (-1);
                        }
                        break;
					case sf::Keyboard::Escape:
								return(-1);
						break;
                    default :
                        break;
                }
            }
        }
        //When getting at alpha_max, we stop modifying the sprite
        
        if (menu==0)
        {
            Menu1.setColor(sf::Color(255, 0, 0, 255));
            Menu2.setColor(sf::Color(255, 255, 255, 255));
           
        }
        else
        {
            Menu1.setColor(sf::Color(255, 255, 255, 255));
            Menu2.setColor(sf::Color(255, 0, 0, 255));
            ;
        }

        //Drawing
        App.draw(Sprite);
       
                App.draw(Menu1);
            
            App.draw(Menu2);
       App.draw(pkt);
        App.display();
		App.clear();
    }

    //Never reaching this point normally, but just in case, exit the application
    return (-1);
}