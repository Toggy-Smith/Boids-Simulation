#include "Game.hpp"

Game::Game(sf::RenderWindow& window)
	: window(window), m_flock(window), m_viewManager(window)
{
	///
}

void Game::handleEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		m_viewManager.handleEvent(event);

		m_flock.handleEvent(event);

		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();

				break;
			case sf::Event::Resized:
				sf::View view = window.getView();

				view.setSize((sf::Vector2f) window.getSize());

				window.setView(view);
		}
	}
}

void Game::update()
{
	static float leftOverTime = 0.0f;

	static sf::Clock updateClock;

	const int framesPerSecond = 60;

	leftOverTime += updateClock.getElapsedTime().asSeconds();

	do
	{
		m_flock.update();

		leftOverTime -= 1.0f / framesPerSecond;
	}
	while (leftOverTime >= 1.0f / framesPerSecond);

	updateClock.restart();
}

void Game::render()
{
	window.clear();

	m_flock.render();

	window.display();
}