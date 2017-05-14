#include <SFML/Graphics.hpp>
#include "../include/Flock.h"
#include "../include/NewVector.h"
#include <iostream>
#include <cassert>

int main () {
	const int gameWidth = 800;
	const int gameHeight = 600;

	std::srand (static_cast<unsigned int>(std::time (NULL)));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window (sf::VideoMode (gameWidth, gameHeight), "Flocking", sf::Style::Default, settings);
	sf::Clock clock;

	// load fonts
	sf::Font fontHNL;
	assert (fontHNL.loadFromFile ("static/font/HelveticaNeue Light.ttf"));

	// draw the background of text field on the top
	sf::RectangleShape textField;
	textField.setFillColor (sf::Color::Black);
	textField.setSize (sf::Vector2f (gameWidth, 30.f));
	textField.setPosition (0, 0);

	// display the text
	sf::Text statsText;
	statsText.setFont (fontHNL);
	statsText.setCharacterSize (20);
	statsText.setFillColor (sf::Color::Green);
	statsText.setPosition (5, 5);

	Flock boids;

	while (window.isOpen ()) {
		sf::Event event;	
		sf::Vector2i mouse = sf::Mouse::getPosition (window);

		while (window.pollEvent (event)) {
			if (event.type == sf::Event::Closed) {
				window.close ();
			}

			if ((event.type == sf::Event::KeyPressed)) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close ();
				} else if (event.key.code == sf::Keyboard::Down) {
					boids.reduceBoid ();
				}
			}
			
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					boids.addBoid (sf::Vector2f (event.mouseButton.x, event.mouseButton.y));
				}
			}
		}

		boids.update ();
		statsText.setString ("fps: " + std::to_string (static_cast<int>(1.f / clock.restart ().asSeconds ()))
		+ " amount: " + std::to_string (boids.getCount ()));

		window.clear ();
		window.draw (boids);
		window.draw (textField);
		window.draw (statsText);
		window.display ();
	}

	return 0;
}
