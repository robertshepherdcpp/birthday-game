#include <SFML/Graphics.hpp>

#include<random>
#include<vector>
#include<chrono>
#include<iostream>

#include"Balloon.h"

using namespace std::chrono_literals;

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Birthday game");

    std::chrono::system_clock::time_point last = std::chrono::system_clock::now();

    std::vector<Balloon> balloons{};

    int score = 0;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> colour_balloon(1, 4);

    std::random_device dev2;
    std::mt19937 rng2(dev2());
    std::uniform_int_distribution<std::mt19937::result_type> x_coord(1, 450);

    bool should_add_another = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // need to find position of mouse relative to the rest of the window
                // then see if a sprite has been clicked.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);
                    for (auto& x : balloons)
                    {
                        if (x.c.getGlobalBounds().contains(worldPos)) {
                            x.die();
                            score += 1;
                            std::cout << score << "\n";
                        }
                    }
                    should_add_another = true;
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "new ballooon\n";
                    int what_type = colour_balloon(rng);
                    int what_x = x_coord(rng2);
                    if (what_type == 2)
                        balloons.push_back(Balloon{ sf::Color::Red , sf::Vector2f(what_x, 450) });
                    if (what_type == 3)
                        balloons.push_back(Balloon{ sf::Color::Green, sf::Vector2f(what_x, 450) });
                    else
                        balloons.push_back(Balloon{ sf::Color::Blue , sf::Vector2f(what_x, 450) });
                    last = std::chrono::system_clock::now();
                    std::cout << what_x << ", " << 450 << '\n';
                }
            }
        }

        if (should_add_another)
        {
            std::cout << "new ballooon\n";
            int what_type = colour_balloon(rng);
            int what_x = x_coord(rng2);
            if (what_type == 1)
                balloons.push_back(Balloon{ sf::Color::Red , sf::Vector2f(what_x, 450) });
            if (what_type == 2)
                balloons.push_back(Balloon{ sf::Color::Green, sf::Vector2f(what_x, 450) });
            else
                balloons.push_back(Balloon{ sf::Color::Blue , sf::Vector2f(what_x, 450) });
            last = std::chrono::system_clock::now();
            std::cout << what_x << ", " << 450 << '\n';
            should_add_another = false;
        }

        if (std::chrono::system_clock::now() - last >= 0.0025s)
        {
            for (auto& x : balloons)
            {
                x.move_up();
            }
            last = std::chrono::system_clock::now();
        }
        

        window.clear();
        for (auto& x : balloons)
        {
            x.print(window);
        }
        window.display();
    }

    return 0;
}