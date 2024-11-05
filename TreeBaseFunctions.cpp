#include "TreeBaseFunctions.h"
#include <algorithm>
#include <cstdlib>
#include <queue>


int findLargestValue(TreeNode* node) {
    if (node == nullptr) return 0;
    int leftMax = findLargestValue(node->left);
    int rightMax = findLargestValue(node->right);
    return std::max({node->value, leftMax, rightMax});
}

bool valueExists(TreeNode* node, int value) {
    if (node == nullptr) return false;
    if (node->value == value) return true;
    return valueExists(node->left, value) || valueExists(node->right, value);
}

void collectValues(TreeNode* node, std::vector<int>& values) {
    if (node == nullptr) return;
    collectValues(node->left, values);
    values.push_back(node->value);
    collectValues(node->right, values);
}

TreeNode* insertBST(TreeNode* node, int value, float x, float y) {
    if (node == nullptr) {
        return new TreeNode(value, x, y);
    }
    if (value < node->value) {
        node->left = insertBST(node->left, value, x - 50, y + 100);
    } else {
        node->right = insertBST(node->right, value, x + 50, y + 100);
    }
    return node;
}

int getRandomValue(int min, int max) {
    return min + rand() % ((max + 1) - min);
}

int findMedian(std::vector<int>& values) {
    std::sort(values.begin(), values.end());
    return values[values.size() / 2];
}

void deleteNode(TreeNode*& root, TreeNode* nodeToDelete) {
    if (root == nullptr || nodeToDelete == nullptr) return;

    // If the node to delete is the root, do nothing
    if (root == nodeToDelete) {
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

void deleteSubtree(TreeNode* node) {
    if (node == nullptr) return;
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
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