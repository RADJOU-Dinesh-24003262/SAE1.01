#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include "Pathfinder.h"
using namespace std;

vector<Node> FindPath(const vector<vector<int>>& graph, const Node& start, const Node& goal) {
    // Define possible movements (4 directions: up, down, left, right)
    const int directionX[] = {-1, 0, 1, 0};
    const int directionY[] = {0, 1, 0, -1};

    // Initialize the open and closed lists
    priority_queue<Node, vector<Node>, greater<Node>> openList;
    vector<vector<bool>> closedList(graph.size(), vector<bool>(graph[0].size(), false));

    // Map to store the parent of each node
    vector<vector<Node*>> parentMap(graph.size(), vector<Node*>(graph[0].size(), nullptr));

    // Start node
    openList.push(start);

    // Main loop
    while (!openList.empty()) {
        // Get the cell with the lowest f value from the open list
        Node current = openList.top();
        openList.pop();

        // Check if the current cell is the goal
        if (current == goal) {
            // Reconstruct the path
            vector<Node> path;
            Node* pathNode = &current;
            while (pathNode != nullptr) {
                path.push_back(*pathNode);
                pathNode = pathNode->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Mark the current cell as closed
        closedList[current.x][current.y] = true;

        // Explore neighbors
        for (int i = 0; i < 4; ++i) {
            int newX = current.x + directionX[i];
            int newY = current.y + directionY[i];

            // Check if the neighbor is within the grid boundaries
            if (newX >= 0 && newX < graph.size() && newY >= 0 && newY < graph[0].size()) {
                // Check if the neighbor is walkable and not in the closed list
                if (graph[newX][newY] == 0 && !closedList[newX][newY]) {
                    Node neighbor(newX, newY);
                    int newG = current.g + 1;
                    neighbor.g = newG;
                    neighbor.h = abs(newX - goal.x) + abs(newY - goal.y);
                    neighbor.f = neighbor.g + neighbor.h;
                    neighbor.parent = new Node(current);  // Set the parent of the neighbor

                    // If the neighbor is not in the open list, add it
                    openList.push(neighbor);
                    parentMap[newX][newY] = &neighbor;  // Track the parent of the node
                }
            }
        }
    }

    // No path found
    return vector<Node>();
}

void PrintPath(const vector<Node>& path) {
    for (const Node& node : path) {
        std::cout << "(" << node.x << ", " << node.y << ") ";
    }
    std::cout << std::endl;
}
