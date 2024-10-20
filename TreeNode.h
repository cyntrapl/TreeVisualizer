#ifndef TREENODE_H
#define TREENODE_H

#include <SFML/Graphics.hpp>
#include <queue>

struct TreeNode {
    int value;
    sf::Vector2f position;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val, float x, float y);
};

struct PlaceholderNode {
    sf::Vector2f position;
    bool isLeft;

    PlaceholderNode(float x, float y, bool left);
};

void deleteNode(TreeNode*& root, TreeNode* nodeToDelete);
void deleteSubtree(TreeNode* node);
TreeNode* getNodeAtPosition(TreeNode* node, sf::Vector2f position);
PlaceholderNode* getPlaceholderAtPosition(const std::vector<PlaceholderNode>& placeholders, sf::Vector2f position);
void drawTree(sf::RenderWindow& window, TreeNode* node, TreeNode* selectedNode);
void drawPlaceholders(sf::RenderWindow& window, const std::vector<PlaceholderNode>& placeholders);

#endif // TREENODE_H