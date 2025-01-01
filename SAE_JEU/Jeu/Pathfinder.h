// ©2023 JDSherbert. All rights reserved.
#pragma once

#include <vector>
#include <queue>
#include <cmath>

// Define a structure to represent a node in the graph
struct Node {
    int x, y;
    size_t f, g, h;
    Node* parent;  // Pointer to parent node for path reconstruction

    // Constructor to initialize the node
    Node(int _x, int _y)
        : x(_x), y(_y), f(0), g(0), h(0), parent(nullptr) {}

    // Overload operator > for the priority queue (min-heap based on f value)
    bool operator>(const Node& other) const {
        return f > other.f;
    }

    // Overload operator == to compare nodes
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

// A* pathfinding algorithm
std::vector<Node> FindPath(const std::vector<std::vector<int>>& graph, const Node& start, const Node& goal);

// Function to print the path
void PrintPath(const std::vector<Node>& path);
