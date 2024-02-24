#include "Balloon.h"

Balloon::Balloon(sf::Color ch, sf::Vector2f pos)
{
	c.setFillColor(ch);
	c.setPosition(pos);
}

auto Balloon::move_up() -> void
{
	c.setPosition(c.getPosition().x, c.getPosition().y - 1);
	if (c.getPosition().y <= 0)
	{
		is_dead = true;
	}
}

auto Balloon::print(sf::RenderWindow& w) -> void
{
	if (!is_dead)
	{
		w.draw(c);
	}
}

auto Balloon::die() -> void
{
	is_dead = true;
}
