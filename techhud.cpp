#include <SFML/Graphics.hpp>
#include <sstream>
#include "techhud.hpp"


TechHUD::TechHUD()
{	   

	// Load it from a file
	if (!font.loadFromFile("resources/arial.ttf"))
	{
		
	}
	czas_tmp=0;
	czas[0]=0;
	czas[1]=0;
	czas[2]=0;
	fps=0;
	color = sf::Color::White;//kolor
	hud2.setFont(font);
	hud2.setCharacterSize(15);
	hud2.setColor(color);
	hud2.setPosition(0,15);
	hud3.setFont(font);
	hud3.setCharacterSize(15);
	hud3.setColor(color);
	hud3.setPosition(0,30);

	zmienna[0].setFont(font);
	zmienna[0].setCharacterSize(15);
	zmienna[0].setColor(color);
	zmienna[0].setPosition(0,45);
	zmienna[1].setFont(font);
	zmienna[1].setCharacterSize(15);
	zmienna[1].setColor(color);
	zmienna[1].setPosition(0,60);
	zmienna[2].setFont(font);
	zmienna[2].setCharacterSize(15);
	zmienna[2].setColor(color);
	zmienna[2].setPosition(0,75);
	zmienna[3].setFont(font);
	zmienna[3].setCharacterSize(15);
	zmienna[3].setColor(color);
	zmienna[3].setPosition(0,90);
	zmienna[4].setFont(font);
	zmienna[4].setCharacterSize(15);
	zmienna[4].setColor(color);
	zmienna[4].setPosition(0,105);

}
void TechHUD::liczFps()
{

	fps = clockfps.getElapsedTime().asSeconds();
	if(fps)
		fps = 1/fps;
	clockfps.restart();


}

void TechHUD::pokazHUD(sf::Clock &zegar, sf::RenderWindow &Window, float posx, float posy, float zmienna1, float zmienna2, float zmienna3, float zmienna4, float zmienna5)
{			
	// Load it from a file
	if (!font.loadFromFile("resources/arial.ttf"))
	{
		
	}
	liczFps();
	hud1.setString("FPS: "+ ToString<int>(fps));
	hud1.setFont(font);
	hud1.setCharacterSize(15);
	hud1.setColor(color);
	Window.draw(hud1);
	hud2.setString("X: " + ToString<int>(posx) + " Y: " + ToString<int>(posy));

	Window.draw(hud2);
	liczCzas(zegar);
	hud3.setString("Czas: " + ToString<int>(czas[0]) + ":" + ToString<int>(czas[1]) + ":" + ToString<int>(czas[2]));

	Window.draw(hud3);
	if(zmienna1){

		zmienna[0].setString("a: " + ToString<float>(zmienna1));
		zmienna[1].setString("b: " + ToString<float>(zmienna2));
		zmienna[2].setString("c: " + ToString<float>(zmienna3));
		zmienna[3].setString("d: " + ToString<float>(zmienna4));
		zmienna[4].setString("e: " + ToString<float>(zmienna5)); 
		for(int i=0;i<5;i++)
			Window.draw(zmienna[i]);
	}
}
void TechHUD::liczCzas(sf::Clock &zegar)
{			  
	if(zegar.getElapsedTime().asSeconds()>=1.0f){
		zegar.restart();
		czas[2]++;			  }
	if(czas[2]>60){czas[1]++; czas[2]=0;}
	if(czas[1]>60){czas[0]++; czas[1]=0;}

}
template <class T> std::string static TechHUD::ToString(const T& t) 
{ 
	std::ostringstream oss; 
	oss << t; 
	return oss.str();
}
