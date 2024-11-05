#include "TreeManagementFunctions.h"
#include <queue>
#include <cmath>

void adjustPositions(TreeNode* root) {
    if (!root) return;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<TreeNode*> levelNodes;

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            levelNodes.push_back(node);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        for (size_t i = 0; i < levelNodes.size(); ++i) {
            for (size_t j = i + 1; j < levelNodes.size(); ++j) {
                if (std::abs(levelNodes[i]->position.x - levelNodes[j]->position.x) < 50) {
                    levelNodes[i]->position.x -= 25;
                    levelNodes[j]->position.x += 25;
                }
            }
        }
    }
}

TreeNode* buildBalancedBST(std::vector<int>& values, int start, int end, float x, float y) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    TreeNode* node = new TreeNode(values[mid], x, y);

    node->left = buildBalancedBST(values, start, mid - 1, x - 50, y + 100);
    node->right = buildBalancedBST(values, mid + 1, end, x + 50, y + 100);

    return node;
}

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