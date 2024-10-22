#include <SFML/Graphics.hpp>
#include "TreeNode.h"
#include "InputBox.h"

// Function to find the largest value in the tree
int findLargestValue(TreeNode* node) {
    if (node == nullptr) return 0;
    int leftMax = findLargestValue(node->left);
    int rightMax = findLargestValue(node->right);
    return std::max({node->value, leftMax, rightMax});
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

    // Display the input box at the start
    std::string initialInput = getInputFromUser(window, "Enter initial value:");

    // Initialize the tree with the input value
    int rootValue = initialInput.empty() ? 1 : std::stoi(initialInput);
    auto* root = new TreeNode(rootValue, 400, 50);
    root->left = new TreeNode(2, 300, 150);
    root->right = new TreeNode(3, 500, 150);
    root->left->left = new TreeNode(4, 250, 250);
    root->left->right = new TreeNode(5, 350, 250);
    root->right->left = new TreeNode(6, 450, 250);
    root->right->right = new TreeNode(7, 550, 250);

    sf::View view = window.getDefaultView();
    TreeNode* draggedNode = nullptr;
    TreeNode* selectedNode = nullptr;
    sf::Vector2f dragOffset;
    std::vector<PlaceholderNode> placeholders;

    // Track the largest value in the tree
    int largestValue = findLargestValue(root);

    // Load font and create guide text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1; // Handle error
    }
    sf::Text guideText;
    guideText.setFont(font);
    guideText.setString("Right click - select\nLeft click - drag\nEnter - edit\nDelete - delete");
    guideText.setCharacterSize(15);
    guideText.setFillColor(sf::Color::White);
    guideText.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W)
                    view.move(0, -10);
                if (event.key.code == sf::Keyboard::S)
                    view.move(0, 10);
                if (event.key.code == sf::Keyboard::A)
                    view.move(-10, 0);
                if (event.key.code == sf::Keyboard::D)
                    view.move(10, 0);
                if (event.key.code == sf::Keyboard::Delete && selectedNode) {
                    deleteNode(root, selectedNode);
                    selectedNode = nullptr;
                    placeholders.clear();
                }
                if (event.key.code == sf::Keyboard::Enter && selectedNode) {
                    std::string newValueStr = getInputFromUser(window, "Enter new value for the node:");
                    if (!newValueStr.empty()) {
                        int newValue = std::stoi(newValueStr);
                        selectedNode->value = newValue;
                        largestValue = std::max(largestValue, newValue);
                    }
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    view.zoom(0.9f);
                else
                    view.zoom(1.1f);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
                    draggedNode = getNodeAtPosition(root, mousePos);
                    if (draggedNode) {
                        dragOffset = draggedNode->position - mousePos;
                        placeholders.clear();
                    } else {
                        PlaceholderNode* placeholder = getPlaceholderAtPosition(placeholders, mousePos);
                        if (placeholder && selectedNode) {
                            int newValue = ++largestValue;
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
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
                    selectedNode = getNodeAtPosition(root, mousePos);
                    if (selectedNode) {
                        placeholders.clear();
                        if (!selectedNode->left) {
                            placeholders.emplace_back(selectedNode->position.x - 50, selectedNode->position.y + 100, true);
                        }
                        if (!selectedNode->right) {
                            placeholders.emplace_back(selectedNode->position.x + 50, selectedNode->position.y + 100, false);
                        }
                    } else placeholders.clear();
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    draggedNode = nullptr;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (draggedNode) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
                    draggedNode->position = mousePos + dragOffset;
                }
            }
        }

        window.clear();
        window.setView(view);
        drawTree(window, root, selectedNode);
        drawPlaceholders(window, placeholders);
        window.setView(window.getDefaultView()); // Reset to default view
        window.draw(guideText); // Draw guide text after resetting the view
        window.display();
    }

    return 0;
}