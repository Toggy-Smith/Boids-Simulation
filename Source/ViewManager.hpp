#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>

class ViewManager
{
	private:
		sf::RenderWindow& m_window;

		/* Zoom */
		const float m_ZOOM_PER_MOUSE_TICK = 0.2f;

		float m_currentZoomLevel = 1.0f;

		const float m_MIN_ZOOM_LEVEL = 0.5f;
		const float m_MAX_ZOOM_LEVEL = 2.0f;

		/* Panning */
		bool m_isPanning = false;

		sf::Vector2i m_panMousePosition;

		sf::Vector2f m_viewPosition;

	private:
		void adjustView();

	public:
		ViewManager(sf::RenderWindow&);

		void handleEvent(const sf::Event&);
};