#pragma once

#include "SFML/Graphics.hpp"
#include "svl.hpp"

#include <cmath>
#include <random>
#include <vector>

class Boid
{
	private:
		sf::RenderWindow& m_window;

		std::vector<Boid>& m_boids;

		//sf::CircleShape m_triangle;

		const float m_BASE = 10.0f;
		const float m_HEIGHT = 30.0f;

		sf::VertexArray m_triangle = sf::VertexArray(sf::Triangles, 3);

		const float m_MAX_SPEED = 1.5f;

		const float m_PERCEPTION_RADIUS = 50.0f;

		const float m_MAX_FORCE = 0.02f;

		const int m_BOUNDS = 2000;

	public:
		Boid(sf::RenderWindow&, std::vector<Boid>&);

		void handleEvent(const sf::Event&);
		svl::Vector2f align();
		svl::Vector2f cohere();
		svl::Vector2f separate();
		void flock();
		void update();
		void render();

		svl::Vector2f m_position;
		svl::Vector2f m_velocity;
		svl::Vector2f m_acceleration;
};