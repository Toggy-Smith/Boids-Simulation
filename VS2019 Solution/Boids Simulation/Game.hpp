#pragma once

#include "SFML/Graphics.hpp"

#include "Flock.hpp"
#include "ViewManager.hpp"

class Game
{
	private:
		sf::RenderWindow& window;

		Flock m_flock;
		ViewManager m_viewManager;

	public:
		     Game         (sf::RenderWindow&);

		void handleEvents ();
		void update       ();
		void render       ();
};