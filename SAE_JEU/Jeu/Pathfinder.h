#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include "type.h"



using namespace std;

struct Node {
    int y;            // Coordonnée y du nœud
    int x;            // Coordonnée x du nœud
    int parentX;      // Coordonnée x du parent
    int parentY;      // Coordonnée y du parent
    float gCost;      // Coût pour arriver au nœud en partant de la pos de départ
    float hCost;      // Coût estimé jusqu'à la destination (heuristique)
    float fCost;      // Coût total (fCost = gCost + hCost)
};


inline bool operator < (const Node & lhs, const Node & rhs) {
    return lhs.fCost < rhs.fCost;
}

// Fonction pour vérifier si une case est valide (dans les limites et sans obstacle)
bool isValid(int x, int y, CMat & map, CMyParamV2 & param);

// Fonction pour vérifier si le noeud actuel est la destination
bool isDestination(int x, int y, Node & dest);

// Calcul de l'heuristique (distance Euclidienne)
double calculateH(int x, int y, Node & dest);

// Génère le chemin en remontant les parents à partir de la destination
vector<Node> makePath(vector <vector<Node>> & map, Node & dest);

// Fonction principale de l'algorithme A*
vector<Node> aStar(Node & player, Node & dest, CMat & map, CMyParamV2 param);

#endif // ASTAR_H
