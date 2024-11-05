#include <SFML/Graphics.hpp>
#include "TreeNode.h"
#include "TreeBaseFunctions.h"
#include "TreeManagementFunctions.h"
#include "InputBox.h"
#include <vector>

void handleKeyPress(sf::Event::KeyEvent key, sf::RenderWindow& window, sf::View& view, TreeNode*& root, TreeNode*& selectedNode, std::vector<PlaceholderNode>& placeholders);
void handleMousePress(sf::Event::MouseButtonEvent button, sf::RenderWindow& window, sf::View& view, TreeNode*& root, TreeNode*& draggedNode, TreeNode*& selectedNode, sf::Vector2f& dragOffset, std::vector<PlaceholderNode>& placeholders);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int rootValue = getRandomValue(10, 100);
    std::vector<int> values = {rootValue};

    for (int i = 0; i < 6; ++i) {
        int randomValue = getRandomValue(1, 100);
        values.push_back(randomValue);
    }

    std::sort(values.begin(), values.end());
    TreeNode* root = buildBalancedBST(values, 0, values.size() - 1, 400, 50);

    adjustPositions(root);

    sf::View view = window.getDefaultView();
    TreeNode* draggedNode = nullptr;
    TreeNode* selectedNode = nullptr;
    sf::Vector2f dragOffset;
    std::vector<PlaceholderNode> placeholders;

    int largestValue = findLargestValue(root);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    sf::Text guideText;
    guideText.setFont(font);
    guideText.setString("Right click - select\nLeft click - drag\nEnter - edit\nDelete - delete\nCtrl+S - balance and sort");
    guideText.setCharacterSize(15);
    guideText.setFillColor(sf::Color::White);
    guideText.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                break;
                case sf::Event::KeyPressed:
                    handleKeyPress(event.key, window, view, root, selectedNode, placeholders);
                break;
                case sf::Event::MouseWheelScrolled:
                    if (event.mouseWheelScroll.delta > 0)
                        view.zoom(0.9f);
                    else
                        view.zoom(1.1f);
                break;
                case sf::Event::MouseButtonPressed:
                    handleMousePress(event.mouseButton, window, view, root, draggedNode, selectedNode, dragOffset, placeholders);
                break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        draggedNode = nullptr;
                    }
                break;
                case sf::Event::MouseMoved:
                    if (draggedNode) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
                        draggedNode->position = mousePos + dragOffset;
                    }
                break;
                default:
                    break;
            }
        }

        window.clear();
        window.setView(view);
        drawTree(window, root, selectedNode);
        drawPlaceholders(window, placeholders);
        window.setView(window.getDefaultView());
        window.draw(guideText);
        window.display();
    }

    return 0;
}

// Function definitions
void handleKeyPress(sf::Event::KeyEvent key, sf::RenderWindow& window, sf::View& view, TreeNode*& root, TreeNode*& selectedNode, std::vector<PlaceholderNode>& placeholders) {
    switch (key.code) {
        case sf::Keyboard::W:
            view.move(0, -10);
        break;
        case sf::Keyboard::S:
            if (key.control) {
                std::vector<int> values;
                collectValues(root, values);
                deleteSubtree(root);
                root = nullptr;

                std::sort(values.begin(), values.end());
                root = buildBalancedBST(values, 0, values.size() - 1, 400, 50);
                adjustPositions(root);
            } else {
                view.move(0, 10);
            }
        break;
        case sf::Keyboard::A:
            view.move(-10, 0);
        break;
        case sf::Keyboard::D:
            view.move(10, 0);
        break;
        case sf::Keyboard::Delete:
            if (selectedNode) {
                deleteNode(root, selectedNode);
                selectedNode = nullptr;
                placeholders.clear();
            }
        break;
        case sf::Keyboard::Enter:
            if (selectedNode) {
                std::string newValueStr = getInputFromUser(window, "Enter new value for the node:");
                if (!newValueStr.empty()) {
                    int newValue = std::stoi(newValueStr);
                    selectedNode->value = newValue;
                    int largestValue = std::max(largestValue, newValue);

                    std::vector<int> values;
                    collectValues(root, values);
                    deleteSubtree(root);
                    root = nullptr;

                    std::sort(values.begin(), values.end());
                    root = buildBalancedBST(values, 0, values.size() - 1, 400, 50);
                    adjustPositions(root);
                }
            }
        break;
        default:
            break;
    }
}

void handleMousePress(sf::Event::MouseButtonEvent button, sf::RenderWindow& window, sf::View& view, TreeNode*& root, TreeNode*& draggedNode, TreeNode*& selectedNode, sf::Vector2f& dragOffset, std::vector<PlaceholderNode>& placeholders) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    if (button.button == sf::Mouse::Left) {
        draggedNode = getNodeAtPosition(root, mousePos);
        if (draggedNode) {
            dragOffset = draggedNode->position - mousePos;
            placeholders.clear();
        } else {
            PlaceholderNode* placeholder = getPlaceholderAtPosition(placeholders, mousePos);
            if (placeholder && selectedNode) {
                int newValue = placeholder->isLeft ? selectedNode->value - 1 : selectedNode->value + 1;
                if (placeholder->isLeft) {
                    selectedNode->left = new TreeNode(newValue, placeholder->position.x, placeholder->position.y);
                } else {
                    selectedNode->right = new TreeNode(newValue, placeholder->position.x, placeholder->position.y);
                }
                placeholders.clear();
            } else {
                placeholders.clear();
            }
        }
    } else if (button.button == sf::Mouse::Right) {
        selectedNode = getNodeAtPosition(root, mousePos);
        if (selectedNode) {
            placeholders.clear();
            if (!selectedNode->left) {
                placeholders.emplace_back(selectedNode->position.x - 50, selectedNode->position.y + 100, true);
            }
            if (!selectedNode->right) {
                placeholders.emplace_back(selectedNode->position.x + 50, selectedNode->position.y + 100, false);
            }
        } else {
            placeholders.clear();
        }
    }
}