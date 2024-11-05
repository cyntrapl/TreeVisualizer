#include "TreeNode.h"

#include <queue>
#include <SFML/Graphics.hpp>

TreeNode::TreeNode(int val, float x, float y) :
    value(val),
    left(nullptr),
    right(nullptr),
    position(x, y)
{}

PlaceholderNode::PlaceholderNode(float x, float y, bool left) :
    position(x, y),
    isLeft(left)
{}