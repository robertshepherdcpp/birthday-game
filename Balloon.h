#include<SFML/Graphics.hpp>

struct Balloon
{
	Balloon(sf::Color c, sf::Vector2f pos);

	auto move_up() -> void;
	auto print(sf::RenderWindow& w) -> void;
	auto die()->void;

	sf::CircleShape c{ 12 };
	bool is_dead = false;
};