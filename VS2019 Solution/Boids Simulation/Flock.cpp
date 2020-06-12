#include "Flock.hpp"

Flock::Flock(sf::RenderWindow& window) : m_window(window)
{
	const int FLOCK_SIZE = 100;

	for (int i = 0; i < FLOCK_SIZE; ++i)
		m_boids.push_back(Boid(m_window, m_boids));

	m_background.setFillColor(sf::Color(50, 50, 50));

	const int SIZE = 2000;

	m_background.setSize(sf::Vector2f(SIZE, SIZE));
}

void Flock::handleEvent(const sf::Event& event)
{
	for (unsigned int i = 0; i < m_boids.size(); ++i)
		m_boids[i].handleEvent(event);
}

void Flock::update()
{
	for (unsigned int i = 0; i < m_boids.size(); ++i)
		m_boids[i].update();
}

void Flock::render()
{
	m_window.draw(m_background);

	for (unsigned int i = 0; i < m_boids.size(); ++i)
		m_boids[i].render();
}