#ifndef TREENODE_H
#define TREENODE_H

#include <SFML/Graphics.hpp>

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

#endif // TREENODE_H