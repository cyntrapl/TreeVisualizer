#include "TreeNode.h"

#include <queue>
#include <SFML/Graphics.hpp>

TreeNode::TreeNode(int val, float x, float y) : value(val), left(nullptr), right(nullptr), position(x, y) {}

PlaceholderNode::PlaceholderNode(float x, float y, bool left) : position(x, y), isLeft(left) {}

void drawTree(sf::RenderWindow& window, TreeNode* node, TreeNode* selectedNode) {
    if (node == nullptr) return;

    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(node->position.x - circle.getRadius(), node->position.y - circle.getRadius());

    if (node == selectedNode) {
        sf::CircleShape border(circle.getRadius() + 2);
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color::Yellow);
        border.setOutlineThickness(2);
        border.setPosition(node->position.x - border.getRadius(), node->position.y - border.getRadius());
        window.draw(border);
    }

    window.draw(circle);

    sf::Font font;
    if (font.loadFromFile("arial.ttf")) {
        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(std::to_string(node->value));
        valueText.setCharacterSize(15);
        valueText.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = valueText.getLocalBounds();
        valueText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        valueText.setPosition(node->position);

        window.draw(valueText);
    }

    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(node->position, sf::Color::White),
            sf::Vertex(node->left->position, sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->left, selectedNode);
    }

    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(node->position, sf::Color::White),
            sf::Vertex(node->right->position, sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->right, selectedNode);
    }
}

void drawPlaceholders(sf::RenderWindow& window, const std::vector<PlaceholderNode>& placeholders) {
    for (const auto& placeholder : placeholders) {
        sf::CircleShape circle(10);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(placeholder.position.x - circle.getRadius(), placeholder.position.y - circle.getRadius());
        window.draw(circle);
    }
}

TreeNode* getNodeAtPosition(TreeNode* node, sf::Vector2f position) {
    if (node == nullptr) return nullptr;

    sf::CircleShape circle(20);
    circle.setPosition(node->position.x - circle.getRadius(), node->position.y - circle.getRadius());

    if (circle.getGlobalBounds().contains(position)) {
        return node;
    }

    TreeNode* foundNode = getNodeAtPosition(node->left, position);
    if (foundNode) return foundNode;

    return getNodeAtPosition(node->right, position);
}

void deleteSubtree(TreeNode* node) {
    if (node == nullptr) return;
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

PlaceholderNode* getPlaceholderAtPosition(const std::vector<PlaceholderNode>& placeholders, sf::Vector2f position) {
    for (const auto& placeholder : placeholders) {
        sf::CircleShape circle(10);
        circle.setPosition(placeholder.position.x - circle.getRadius(), placeholder.position.y - circle.getRadius());

        if (circle.getGlobalBounds().contains(position)) {
            return const_cast<PlaceholderNode*>(&placeholder);
        }
    }
    return nullptr;
}

void deleteNode(TreeNode*& root, TreeNode* nodeToDelete) {
    if (root == nullptr || nodeToDelete == nullptr) return;

    // If the node to delete is the root
    if (root == nodeToDelete) {
        deleteSubtree(root);
        root = nullptr;
        return;
    }

    // Find the parent of the node to delete
    TreeNode* parent = nullptr;
    std::queue<TreeNode*> queue;
    queue.push(root);

    while (!queue.empty()) {
        TreeNode* current = queue.front();
        queue.pop();

        if (current->left == nodeToDelete || current->right == nodeToDelete) {
            parent = current;
            break;
        }

        if (current->left) queue.push(current->left);
        if (current->right) queue.push(current->right);
    }

    if (parent) {
        // Remove the node from its parent's children
        if (parent->left == nodeToDelete) {
            deleteSubtree(parent->left);
            parent->left = nullptr;
        } else if (parent->right == nodeToDelete) {
            deleteSubtree(parent->right);
            parent->right = nullptr;
        }
    }
}