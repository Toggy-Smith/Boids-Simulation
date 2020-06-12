#include "ViewManager.hpp"

ViewManager::ViewManager(sf::RenderWindow& window) : m_window(window)
{
	sf::View view;

	view.setCenter(m_viewPosition);

	window.setView(view);

	adjustView();
}

void ViewManager::adjustView()
{
	sf::View view = m_window.getView();

	view.setCenter(m_viewPosition);
	view.setSize((sf::Vector2f) m_window.getSize() * m_currentZoomLevel);

	m_window.setView(view);
}

void ViewManager::handleEvent(const sf::Event& event)
{
	/* Resizing */
	if (event.type == sf::Event::Resized)
	{
		adjustView();
	}

	/* Zooming */
	else if (event.type == sf::Event::MouseWheelMoved)
	{
		int nMouseWheelTicks = event.mouseWheel.delta;

		float zoomChangeAmount = nMouseWheelTicks * m_ZOOM_PER_MOUSE_TICK;

		zoomChangeAmount = -zoomChangeAmount; // CLARIFY: Reverse direction so it acts in a more "intuitive" manner

		m_currentZoomLevel += zoomChangeAmount;

		if (m_currentZoomLevel < m_MIN_ZOOM_LEVEL)
			m_currentZoomLevel = m_MIN_ZOOM_LEVEL;

		if (m_currentZoomLevel > m_MAX_ZOOM_LEVEL)
			m_currentZoomLevel = m_MAX_ZOOM_LEVEL;

		adjustView();
	}

	/* Panning */
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			m_panMousePosition = sf::Mouse::getPosition(m_window);

			m_isPanning = true;
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		if (m_isPanning)
		{
			sf::Vector2i currentMousePosition = sf::Mouse::getPosition(m_window);

			sf::Vector2i difference = currentMousePosition - m_panMousePosition;
			
			m_viewPosition -= (sf::Vector2f) difference * m_currentZoomLevel;

			adjustView();

			m_panMousePosition = currentMousePosition;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
			m_isPanning = false;
	}

	adjustView();
}