#include "Boid.hpp"

Boid::Boid(sf::RenderWindow& window, std::vector<Boid>& boids)
	: m_window(window), m_boids(boids)
{
	// Shape setup
	m_triangle[0].color = sf::Color::White;
	m_triangle[1].color = sf::Color::White;
	m_triangle[2].color = sf::Color::White;


	// Position
	const int DISTRIBUTION_SIZE = m_BOUNDS;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> positionDist(0, DISTRIBUTION_SIZE);

	m_position = svl::Vector2f((float) positionDist(mt), (float)positionDist(mt));


	// Velocity
	const float VELOCITY_RANGE = 0.5f;
	const float MIN_VELOCITY = 0.1f;

	std::uniform_real_distribution<float> directionDist(-1, 1);
	std::uniform_real_distribution<float> velocityDist(MIN_VELOCITY, VELOCITY_RANGE);

	float directionX = 0;
	float directionY = 0;

	do
	{
		directionX = directionDist(mt);
	} while (directionX == 0);

	do
	{
		directionY = directionDist(mt);
	} while (directionY == 0);

	m_velocity = svl::Vector2f(directionX, directionY);
	
	m_velocity.normalize();
		
	m_velocity.setMagnitude(velocityDist(mt));
}

void Boid::handleEvent(const sf::Event& event)
{
	///
}

svl::Vector2f Boid::align()
{
	svl::Vector2f steering;

	unsigned int total = 0;

	for (unsigned int i = 0; i < m_boids.size(); ++i)
	{
		if (&m_boids[i] != this)
		{
			float distanceBetween = std::sqrt(
			                        std::pow(m_position.x - m_boids[i].m_position.x, 2)
			                        +
			                        std::pow(m_position.y - m_boids[i].m_position.y, 2));

			if (distanceBetween > m_PERCEPTION_RADIUS)
				continue;

			steering += m_boids[i].m_velocity;

			total++;
		}
	}

	if (total > 0)
	{
		steering /= total;

		steering.setMagnitude(m_MAX_SPEED);

		steering -= m_velocity;

		if (steering.getMagnitude() > m_MAX_FORCE)
		{
			steering.setMagnitude(m_MAX_FORCE);
		}
	}
	
	return steering;
}

svl::Vector2f Boid::cohere()
{
	svl::Vector2f steering;

	unsigned int total = 0;

	for (unsigned int i = 0; i < m_boids.size(); ++i)
	{
		if (&m_boids[i] != this)
		{
			float distanceBetween = std::sqrt(
				std::pow(m_position.x - m_boids[i].m_position.x, 2)
				+
				std::pow(m_position.y - m_boids[i].m_position.y, 2));

			if (distanceBetween > m_PERCEPTION_RADIUS)
				continue;

			steering += m_boids[i].m_position;

			total++;
		}
	}

	if (total > 0)
	{
		steering /= total;

		steering -= m_position;

		steering.setMagnitude(m_MAX_SPEED);

		steering -= m_velocity;

		if (steering.getMagnitude() > m_MAX_FORCE)
		{
			steering.setMagnitude(m_MAX_FORCE);
		}
	}

	return steering;
}

svl::Vector2f Boid::separate()
{
	svl::Vector2f steering;

	unsigned int total = 0;

	for (unsigned int i = 0; i < m_boids.size(); ++i)
	{
		if (&m_boids[i] != this)
		{
			float distanceBetween = std::sqrt(
				std::pow(m_position.x - m_boids[i].m_position.x, 2)
				+
				std::pow(m_position.y - m_boids[i].m_position.y, 2));

			if (distanceBetween > m_PERCEPTION_RADIUS)
				continue;

			svl::Vector2f diff = m_position - m_boids[i].m_position;

			diff /= std::pow(distanceBetween, 2);

			steering += diff;

			total++;
		}
	}

	if (total > 0)
	{
		steering /= total;

		steering.setMagnitude(m_MAX_SPEED);

		steering -= m_velocity;

		if (steering.getMagnitude() > m_MAX_FORCE)
		{
			steering.setMagnitude(m_MAX_FORCE);
		}
	}

	return steering;
}

void Boid::flock()
{
	svl::Vector2f alignment = align();
	svl::Vector2f cohesion = cohere();
	svl::Vector2f separation = separate();

	m_acceleration = alignment + cohesion + separation;
}

void Boid::update()
{
	// Behaviours
	flock();

	// Handle velocity
	m_position += m_velocity;

	if (m_position.x < 0)
	{
		m_position.x = (float) m_BOUNDS;
	}
	else if (m_position.x > m_BOUNDS)
	{
		m_position.x = 0;
	}

	if (m_position.y < 0)
	{
		m_position.y = (float) m_BOUNDS;
	}
	else if (m_position.y > m_BOUNDS)
	{
		m_position.y = 0;
	}

	m_velocity += m_acceleration;

	if (m_velocity.getMagnitude() > m_MAX_SPEED)
		m_velocity.setMagnitude(m_MAX_SPEED);

	// Update shape
	float angleInRadians = std::atan2(m_velocity.y, m_velocity.x);

	float angleInDegrees = angleInRadians * 180.0f / 3.14159f;

	sf::Transform transform;

	transform.rotate(angleInDegrees - 90.0f);

	sf::Vector2f pointA = sf::Vector2f(-m_BASE, -(m_HEIGHT / 2.0f));
	sf::Vector2f pointB = sf::Vector2f(m_BASE, -(m_HEIGHT / 2.0f));
	sf::Vector2f pointC = sf::Vector2f(0.0f, (m_HEIGHT / 2.0f));

	pointA = transform.transformPoint(pointA);
	pointB = transform.transformPoint(pointB);
	pointC = transform.transformPoint(pointC);

	pointA += sf::Vector2f(m_position.x, m_position.y);
	pointB += sf::Vector2f(m_position.x, m_position.y);
	pointC += sf::Vector2f(m_position.x, m_position.y);

	m_triangle[0].position = pointA;
	m_triangle[1].position = pointB;
	m_triangle[2].position = pointC;

	// Reset acceleration
	m_acceleration.setMagnitude(0.0f);
}

void Boid::render()
{
	m_window.draw(m_triangle);
}