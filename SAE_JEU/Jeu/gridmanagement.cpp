#include <iostream>
#include <math.h>
#include "gridmanagement.h"

#include "type.h" //nos types
#include "Pathfinder.h"
#include <bits/stdc++.h>
using namespace std;








static Form F_T(){
    Form formeT;
    formeT.nom = "Forme T";
    formeT.piece = {
        {' ', 'M', ' '},
        {'M', 'M', 'M'}
    };
    formeT.dim = {2,3};
    return formeT;
}

static Form F_Carre() {
    Form carre;
    carre.nom = "Carre";
    carre.piece = {
        {'M', 'M'},
        {'M', 'M'}
    };
    carre.dim = {2, 2};
    return carre;
}

static Form F_L() {
    Form formeL;
    formeL.nom = "Carre";
    formeL.piece = {
        {' ', ' ', 'M'},
        {'M', 'M', 'M'}
    };
    formeL.dim = {2, 3};
    return formeL;
}

static Form F_S() {
    Form carre;
    carre.nom = "Carre";
    carre.piece = {
        {' ', 'M', 'M'},
        {'M', 'M', ' '}
    };
    carre.dim = {2, 3};
    return carre;
}


static Form F_Z() {
    Form carre;
    carre.nom = "Carre";
    carre.piece = {
        {'M', 'M', ' '},
        {' ', 'M', 'M'}
    };
    carre.dim = {2, 3};
    return carre;
}

static Form F_J() {
    Form carre;
    carre.nom = "Carre";
    carre.piece = {
        {' ', 'M'},
        {' ', 'M'},
        {'M', 'M'}
    };
    carre.dim = {3, 2};
    return carre;
}



//fonction pour ajouter piece dans la matrice (si manque de place => on supprime le M initial pour éviter un M seul)
void ajouterpiece(CMat &Mat, const Form &forme, int x, int y) {
    // Ajouter la pièce à partir de la position (x, y) dans la matrice cible
    for (size_t i = 0; i < forme.dim.first; ++i)
    {
        for (size_t j = 0; j < forme.dim.second; ++j)
        {
            // Vérifier que nous sommes dans les limites de la matrice cible
            if (x + i < Mat.size() && y + j < Mat[0].size())
            {
                // Ajouter la pièce uniquement si ce n'est pas un espace vide
                if (forme.piece[i][j] == 'M') {
                    Mat[x + i][y + j] = forme.piece[i][j];
                }
            }
            else
            {//sinon on supprime le M initial
                Mat[x][y] = ' ';
            }
        }
    }
}

void rotation90(Form &forme) {
    // Créer une nouvelle matrice avec les dimensions inversées
    vector<vector<char>> matrice;
    matrice.resize(forme.dim.second, vector<char>(forme.dim.first));

    // Effectuer la rotation de 90° (sens horaire)
    for (size_t i = 0; i < forme.dim.first; ++i) {      // Parcours des lignes de l'ancienne matrice
        for (size_t j = 0; j < forme.dim.second; ++j) { // Parcours des colonnes de l'ancienne matrice
            matrice[j][forme.dim.first - 1 - i] = forme.piece[i][j];
        }
    }

    // Remplacer la matrice actuelle par la matrice pivotée
    forme.piece = matrice;

    // Mettre à jour les dimensions de la forme
    swap(forme.dim.first, forme.dim.second);
}


