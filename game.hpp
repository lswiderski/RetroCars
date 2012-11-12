#include <iostream>
//#include "screen.hpp"
#include "techhud.hpp"
#include <sstream>

class Game : public cScreen
{
private:
	bool dodac2;
	int dzielnik;
	
	bool dodac;
	sf::Sprite enemy[8];
	int movement_step;
	int posx;
	int posy;
	int speed;
	sf::Sprite gracz;
	sf::Sprite Sprite2;
	sf::Texture Image;
	sf::Text pkty;
	bool hud;
	TechHUD _hud;
	sf::Texture _BG; 
	sf::Sprite map;
	int wyswietlacz;
	sf::Font Font;
	
	int pos1;
	int pos2;
	sf::Event Event;
	bool Running;
	sf::Clock zegarfps;
	sf::Clock predkosc;
	template <class T> std::string static ToString(const T& t) 
	{ 
		std::ostringstream oss; 
		oss << t; 
		return oss.str();
	}
	


public:
	Game (void);
	virtual int Run (sf::RenderWindow &App);
	bool kolizja(sf::Sprite &O1, sf::Sprite &O2);
	void restart();
	static int pkt;
	 
};
int Game::pkt=0;
bool Game::kolizja(sf::Sprite &O1, sf::Sprite &O2)
{
	if(O1.getPosition().x == O2.getPosition().x &&
		(O2.getPosition().y>320	&& O2.getPosition().y<490))
		return true;
	else return false;


}
void Game::restart(){
	dodac2 = true;

	dzielnik=100;
	dodac = false;
	
	movement_step = 50;
	posx = 325;
	speed = 150;
	for(int i=0; i<4;i++)
	{

		enemy[i].setPosition((std::rand()%5+1)*50+175,-100);	}
	for(int i=4; i<8;i++)
	{

		enemy[i].setPosition((std::rand()%5+1)*50+175,-460);	}

	wyswietlacz =0;

	pos1 =0;
	pos2 =0;
	Running = true;

}

Game::Game (void)	
{
	dodac2 = true;
	dzielnik=100;
	dodac = false;
	pkt=0;
	movement_step = 50;
	posx = 325;
	posy = 410;
	speed = 150;
	hud=false;

	//Setting sprite
	if(!Image.loadFromFile("resources/car.png"))
	{ std::cerr<<"Error loading car.png"<<std::endl;
		
	}
	Image.setSmooth(true);
	gracz.setTexture(Image);
	gracz.setOrigin(25,50);


	if(!_BG.loadFromFile("resources/tor.png"))
	{ std::cerr<<"Error loading tor.png"<<std::endl;
		
	}
	map.setTexture(_BG);
	map.setPosition(195,0);


	for(int i=0; i<4;i++)
	{
		enemy[i].setTexture(Image);
		enemy[i].setOrigin(25,50);
		enemy[i].setPosition((std::rand()%5+1)*50+175,-100);
		enemy[i].setRotation(180);	}
	for(int i=4; i<8;i++)
	{
		enemy[i].setTexture(Image);
		enemy[i].setOrigin(25,50);
		enemy[i].setPosition((std::rand()%5+1)*50+175,-460);	
		enemy[i].setRotation(180);
	}
	
	
	Font.loadFromFile("resources/arial.ttf");
	pkty.setFont(Font);
	pkty.setPosition(460,50);
	pkty.setColor(sf::Color::White);
	wyswietlacz =0;

	pos1 =0;
	pos2 =0;
	Running = true;

}


int Game::Run (sf::RenderWindow &App)
{



	predkosc.restart();
	while (Running)
	{	

		pkty.setString("Score: " + ToString<int>(pkt));
		for(int i=0;i<8;i++)
			if(kolizja(gracz,enemy[i]))
			{	 restart();
		return(2);	}


		wyswietlacz++;
		if(wyswietlacz>20)wyswietlacz=0;
		if(!wyswietlacz){
			pos1= enemy[0].getPosition().y;
			pos2=enemy[4].getPosition().y; }

		if(dodac){
			if(pkt%dzielnik==0) {

				if(dodac2){
					speed+=50; dzielnik+=10; dodac2 = false;}
				else dodac2=true;
			}
			dodac = false;

		}

		for(int i=0; i<8; i++)
		{
			enemy[i].move(0, predkosc.getElapsedTime().asSeconds()*speed);

		}
		predkosc.restart();
		if(enemy[0].getPosition().y>530)
		{
			pkt+=10;
			dodac = true;
			
			for(int i=0; i<4; i++)
			{
				enemy[i].setPosition((std::rand()%5+1)*50+175, enemy[4].getPosition().y -360);

			} }
		if(enemy[4].getPosition().y>530)
		{
			pkt+=10;
			dodac = true;
			
			for(int i=4; i<8; i++)
			{
				enemy[i].setPosition((std::rand()%5+1)*50+175, enemy[0].getPosition().y -360);
			}  }

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
				case sf::Keyboard::Escape:
					return (0);
					break; 
				case sf::Keyboard::Left:
					posx -= movement_step;
					break;
				case sf::Keyboard::Right:
					posx += movement_step;
					break;
				case sf::Keyboard::F1:
					if(!hud)
						hud=true;
					else hud=false;
					break;
				default:
					break;
				}
			}
		}

		//Updating
		if (posx>425)
			posx = 425;
		if (posx<225)
			posx = 225;
		gracz.setPosition(posx, posy);


		//Drawing
		App.clear();

		App.draw(map);
		for(int i=0; i<8; i++)
		{
			App.draw(enemy[i]);

		}

		App.draw(gracz);
		App.draw(pkty);
		if(hud)_hud.pokazHUD(zegarfps, App,posx,posy,speed,dzielnik,pkt%dzielnik,abs(pos2-pos1),pkt);
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}