#ifndef TREEMANAGEMENTFUNCTIONS_H
#define TREEMANAGEMENTFUNCTIONS_H

#include "TreeNode.h"
#include <vector>
#include <SFML/Graphics.hpp>

void adjustPositions(TreeNode* root);
TreeNode* buildBalancedBST(std::vector<int>& values, int start, int end, float x, float y);
void drawTree(sf::RenderWindow& window, TreeNode* node, TreeNode* selectedNode);
void drawPlaceholders(sf::RenderWindow& window, const std::vector<PlaceholderNode>& placeholders);

#endif // TREEMANAGEMENTFUNCTIONS_H