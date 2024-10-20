#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SFML/Graphics.hpp>
#include <string>

std::string getInputFromUser(sf::RenderWindow& window, const std::string& prompt);

#endif // INPUTBOX_H