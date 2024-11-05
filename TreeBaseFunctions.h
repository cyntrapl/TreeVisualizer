#ifndef TREEBASEFUNCTIONS_H
#define TREEBASEFUNCTIONS_H

#include "TreeNode.h"
#include <vector>

int findLargestValue(TreeNode* node);
bool valueExists(TreeNode* node, int value);
void collectValues(TreeNode* node, std::vector<int>& values);
TreeNode* insertBST(TreeNode* node, int value, float x, float y);
int getRandomValue(int min, int max);
int findMedian(std::vector<int>& values);
void deleteNode(TreeNode*& root, TreeNode* nodeToDelete);
void deleteSubtree(TreeNode* node);
TreeNode* getNodeAtPosition(TreeNode* node, sf::Vector2f position);
PlaceholderNode* getPlaceholderAtPosition(const std::vector<PlaceholderNode>& placeholders, sf::Vector2f position);

#endif // TREEBASEFUNCTIONS_H