void ClearScreen(){
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col){
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()


void DisplayGrid (const CMat & Mat,const CMyParamV2 & Param){
    const unsigned KNbLine = Mat.size ();
    const unsigned KNbCol  = Mat[0].size ();
    cout << string (KNbCol + 2 , '-') << endl;
    for (unsigned i (0); i < KNbLine; ++i){
        cout << '|';
        for (char c : Mat[i]){
            if(c == Param.tokenP1){
                Color (KColor.find(Param.ColorP1)->second);
                cout << c;
                Color (KColor.find("KReset")->second);
            }
            else if(c == Param.tokenP2){
                Color (KColor.find(Param.ColorP2)->second);
                cout << c;
                Color (KColor.find("KReset")->second);
            }
            else if(c == 'M'){
                Color ("\e[7;33");
                cout <<  ' ';
                Color (KColor.find("KReset")->second);
            }
            else if(c == 'T'){
                cout << "\e[6;34m";
                cout << c;
                Color (KColor.find("KReset")->second);
            }
            else if (c == 'A') {
                cout << "\e[6;35m";
                cout << c;
                Color (KColor.find("KReset")->second);

            }
            else{
                cout << c;
            }
        }
        cout << '|' << endl;
    }
    cout << string (KNbCol + 2 , '-') << endl;
}// ShowMatrix ()


void InitGrid (CMat & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2,
               const CMyParamV2 & Param, CPosition & Tp1, CPosition & Tp2, vector <CPosition> & PosMonster ){
    Mat.resize (NbLine);
    const CVLine KLine (NbColumn, KEmpty);
    for (CVLine & ALine : Mat)
        ALine = KLine;

    srand(time(0));

    unsigned x = 0, y = 0,val = 0, last_rand = 0;
    for (size_t i = 0; i < NbLine; i = i + 5)
    {
        for (size_t j = 0; j < NbColumn; j = j+5)
        {
            for (unsigned p = 0; p < 1; ++p)
            {
                x = x + rand();
                y = y + rand();
                x = x%(5-1);
                y = y%(5-1);
                Mat[i+x][j+y] = 'M';

                val = rand()%6;
                last_rand = rand()%3+0;
                Form mur; //jsp pas pourquoi je doit initialiser mur ici pour éviter un bug dans le switch
                switch (val)
                {
                case 0:
                    mur = F_T();
                    // un nbr random de rotation de 90° (entre 0 et 3)
                    // puis on ajouter cette piece a MAT
                    break;
                case 1:
                    mur = F_Carre();
                    break;
                case 2:
                    mur = F_L();
                    break;
                case 3:
                    mur = F_J();
                    break;
                case 4:
                    mur = F_S();
                    break;
                case 5:
                    mur = F_Z();
                    break;
                }
                for (unsigned int k = 0; k < last_rand; ++k)
                {
                    rotation90(mur);
                }
                ajouterpiece(Mat, mur, i + x, j + y);
            }
        }
    }

    //Init teleporter
    vector <long long> teleportX (2);
    vector <long long> teleportY (2);
    size_t  distx, disty;

    do{
        for(unsigned i = 0; i < 2; ++i){
            do{
                teleportX[i] = rand()%(Param.NbRow-3)+1;
                teleportY[i] = rand()%(Param.NbColumn-3)+1;
            }while(Mat[teleportX[i]][teleportY[i]] == 'M' || Mat[teleportX[i]-1][teleportY[i]] == 'M' ||
                   Mat[teleportX[i]+1][teleportY[i]] == 'M' || Mat[teleportX[i]][teleportY[i]-1] == 'M' ||
                     Mat[teleportX[i]][teleportY[i]+1] == 'M');

        }
        distx = std::abs(teleportY[0] - teleportY[1]);
        disty = std::abs(teleportX[0] - teleportX[1]);
    }while(distx < Param.NbColumn/3 || disty < Param.NbRow/3);

    Mat[teleportX[0]][teleportY[0]] = 'T';
    Tp1 = {teleportX[0], teleportY[0]};

    Mat[teleportX[1]][teleportY[1]] = 'T';
    Tp2 = {teleportX[1], teleportY[1]};


    srand(time(0)); // a test

    int nbr_item, cpt;
    x = 0, y = 0, cpt = 0;  //On reféfinit nos valeurs x et y pour placer les items(pour l'instant, un seul type)

    nbr_item = (Param.NbColumn * Param.NbRow) / (Param.NbColumn + Param.NbRow);

    if(nbr_item % 2 == 0) // pour avoir un nbr impaire d'item afin éviter égalité
        nbr_item += 1;

    do{
        x = rand()%(Param.NbRow-3)+1;
        y = rand()%(Param.NbColumn-3)+1;

        if(Mat[x][y] != 'M' && Mat[x][y] != 'T' && Mat[x][y] != 'S')
        {
            cpt += 1;
            Mat[x][y] = 'S';
        }
    }
    while (cpt < nbr_item);


    PosPlayer1.first = 0;
    PosPlayer1.second = NbColumn - 1;
    Mat [PosPlayer1.first][PosPlayer1.second] = Param.tokenP1;
    PosPlayer2.first = NbLine - 1;
    PosPlayer2.second =0;
    Mat [PosPlayer2.first][PosPlayer2.second] = Param.tokenP2;

    //Init Monster
    PosMonster.resize((Param.NbRow-3)/4);

    for(unsigned i = 0; i < PosMonster.size(); ++i){
        do{
            PosMonster[i] = CPosition(rand()%(Param.NbRow-3), rand()%(Param.NbColumn-3));
        }while(Mat[PosMonster[i].first][PosMonster[i].second] != KEmpty);

        Mat[PosMonster[i].first][PosMonster[i].second] = 'A';
    }

}//InitMat ()



void MoveMonster(vector<CPosition> & PosMonster, CMat &  Mat, const CMyParamV2 & param){

    for(unsigned m = 0 ; m < PosMonster.size() ; ++m ){
        CMat VuMonster;
        for(long long i = PosMonster[m].first-(param.NbRow/3); i < int(PosMonster[m].first+(param.NbRow/3)) && i < int(param.NbRow) ; ++i){
            if(i < 0) i = 0;
            if (size_t(i) >= param.NbRow) i = param.NbRow -1;
            CVLine Line;

            for(long long j = PosMonster[m].second -(param.NbColumn/3); j < int(PosMonster[m].second + (param.NbColumn/3)) && j <int(param.NbColumn) ; ++j){
                if(j < 0) j = 0;
                if (size_t(j) >= param.NbColumn) j = param.NbColumn -1;

                Line.push_back(Mat[i][j]);
            }
            VuMonster.push_back(Line);
        }

        vector <CPosition> VPosPlayer;
        CPosition PosMonsterLocal;
        for(size_t i = 0; i < VuMonster.size(); ++i){
            for(size_t j = 0; j < VuMonster[i].size(); ++j){
                if(VuMonster[i][j] == param.tokenP1 || VuMonster[i][j] == param.tokenP2){
                    VPosPlayer.push_back(CPosition(i,j));
                }
                else if(VuMonster[i][j] == 'A' &&
                           (int(i) - param.NbRow / 3 <= 2 || int(j) - param.NbColumn / 3 <= 2) ){
                    PosMonsterLocal = CPosition(i,j);
                }
            }
        }

        if(not VPosPlayer.empty()){
            CPosition ChoixPl = VPosPlayer[rand()%(VPosPlayer.size())];


            Node Monster = {int(PosMonsterLocal.second), int(PosMonsterLocal.first), -1, -1, 0.0, 0.0, 0.0};
            Node player = {int(ChoixPl.second), int(ChoixPl.first), -1, -1, 0.0, 0.0, 0.0};

            // Appel de l'algorithme A* pour trouver un chemin
            vector<Node> path = aStar(Monster, player, VuMonster, param);

            // Affichage du chemin trouvé
            if (!path.empty()) {
                cout << "Path found:" << endl;
                for (const Node& n : path) {
                    cout << "(" << n.x << ", " << n.y << ")" << endl;
                }


                CPosition NextMov (PosMonster[m].first + path[1].x - path[0].x, PosMonster[m].second + path[1].y - path[0].y);
                Mat[PosMonster[m].first][PosMonster[m].second] = KEmpty;
                Mat[NextMov.first][NextMov.second] = 'A';

                PosMonster[m] = NextMov;

            } else {
                cout << "No path found!" << endl;
            }

        }


    }
}



