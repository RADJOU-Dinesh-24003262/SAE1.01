#include <iostream>
#include <vector>

#include <unistd.h>

#include "game.h"
#include "params.h"
#include "gridmanagement.h"

#define FPS_LIMIT 60

#include <thread>
#include <cmath>

#include "mingl/mingl.h"

#include <tuple>
#include "sprites/player1.h"
#include "sprites/player2.h"
#include "sprites/wall.h"
#include "sprites/kebab.h"
#include "sprites/cigarette.h"
#include "sprites/monstre.h"
#include "sprites/teleporter.h"
#include "sprites/statue.h"
#include "MenuManagement.h"



#include <map>
using namespace std;

bool IsMoveLegal(const CMat & Mat, const char & Move, const  CPosition & Pos, const CMyParamV2 & Param){
    if (Move == Param.KeyUp && Pos.first > 0 && Mat [Pos.first-1][Pos.second] != 'M'){
        return true;
    }else if (Move == Param.KeyDown && Pos.first < Param.NbRow -1 && Mat [Pos.first+1][Pos.second] != 'M'){
        return true;
    }else if (Move == Param.KeyRight && Pos.second < Param.NbColumn-1 && Mat [Pos.first][Pos.second+1] != 'M'){
        return true;
    }else if(Move == Param.KeyLeft && Pos.second > 0 && Mat [Pos.first][Pos.second-1] != 'M'){
        return true;
    }else{
        Color(KColor.find("KRed")->second);
        cout << "Illegal Move, Play again ! ";
        Color (KColor.find("KReset")->second);
        return false;
    }
}

pair<char, CPosition> nextMove(const CMat &Mat, const char &Move, const CPosition &Pos,
                               const CMyParamV2 &Param, CPosition &Tp1, CPosition &Tp2) {
    // Retourne le contenu de la case suivante et sa position
    if (Move == Param.KeyUp && Pos.first > 0 && Mat[Pos.first - 1][Pos.second] != 'M') {
        if (Tp1.first == Pos.first - 1 && Tp1.second == Pos.second) { // Si c'est Tp1, aller vers Tp2
            return {Mat[Tp2.first-1][Tp2.second], {Tp2.first - 1, Tp2.second}};
        } else if (Tp2.first == Pos.first - 1 && Tp2.second == Pos.second) { // Si c'est Tp2, aller vers Tp1
            return {Mat[Tp1.first - 1][Tp1.second], {Tp1.first - 1, Tp1.second}};
        } else { // Sinon, déplacement normal
            return {Mat[Pos.first - 1][Pos.second], {Pos.first - 1, Pos.second}};
        }
    } else if (Move == Param.KeyDown && Pos.first < Param.NbRow - 1 && Mat[Pos.first + 1][Pos.second] != 'M') {
        if (Tp1.first == Pos.first + 1 && Tp1.second == Pos.second) { // Si c'est Tp1, aller vers Tp2
            return {Mat[Tp2.first + 1][Tp2.second], {Tp2.first + 1, Tp2.second}};
        } else if (Tp2.first == Pos.first + 1 && Tp2.second == Pos.second) { // Si c'est Tp2, aller vers Tp1
            return {Mat[Tp1.first + 1][Tp1.second], {Tp1.first + 1, Tp1.second}};
        } else { // Sinon, déplacement normal
            return {Mat[Pos.first + 1][Pos.second], {Pos.first + 1, Pos.second}};
        }
    } else if (Move == Param.KeyRight && Pos.second < Param.NbColumn - 1 && Mat[Pos.first][Pos.second + 1] != 'M') {
        if (Tp1.first == Pos.first && Tp1.second == Pos.second + 1) { // Si c'est Tp1, aller vers Tp2
            return {Mat[Tp2.first][Tp2.second + 1], {Tp2.first, Tp2.second + 1}};
        } else if (Tp2.first == Pos.first && Tp2.second == Pos.second + 1) { // Si c'est Tp2, aller vers Tp1
            return {Mat[Tp1.first][Tp1.second + 1], {Tp1.first, Tp1.second + 1}};
        } else { // Sinon, déplacement normal
            return {Mat[Pos.first][Pos.second + 1], {Pos.first, Pos.second + 1}};
        }
    } else if (Move == Param.KeyLeft && Pos.second > 0 && Mat[Pos.first][Pos.second - 1] != 'M') {
        if (Tp1.first == Pos.first && Tp1.second == Pos.second - 1) { // Si c'est Tp1, aller vers Tp2
            return {Mat[Tp2.first][Tp2.second - 1], {Tp2.first, Tp2.second - 1}};
        } else if (Tp2.first == Pos.first && Tp2.second == Pos.second - 1) { // Si c'est Tp2, aller vers Tp1
            return {Mat[Tp1.first][Tp1.second - 1], {Tp1.first, Tp1.second - 1}};
        } else { // Sinon, déplacement normal
            return {Mat[Pos.first][Pos.second - 1], {Pos.first, Pos.second - 1}};
        }
    }
}

