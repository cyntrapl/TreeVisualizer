#include "InputBox.h"
#include <cctype>

std::string getInputFromUser(sf::RenderWindow& window, const std::string& prompt) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return "";
    }

    sf::Text promptText(prompt, font, 20);
    promptText.setFillColor(sf::Color::White);

    sf::RectangleShape inputBox(sf::Vector2f(200, 30));
    inputBox.setFillColor(sf::Color::Black);
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);

    sf::Text inputText("", font, 20);
    inputText.setFillColor(sf::Color::White);

    std::string input;
    bool enterPressed = false;

    while (window.isOpen() && !enterPressed) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back();
                } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    input += static_cast<char>(event.text.unicode);
                }
                inputText.setString(input);
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Check if the input is a number
                bool isNumber = !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
                if (isNumber) {
                    enterPressed = true;
                } else {
                    input.clear();
                    inputText.setString(input);
                }
            }
        }

        // Convert the position to the current view coordinates
        sf::Vector2f viewCenter = window.getView().getCenter();
        sf::Vector2f viewSize = window.getView().getSize();
        sf::Vector2f viewTopLeft(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

        promptText.setPosition(viewTopLeft.x + 100, viewTopLeft.y + 100);
        inputBox.setPosition(viewTopLeft.x + 100, viewTopLeft.y + 150);
        inputText.setPosition(viewTopLeft.x + 105, viewTopLeft.y + 155);

        window.clear();
        window.draw(promptText);
        window.draw(inputBox);
        window.draw(inputText);
        window.display();
    }

    return input;
}