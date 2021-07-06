#include <SFML/Graphics.hpp>
#include <iostream>
#include "Field.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML window");
    Field f;
    f.draw(window);
    window.setFramerateLimit(0); //2
    f.prims_alg(window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
    }

	return 0;
}