bool IsCollectible(const char move) // On check si la case n'est ni un mur, ni un tp, ni une case vide
{
    if(move == ' ' || move == 'T' || move == 'M')
        return false;
    else
        return true;
}

void CalculateScore(vector<char> &objets, int &score)
{
    while (!objets.empty()) {
        char item = objets.back();
        objets.pop_back();
        switch (item) {
        case 'S': score += 350; break;
        case 'C': score += 100; break;
        case 'K': score += 75; break;
        }
    }
}

void Sprite(MinGL &window, int grid_x, int grid_y, int pos_x, int pos_y, int mat_x, int mat_y, string sprite){
    //calcule la position de la tuile
    int x0 = (grid_x*pos_x); // coordonées x points en haut a gauche
    int y0 = (grid_x*pos_y); // coordonées y points en haut a gauche
    int x1 = (grid_y*(pos_x+1)); // coordonées x points en bas a droite
    int y1 = (grid_y*(pos_y+1)); // coordonées y points en bas a droite
    //calcul de la position centrale du personnage
    int Center1 = x0+((x1-x0)/2);
    int Center2 = y0+((y1-y0)/2);

    //affiche le sprite correspondant a l'élément de la case
    if (sprite == "player1")Player1(window, Center1, Center2, mat_x, mat_y);
    if (sprite == "player2")Player2(window, Center1, Center2, mat_x, mat_y);
    if (sprite == "wall")Wall(window, Center1, Center2, mat_x, mat_y);
    if (sprite == "statue")Statue(window, Center1, Center2, mat_x, mat_y);
    if (sprite == "cigarette")Cigarette(window, Center1, Center2, mat_x, mat_y);
    if (sprite == "kebab")Kebab(window, Center1, Center2, mat_x, mat_y);
    if (sprite == "teleporter")Teleporter(window, Center1, Center2, mat_x, mat_y);
    if (sprite == "monstre")Monstre(window, Center1, Center2, mat_x, mat_y);
}

void DisplayGrid (MinGL &window, const CMat & mat, tuple <int, int> Screen_size){
    int mat_x = size(mat);
    int mat_y = size(mat[0]);

    int grid_x = get<0>(Screen_size)/mat_x;
    int grid_y = get<1>(Screen_size)/mat_y;

    for (int i=0; i < mat_x; ++i){
        for (int j=0; j < mat_y; ++j){
            switch (mat[j][i]){
            case 'X':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "player1");
                break;
            case 'O':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "player2");
                break;
            case 'M':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "wall");
                break;
            case 'S':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "statue");
                break;
            case 'A':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "monstre");
                break;
            case 'C':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "cigarette");
                break;
            case 'K':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "kebab");
                break;
            case 'T':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "teleporter");
                break;
            default:
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "floor");
            }
        }
    }
}



void MoveToken (CMat & Mat, const char & Move, CPosition & Pos, const CMyParamV2 & Param, CPosition & Tp1, CPosition & Tp2 ){
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;

    if (Move == Param.KeyUp){
        --Pos.first;
    }else if (Move == Param.KeyDown){
        ++Pos.first;
    }else if (Move == Param.KeyRight){
        ++Pos.second;
    }else if(Move == Param.KeyLeft){
        --Pos.second;
    }

    vector <CPosition> PosTP = {Tp1,Tp2};
    for(unsigned i = 0;i < 2; ++i){
        if(Pos == PosTP[i]){
            Pos.first = PosTP[(i+1)%2].first;
            Pos.second = PosTP[(i+1)%2].second;

            if (Move == Param.KeyUp){
                --Pos.first;
            }else if (Move == Param.KeyDown){
                ++Pos.first;
            }else if (Move == Param.KeyRight){
                ++Pos.second;
            }else if(Move == Param.KeyLeft){
                --Pos.second;
            }
        }
        Mat[PosTP[i].first][PosTP[i].second] = 'T';
    }

    Mat [Pos.first][Pos.second] = car;

} //MoveToken ()


