#include "Controller.h"


Controller::Controller()
	: m_window(sf::VideoMode(1000, 1000), "Super Mario", sf::Style::Close)
{

}

void Controller::run()
{

	Menu menu(1000, 1000);

	menu.draw(m_window);

	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))//WAIT FOR EVENT
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				break;
			}

			if (menu.options(event, m_window))
				Board b(m_window, event, m_winner, m_loser);

			if (m_winner)
			{
				menu.end(m_window);
				m_winner = false;
			}

			if (m_loser)
			{
				menu.lose(m_window);
				m_loser = false;
			}
		}
	}
}
