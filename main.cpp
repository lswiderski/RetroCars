/* created by Neufrin.com */
#include <fstream>
#include <iostream>
#include <sfml/Graphics.hpp>


#include "screens.hpp"

int main(int argc, char** argv)
{	std::srand(static_cast<unsigned int>(std::time(NULL)));
    //Applications variables
    std::vector<cScreen*> Screens;
    int screen = 0;

    //Window creation
    sf::RenderWindow App(sf::VideoMode(640, 480, 32), "Retro Cars");
	App.setFramerateLimit(60);
    //Mouse cursor no more visible
    App.setMouseCursorVisible(false);

    //Screens preparations
    Menu s0;
    Screens.push_back (&s0);
    Game s1;
    Screens.push_back (&s1);
	Lose s2;
	Screens.push_back (&s2);

    //Main loop
    while (screen >= 0)
    {
        screen = Screens[screen]->Run(App);
    }

    return EXIT_SUCCESS;
}