int ppal (void){

    // Initialise le système
    tuple <int, int> Screen_size(640,640);
    MinGL window("Lethal Company  |  V0.0.1", nsGraphics::Vec2D(get<0>(Screen_size), get<1>(Screen_size)), nsGraphics::Vec2D(128, 128), nsGraphics::KWhite);
    window.initGlut();
    window.initGraphic();

    int menuid (0);
    CMyParamV2 param;
    initParams(param);
    LoadParams(param);
    vector<tuple<vector<int>, vector<int>, int>> clickablepool;
    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (param.NbColumn * param.NbRow);
    int scoreJ1 = 0, scoreJ2 = 0;
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
    CMat Mat;

    bool Player1Turn (true);
    bool Victory (false);

    CPosition PosPlayer1, PosPlayer2, PosTP1, PosTP2;
    vector <CPosition> PosMonster;
    cout << param.NbColumn << " " << param.NbRow << endl;

    InitGrid(Mat, param.NbRow, param.NbColumn, PosPlayer1, PosPlayer2, param, PosTP1, PosTP2, PosMonster);



    vector<char> objetJ1;
    vector<char> objetJ2;

    pair<char,CPosition> N_move;

    bool run (true);
    while (run){ //voir case 5 pour break;

        switch(menuid) {

        case 0: //menu principal

            clickablepool.clear();
            clickablepool = {
                std::make_tuple(std::vector<int>{100, 48}, std::vector<int>{300, 148}, 4),
                std::make_tuple(std::vector<int>{100, 196}, std::vector<int>{300, 296}, 1),
                std::make_tuple(std::vector<int>{100, 344}, std::vector<int>{300, 444}, 2),
                std::make_tuple(std::vector<int>{100, 492}, std::vector<int>{300, 592}, 6)
            };
            while(menuid == 0){

                window.clearScreen();

                MenuPrincipal(window, get<0>(Screen_size), get<1>(Screen_size));

                window.finishFrame();

                events(window, clickablepool, menuid);

                window.getEventManager().clearEvents();

                this_thread::sleep_for(chrono::milliseconds(2500 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

            }
            break;

        case 1: //Options

            clickablepool.clear();
            clickablepool = {
                std::make_tuple(std::vector<int>{0, 0}, std::vector<int>{120, 50}, 0)
            };

            while(menuid == 1){

                window.clearScreen();

                Options(window, get<0>(Screen_size), get<1>(Screen_size));

                window.finishFrame();

                events(window, clickablepool, menuid);

                window.getEventManager().clearEvents();

                this_thread::sleep_for(chrono::milliseconds(2500 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

            }
            break;

        case 2: //Credits

            clickablepool.clear();
            clickablepool = {
                std::make_tuple(std::vector<int>{0, 0}, std::vector<int>{120, 50}, 0)
            };

            while(menuid == 2){

                Credits(window, get<0>(Screen_size), get<1>(Screen_size));

                window.finishFrame();

                events(window, clickablepool, menuid);

                window.getEventManager().clearEvents();

                this_thread::sleep_for(chrono::milliseconds(2500 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

            }
            break;

        case 3: //Pause

            clickablepool.clear();
            clickablepool = {
                std::make_tuple(std::vector<int>{100, 48}, std::vector<int>{300, 148}, 4),
                std::make_tuple(std::vector<int>{100, 196}, std::vector<int>{300, 296}, 5),
                std::make_tuple(std::vector<int>{100, 344}, std::vector<int>{300, 444}, 0),
                             };

            while(menuid == 3){

                MenuPause(window, get<0>(Screen_size), get<1>(Screen_size));

                window.finishFrame();

                events(window, clickablepool, menuid);

                window.getEventManager().clearEvents();

                this_thread::sleep_for(chrono::milliseconds(2500 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

            }
            break;

        case 4: //Jeu

            clickablepool.clear();
            clickablepool = {
                std::make_tuple(std::vector<int>{0, 0}, std::vector<int>{120, 50}, 1),
                             };

            DisplayGrid(window, Mat, Screen_size);
            window.finishFrame();

            while(PartyNum <= KMaxPartyNum && !Victory && window.isOpen()){

                chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
                window.clearScreen();
                DisplayGrid(window, Mat, Screen_size);
                window.finishFrame();
                char Move;
                string temp;
                //ask to the player the move to do till it's legal
                DisplayGrid(window, Mat, Screen_size);
                do{
                    cout << "Score J1: " << scoreJ1 << ", Score J2: " << scoreJ2 << endl;
                    cout << "tour numero : " << PartyNum << ", Joueur "
                         << (Player1Turn ? '1' : '2') << ", entrez un déplacement : ";
                    getline(cin, temp);
                    Move = temp[0];
                    Move = tolower(Move);

                }while(not IsMoveLegal(Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param));

                window.clearScreen();
                DisplayGrid(window, Mat, Screen_size);
                window.finishFrame();

                N_move = nextMove(Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param, PosTP1, PosTP2);

                // check si il ya un objet => ajouter a une liste
                if(IsCollectible(N_move.first))
                {
                    if(Player1Turn == 1) objetJ1.push_back(N_move.first);
                    if(Player1Turn == 0) objetJ2.push_back(N_move.first);
                }

                // check si joueur arrive a la maison => vide ses poches (comptage du score)
                if (!Player1Turn && N_move.second.first == param.NbRow - 1 && N_move.second.second == 0)
                {
                    CalculateScore(objetJ2, scoreJ2);
                }

                if (Player1Turn && N_move.second.first == 0 && N_move.second.second == param.NbColumn - 1)
                    CalculateScore(objetJ1, scoreJ1);

                MoveToken(Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param, PosTP1, PosTP2);
                //on fait jouer le bot 1fois/2 sinon il aurait trop d'avantage
                if(Player1Turn){
                    MoveMonster(PosMonster, Mat, param, PosPlayer1, PosPlayer2);
                }
                DisplayGrid(Mat, param);

                window.finishFrame();

                events(window, clickablepool, menuid);

                // On vide la queue d'évènements
                window.getEventManager().clearEvents();

                // On attend un peu pour limiter le framerate et soulager le CPU
                this_thread::sleep_for(chrono::milliseconds(2500 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

                //Victory test
                if (PosPlayer1 == PosPlayer2) Victory = true;
                bool MonsterEatPLay (false);
                for(const CPosition & posmonst : PosMonster){
                    if(posmonst == PosPlayer1 || posmonst == PosPlayer2) MonsterEatPLay = true;
                }
                if(MonsterEatPLay){
                    Color (KColor.find("KRed")->second);
                    cout << "Vous avez perdu !! \nMission Failed \n";
                    Color (KColor.find("KReset")->second);
                    InitGrid(Mat, param.NbRow, param.NbColumn, PosPlayer1, PosPlayer2, param, PosTP1, PosTP2, PosMonster); //reinitialise la grille pour la prochaine partie
                    PartyNum = 1;
                    break;
                }
                //Increase party's number
                ++PartyNum;

                //Player changing
                Player1Turn = !Player1Turn;

            }//while(no victory)

            if (!Victory){
                Color (KColor.find("KMAgenta")->second);
                cout << "Aucun vainqueur" << endl;
                menuid = 0;
            }

            Color (KColor.find("KGreen")->second);
            cout << "Félicitations Joueur " << (Player1Turn ? '2' : '1')
                 << " vous avez gagné :)" << endl;
            Color (KColor.find("KReset")->second);
            menuid = 0;
            InitGrid(Mat, param.NbRow, param.NbColumn, PosPlayer1, PosPlayer2, param, PosTP1, PosTP2, PosMonster);//reinitialise la grille pour la prochaine partie
            PartyNum = 1;

            break;

        case 5 ://restart

            InitGrid(Mat, param.NbRow, param.NbColumn, PosPlayer1, PosPlayer2, param, PosTP1, PosTP2, PosMonster);
            PartyNum = 1;
            menuid = 4;
            break;

        case 6 :
            run = false;
        }
    }
    return 0;
}//ppal ()

