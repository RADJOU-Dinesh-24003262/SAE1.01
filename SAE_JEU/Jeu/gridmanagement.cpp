#include <iostream>
#include "gridmanagement.h"
#include "type.h" //nos types

#include <bits/stdc++.h>
using namespace std;

#include <cmath>

struct Form{
    string nom;
    pair<size_t,size_t> dim;
    vector<vector<char>> piece;
};





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



void MoveMonster(vector<CPosition> & VPosMonster, CMat &  Mat, CMyParamV2 & param, CPosition & PosPlayer1, CPosition & PosPlayer2){
    vector <CPosition> VPosPlayer = {PosPlayer1, PosPlayer2};
    for (CPosition & PosMonster : VPosMonster) {
        vector< vector <Node>> MapNode(Mat.size(), vector<Node>(Mat[0].size()));
        bool finish;

        CPosition posplay = VPosPlayer[rand()%(VPosPlayer.size()-1)];
        //for(const CPosition & posplay : VPosPlayer){
            finish = false;
            vector <Node> PosOpen = {Node {posplay, 0, CPosition(-1,-1)}};
            vector <Node> PosClose = {};
            finish = false;
            Node CurrentNode;
            while (not finish) {

                if (PosOpen.empty()) {
                    cout << "PosOpen is empty. Exiting..." << endl;
                    break;
                }


                size_t indice = 0 ;

                for(size_t i = 1; i < PosOpen.size(); ++i){
                    if(PosOpen[i].f_cost < PosOpen[indice].f_cost) indice = i;
                }
                CurrentNode = PosOpen[indice];
                PosOpen.erase (PosOpen.begin() + indice);
                PosClose.push_back(CurrentNode);
                MapNode[CurrentNode.Pos.first][CurrentNode.Pos.second] = CurrentNode;

                if(CurrentNode.Pos == PosMonster){
                    finish = true;
                    break;
                }

                //regarder les voisins
                for(const int & i : {-1,0,1}){
                    for (const int & j : {-1,0,1}) {
                        int voisin_i = CurrentNode.Pos.first + i;
                        int voisin_j = CurrentNode.Pos.second + j;
                        // cout << voisin_i << " " << voisin_j << endl;
                        if(i == 0 && j == 0 && voisin_i == 0 && voisin_j == 0) continue; //éviter de reprendre lui même

                        bool inClose = false;
                        for (const Node & node_test : PosClose) {
                            if (node_test.Pos.first == voisin_i && node_test.Pos.second == voisin_j) {
                                inClose = true;
                                break;
                            }
                        }

                        if (voisin_i >= 0 && voisin_j >= 0 && size_t(voisin_i) < Mat.size() &&
                            size_t(voisin_j) < Mat[voisin_i].size() && (Mat[voisin_i][voisin_j] == KEmpty || Mat[voisin_i][voisin_j] == param.tokenP2 ||Mat[voisin_i][voisin_j] == param.tokenP1 || Mat[voisin_i][voisin_j] == 'A') && not inClose){

                            Node NodeVoisin = {CPosition(voisin_i, voisin_j), CurrentNode.f_cost + 1, CurrentNode.Pos};


                            bool inOpen = false;
                            for (Node & node_test : PosOpen) {
                                if (node_test.Pos == NodeVoisin.Pos) {
                                    inOpen = true;
                                    if(node_test.f_cost > NodeVoisin.f_cost){
                                        node_test.f_cost = NodeVoisin.f_cost;
                                        node_test.Parent = CurrentNode.Pos;
                                    }
                                    break;
                                }
                            }

                            if(not inOpen){
                                PosOpen.push_back(NodeVoisin);
                            }

                        }
                    }
                }

            }

            //cout << Mat[PosMonster.first][PosMonster.second] << endl;
            Mat[PosMonster.first][PosMonster.second] = KEmpty;
            //cout << Mat[PosMonster.first][PosMonster.second] << endl;
            Mat[ MapNode[PosMonster.first][PosMonster.second].Parent.first][MapNode[PosMonster.first][PosMonster.second].Parent.second] = 'A';
            //cout << MapNode[PosMonster.first][PosMonster.second].Parent.first << ' ' << MapNode[PosMonster.first][PosMonster.second].Parent.second << endl;
            PosMonster = CPosition(MapNode[PosMonster.first][PosMonster.second].Parent.first,MapNode[PosMonster.first][PosMonster.second].Parent.second);
            //string zlkjd;
            //cin >> zlkjd;
        //}

    }
}


