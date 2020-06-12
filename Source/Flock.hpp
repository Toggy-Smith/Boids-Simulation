#pragma once

#include "SFML/Graphics.hpp"

#include "Boid.hpp"

#include <vector>

class Flock
{
	private:
		sf::RenderWindow& m_window;

		std::vector<Boid> m_boids;

		sf::RectangleShape m_background;
	
	public:
		Flock(sf::RenderWindow&);

		void handleEvent(const sf::Event&);
		void update();
		void render();
};