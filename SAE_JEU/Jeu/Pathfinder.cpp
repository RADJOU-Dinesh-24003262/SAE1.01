#include "Pathfinder.h"
using namespace std;


bool isValid(int x, int y, CMat & map, CMyParamV2 & param) { //If our Node is an obstacle it is not valid
    if (x >= 0 && y >= 0 && size_t(x) < map[0].size() && size_t(y) < map.size()) {
        if (map[x][y] == KEmpty || map[x][y] == param.tokenP1 || map[x][y] == param.tokenP2 || map[x][y] == 'A') {
            return true;
        }
        cout << x << " " << y << " " <<map[x][y] << endl;
        return false;
    }
    cout << x << " " << y;
    return false;
}

bool isDestination(int x, int y, Node & dest) {
    if (x == dest.x && y == dest.y) {
        return true;
    }
    return false;
}

double calculateH(int x, int y, Node & dest) {
    double H = (sqrt((x - dest.x)*(x - dest.x) + (y - dest.y)*(y - dest.y)));
    return H;
}

vector<Node> makePath(vector <vector<Node>> & map, Node & dest) {
    try {
        cout << "Found a path" << endl;
        int x = dest.x;
        int y = dest.y;
        stack<Node> path;
        vector<Node> usablePath;

        while (!(map[x][y].parentX == x && map[x][y].parentY == y)
               && map[x][y].x != -1 && map[x][y].y != -1)
        {
            path.push(map[x][y]);
            int tempX = map[x][y].parentX;
            int tempY = map[x][y].parentY;
            x = tempX;
            y = tempY;

        }
        path.push(map[x][y]);

        while (!path.empty()) {
            Node top = path.top();
            path.pop();
            usablePath.emplace_back(top);
        }
        return usablePath;
    }
    catch(const exception& e){
        cout << e.what() << endl;
    }
}

vector<Node> aStar(Node & player, Node & dest, CMat & map,CMyParamV2 param) {
    vector<Node> empty;
    if (isValid(dest.x, dest.y, map, param) == false) {
        cout << "Destination is an obstacle" << endl;
        return empty;
        //Destination is invalid
    }
    if (isDestination(player.x, player.y, dest)) {
        cout << "You are the destination" << endl;
        return empty;
        //You clicked on yourself
    }
    vector<vector<bool>> closedList(map[0].size(), vector<bool>(map.size()));

    //Initialize whole map
    vector<vector < Node>> allMap;
    allMap.resize(map[0].size());
    for(vector <Node> & line : allMap){
        line.resize(map.size());
    }


    for (size_t x = 0; x < map[0].size(); ++x) {
        for (size_t y = 0; y < map.size(); ++y) {
            allMap[x][y].fCost = map.max_size();
            allMap[x][y].gCost = map.max_size();
            allMap[x][y].hCost = map.max_size();
            allMap[x][y].parentX = -1;
            allMap[x][y].parentY = -1;
            allMap[x][y].x = x;
            allMap[x][y].y = y;

            closedList[x][y] = false;
        }
    }

    //Initialize our starting list
    int x = player.x;
    int y = player.y;
    allMap[x][y].fCost = 0.0;
    allMap[x][y].gCost = 0.0;
    allMap[x][y].hCost = 0.0;
    allMap[x][y].parentX = x;
    allMap[x][y].parentY = y;

    vector<Node> openList;
    openList.emplace_back(allMap[x][y]);
    bool destinationFound = false;

    while (!openList.empty() && openList.size() < map[0].size()*map.size()) {
        Node node;
        do {
            //This do-while loop could be replaced with extracting the first
            //element from a set, but you'd have to make the openList a set.
            //To be completely honest, I don't remember the reason why I do
            //it with a vector, but for now it's still an option, although
            //not as good as a set performance wise.
            float temp = map.max_size();
            vector<Node>::iterator itNode;
            for (vector<Node>::iterator it = openList.begin();
                 it != openList.end(); it = next(it)) {
                Node n = *it;
                if (n.fCost < temp) {
                    temp = n.fCost;
                    itNode = it;
                }
            }
            node = *itNode;
            openList.erase(itNode);
        } while (isValid(node.x, node.y, map, param) == false);

        x = node.x;
        y = node.y;
        closedList[x][y] = true;

        //For each neighbour starting from North-West to South-East
        for (int newX = -1; newX <= 1; newX++) {
            for (int newY = -1; newY <= 1; newY++) {
                double gNew, hNew, fNew;
                if (isValid(x + newX, y + newY, map, param)) {
                    if (isDestination(x + newX, y + newY, dest))
                    {
                        //Destination found - make path
                        allMap[x + newX][y + newY].parentX = x;
                        allMap[x + newX][y + newY].parentY = y;
                        destinationFound = true;
                        return makePath(allMap, dest);
                    }
                    else if (closedList[x + newX][y + newY] == false)
                    {
                        gNew = node.gCost + 1.0;
                        hNew = calculateH(x + newX, y + newY, dest);
                        fNew = gNew + hNew;
                        // Check if this path is better than the one already present
                        if (allMap[x + newX][y + newY].fCost == map.max_size() ||
                            allMap[x + newX][y + newY].fCost > fNew)
                        {
                            // Update the details of this neighbour node
                            allMap[x + newX][y + newY].fCost = fNew;
                            allMap[x + newX][y + newY].gCost = gNew;
                            allMap[x + newX][y + newY].hCost = hNew;
                            allMap[x + newX][y + newY].parentX = x;
                            allMap[x + newX][y + newY].parentY = y;
                            openList.emplace_back(allMap[x + newX][y + newY]);
                        }
                    }
                }
            }
        }
    }
    if (destinationFound == false) {
        cout << "Destination not found" << endl;
        return empty;
    }
}



