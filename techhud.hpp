#ifndef TECHHUD_HPP_INCLUDED
#define TECHHUD_HPP_INCLUDED

class TechHUD{
public:
	
	void pokazHUD(sf::Clock &zegar, sf::RenderWindow &Window, float posx=0, float posy=0, float zmienna1=0, float zmienna2=0, float zmienna3=0, float zmienna4=0, float zmienna5=0);
	  TechHUD();
	  
private:
		  sf::Text zmienna[5];
		  sf::Text hud1,hud2,hud3;
		  sf::Color color;
	float fps;
	int czas[3];
	float czas_tmp;
	   sf::Clock clockfps;
	void liczCzas(sf::Clock &zegar);
	void liczFps();
	template <class T> std::string static ToString(const T& t);
	// Declare a new font
	sf::Font font;

	

};

#endif	 TECHHUD_HPP_INCLUDED