#include <iostream>
#include <vector>

#include <unistd.h>

#include "game.h"
#include "params.h"
#include "gridmanagement.h"

#define FPS_LIMIT 15

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

bool IsMoveLegal(const CMat & Mat, const bool & KeyUp, const bool & KeyDown,
                 const bool & KeyRight, const bool & KeyLeft,
                 const  CPosition & Pos, const CMyParamV2 &Param){

    if (not KeyUp && not KeyDown && not KeyRight && not KeyLeft){
        return false;
    }else if ((KeyUp && KeyDown) || (KeyUp && KeyLeft) || (KeyUp && KeyRight)||
        (KeyDown && KeyLeft) || (KeyDown && KeyRight) ||
        ( KeyRight && KeyLeft)){
        return false;
    }else if (KeyUp && Pos.first > 0 && Mat [Pos.first-1][Pos.second] != 'M' && Mat [Pos.first-1][Pos.second] != 'A'){
        return true;
    }else if (KeyDown && Pos.first < Param.NbRow -1 && Mat [Pos.first+1][Pos.second] != 'M' && Mat [Pos.first+1][Pos.second] != 'A'){
        return true;
    }else if (KeyRight && Pos.second < Param.NbColumn-1 && Mat [Pos.first][Pos.second+1] != 'M' && Mat [Pos.first][Pos.second - 1] != 'A'){
        return true;
    }else if(KeyLeft && Pos.second > 0 && Mat [Pos.first][Pos.second-1] != 'M' && Mat [Pos.first][Pos.second - 1] != 'A'){
        return true;
    }else{
        Color(KColor.find("KRed")->second);
        cout << "Illegal Move, Play again ! ";
        Color (KColor.find("KReset")->second);
        return false;
    }
}

pair<char, CPosition> nextMove(const CMat &Mat, const bool & KeyUp, const bool & KeyDown,
                               const bool & KeyRight, const bool & KeyLeft, const CPosition &Pos,
                               const CMyParamV2 &Param, CPosition &Tp1, CPosition &Tp2) {
    // Retourne le contenu de la case suivante et sa position
    if (KeyUp && Pos.first > 0 && Mat[Pos.first - 1][Pos.second] != 'M') {
        if (Tp1.first == Pos.first - 1 && Tp1.second == Pos.second) { // Si c'est Tp1, aller vers Tp2
            return {Mat[Tp2.first-1][Tp2.second], {Tp2.first - 1, Tp2.second}};
        } else if (Tp2.first == Pos.first - 1 && Tp2.second == Pos.second) { // Si c'est Tp2, aller vers Tp1
            return {Mat[Tp1.first - 1][Tp1.second], {Tp1.first - 1, Tp1.second}};
        } else { // Sinon, déplacement normal
            return {Mat[Pos.first - 1][Pos.second], {Pos.first - 1, Pos.second}};
        }
    } else if (KeyDown && Pos.first < Param.NbRow - 1 && Mat[Pos.first + 1][Pos.second] != 'M') {
        if (Tp1.first == Pos.first + 1 && Tp1.second == Pos.second) { // Si c'est Tp1, aller vers Tp2
            return {Mat[Tp2.first + 1][Tp2.second], {Tp2.first + 1, Tp2.second}};
        } else if (Tp2.first == Pos.first + 1 && Tp2.second == Pos.second) { // Si c'est Tp2, aller vers Tp1
            return {Mat[Tp1.first + 1][Tp1.second], {Tp1.first + 1, Tp1.second}};
        } else { // Sinon, déplacement normal
            return {Mat[Pos.first + 1][Pos.second], {Pos.first + 1, Pos.second}};
        }
    } else if (KeyRight && Pos.second < Param.NbColumn - 1 && Mat[Pos.first][Pos.second + 1] != 'M') {
        if (Tp1.first == Pos.first && Tp1.second == Pos.second + 1) { // Si c'est Tp1, aller vers Tp2
            return {Mat[Tp2.first][Tp2.second + 1], {Tp2.first, Tp2.second + 1}};
        } else if (Tp2.first == Pos.first && Tp2.second == Pos.second + 1) { // Si c'est Tp2, aller vers Tp1
            return {Mat[Tp1.first][Tp1.second + 1], {Tp1.first, Tp1.second + 1}};
        } else { // Sinon, déplacement normal
            return {Mat[Pos.first][Pos.second + 1], {Pos.first, Pos.second + 1}};
        }
    } else if (KeyLeft && Pos.second > 0 && Mat[Pos.first][Pos.second - 1] != 'M') {
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
    window << nsShape::Rectangle(nsGraphics::Vec2D(0, 0), nsGraphics::Vec2D(120, 50), nsGraphics::KBlueTransparent);
    int mat_x = size(mat);
    int mat_y = size(mat[0]);

    int grid_x = get<0>(Screen_size)/mat_x;
    int grid_y = get<1>(Screen_size)/mat_y;
    std::map <char, string> sprits = {
        {'X' , "player1" },
        {'O' , "player2" },
        {'M' , "wall" },
        {'S' , "statue" },
        {'A' , "monstre" },
        {'C' , "cigarette" },
        {'K' , "kebab" },
        {'T' , "teleporter" }
    };

    for (int i=0; i < mat_x; ++i){
        for (int j=0; j < mat_y; ++j){
            Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, sprits[mat[j][i]]);
        }
    }
}

void MoveToken (CMat &Mat, const bool & KeyUp, const bool & KeyDown,
               const bool & KeyRight, const bool & KeyLeft, CPosition &Pos, CPosition &Tp1, CPosition &Tp2){
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;

    if (KeyUp){
        --Pos.first;
    }else if (KeyDown){
        ++Pos.first;
    }else if (KeyRight){
        ++Pos.second;
    }else if(KeyLeft){
        --Pos.second;
    }

    vector <CPosition> PosTP = {Tp1,Tp2};
    for(unsigned i = 0;i < 2; ++i){
        if(Pos == PosTP[i]){
            Pos.first = PosTP[(i+1)%2].first;
            Pos.second = PosTP[(i+1)%2].second;

            if (KeyUp){
                --Pos.first;
            }else if (KeyDown){
                ++Pos.first;
            }else if (KeyRight){
                ++Pos.second;
            }else if(KeyLeft){
                --Pos.second;
            }
        }
        Mat[PosTP[i].first][PosTP[i].second] = 'T';
    }

    Mat [Pos.first][Pos.second] = car;

} //MoveToken ()

void MenuP(MinGL &window, vector<tuple<vector<int>, vector<int>, int>> clickablepool,
           tuple <int, int> Screen_size, int & menuid, chrono::time_point<chrono::steady_clock> start){
    clickablepool.clear();
    clickablepool = {
        std::make_tuple(std::vector<int>{100, 48}, std::vector<int>{300, 148}, 4),
        std::make_tuple(std::vector<int>{100, 196}, std::vector<int>{300, 296}, 1),
        std::make_tuple(std::vector<int>{100, 344}, std::vector<int>{300, 444}, 2),
        std::make_tuple(std::vector<int>{100, 492}, std::vector<int>{300, 592}, 6)
    };
    while(menuid == 0){

        window.clearScreen();
        InterfaceMenuP(window, get<0>(Screen_size), get<1>(Screen_size));
        window.finishFrame();
        events(window, clickablepool, menuid);
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
    }
}

void Options(MinGL &window, vector<tuple<vector<int>, vector<int>, int>> clickablepool, tuple <int, int> Screen_size, int & menuid, chrono::time_point<chrono::steady_clock> start){
    clickablepool.clear();
    clickablepool = {
        std::make_tuple(std::vector<int>{0, 0}, std::vector<int>{120, 50}, 0)
    };

    while(menuid == 1){

        window.clearScreen();
        InterfaceOptions(window, get<0>(Screen_size), get<1>(Screen_size));
        window.finishFrame();
        events(window, clickablepool, menuid);
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

    }
}

void Credits(MinGL &window, vector<tuple<vector<int>, vector<int>, int>> clickablepool,
             tuple <int, int> Screen_size, int & menuid, chrono::time_point<chrono::steady_clock> start){
    clickablepool.clear();
    clickablepool = {
        std::make_tuple(std::vector<int>{0, 0}, std::vector<int>{120, 50}, 0)
    };

    while(menuid == 2){

        InterfaceCredits(window, get<0>(Screen_size), get<1>(Screen_size));
        window.finishFrame();
        events(window, clickablepool, menuid);
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
    }
}

void Pause(MinGL &window, vector<tuple<vector<int>, vector<int>, int>> clickablepool,
           tuple <int, int> Screen_size, int & menuid, chrono::time_point<chrono::steady_clock> start){
    clickablepool.clear();
    clickablepool = {
        std::make_tuple(std::vector<int>{100, 48}, std::vector<int>{300, 148}, 4),
        std::make_tuple(std::vector<int>{100, 196}, std::vector<int>{300, 296}, 5),
        std::make_tuple(std::vector<int>{100, 344}, std::vector<int>{300, 444}, 0),
        };

    while(menuid == 3){
        InterfacePause(window, get<0>(Screen_size), get<1>(Screen_size));
        window.finishFrame();
        events(window, clickablepool, menuid);
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

    }
}

void GameLoop(MinGL &window, vector<tuple<vector<int>, vector<int>, int>>clickablepool,CMat Mat, int menuid, unsigned PartyNum,
              bool Key_UP, bool Key_DOWN, bool Key_RIGHT, bool Key_LEFT, tuple <int, int> Screen_size, CMyParamV2 param,
              bool Victory, unsigned KMaxPartyNum, CPosition PosPlayer1, CPosition PosPlayer2, CPosition PosTP1,
              CPosition PosTP2, bool Player1Turn, pair<char,CPosition> N_move, vector<char> objetJ1, vector<char> objetJ2,
              int scoreJ1, int scoreJ2, vector <CPosition> PosMonster){
    clickablepool.clear();
    clickablepool = {
                     std::make_tuple(std::vector<int>{0, 0}, std::vector<int>{120, 50}, 1),
                     };
    window << nsShape::Rectangle(nsGraphics::Vec2D(0, 0), nsGraphics::Vec2D(120, 50), nsGraphics::KBlue);

    DisplayGrid(window, Mat, Screen_size);
    window.finishFrame();

    while(PartyNum <= KMaxPartyNum && !Victory && window.isOpen() && (menuid == 4)){

        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
        window.clearScreen();
        DisplayGrid(window, Mat, Screen_size);
        window.finishFrame();

        Key_RIGHT = window.MinGL::isPressed({param.KeyRight,false}) || window.MinGL::isPressed({toupper(param.KeyRight),false});
        Key_LEFT  = window.MinGL::isPressed({param.KeyLeft, false}) || window.MinGL::isPressed({toupper(param.KeyLeft), false});
        Key_UP    = window.MinGL::isPressed({param.KeyUp,   false}) || window.MinGL::isPressed({toupper(param.KeyUp),   false});
        Key_DOWN  = window.MinGL::isPressed({param.KeyDown, false}) || window.MinGL::isPressed({toupper(param.KeyDown), false});
        if (Key_UP || Key_DOWN){
            Key_RIGHT = false;
            Key_LEFT  = false;
        }

        cout << IsMoveLegal(Mat, Key_UP, Key_DOWN, Key_RIGHT, Key_LEFT, PosPlayer1, param) << Key_UP << Key_DOWN << Key_RIGHT << Key_LEFT << endl;

        if ((Key_UP || Key_DOWN || Key_RIGHT || Key_LEFT) &&
            IsMoveLegal(Mat, Key_UP, Key_DOWN, Key_RIGHT, Key_LEFT, PosPlayer1, param)){
            cout << "move" << endl;
            N_move = nextMove(Mat, Key_UP, Key_DOWN, Key_RIGHT, Key_LEFT, PosPlayer1, param, PosTP1, PosTP2);

            // check si il ya un objet => ajouter a une liste
            if(IsCollectible(N_move.first))
            {
                if(Player1Turn == 1) objetJ1.push_back(N_move.first);
                if(Player1Turn == 0) objetJ2.push_back(N_move.first);
            }

            // check si joueur arrive a la maison => vide ses poches (comptage du score)
            if (!Player1Turn && N_move.second.first == param.NbRow - 1 && N_move.second.second == 0)
                CalculateScore(objetJ2, scoreJ2);

            if (Player1Turn && N_move.second.first == 0 && N_move.second.second == param.NbColumn - 1)
                CalculateScore(objetJ1, scoreJ1);

            MoveToken(Mat, Key_UP, Key_DOWN, Key_RIGHT, Key_LEFT, PosPlayer1, PosTP1, PosTP2);
        }

        //on fait jouer le bot 1fois/2 sinon il aurait trop d'avantage
        if(Player1Turn)
            MoveMonster(PosMonster, Mat, param, PosPlayer1, PosPlayer2);

        Mat[PosPlayer1.first][PosPlayer1.second] = param.tokenP1;
        Mat[PosPlayer2.first][PosPlayer2.second] = param.tokenP2;

        //check if Monster on player

        for(CPosition & posmonst : PosMonster){
            if(posmonst == PosPlayer1 || posmonst == PosPlayer2)
            {
                if(posmonst == PosPlayer1){
                    Mat[PosPlayer1.first][PosPlayer1.second] = param.tokenP1;
                    scoreJ1 = scoreJ1 - (param.NbColumn + param.NbRow)*2;
                }
                if(posmonst == PosPlayer2)
                {
                    Mat[PosPlayer2.first][PosPlayer2.second] = param.tokenP2;
                    scoreJ2 = scoreJ2 - (param.NbColumn + param.NbRow)*2;
                }
                Mat[posmonst.first][posmonst.second] = KEmpty;
                do{
                    //replacer les montres plutot au centre
                    posmonst = CPosition((rand()%param.NbRow/2) + param.NbRow/4,
                                         (rand()%param.NbColumn/2) + param.NbColumn/4);
                }while(Mat[posmonst.first][posmonst.second] != KEmpty);

                Mat[posmonst.first][posmonst.second] = 'A';
            }
        }

        DisplayGrid(Mat, param);

        window.finishFrame();

        events(window, clickablepool, menuid);

        cout << menuid << endl;

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        //Victory test
        if (PosPlayer1 == PosPlayer2) Victory = true;

        if ((scoreJ2 > 0 && size_t(scoreJ2) > (param.NbColumn+param.NbRow)*15)) Victory = true;
        if ((scoreJ1 > 0  && size_t(scoreJ1) > (param.NbColumn+param.NbRow)*15 )) Victory = true;

        //Increase party's number
        ++PartyNum;

        //Player changing
        Player1Turn = !Player1Turn;

    }//while(no victory)

    if (scoreJ1 == scoreJ2){
        Color (KColor.find("KMAgenta")->second);
        cout << "Égalité : Aucun vainqueur" << endl;
        menuid = 0;
    }else{
        Color (KColor.find("KGreen")->second);
        cout << "Félicitations Joueur " << (scoreJ1 > scoreJ2 ? '1' : '2') <<
            " vous avez gagné avec " << (scoreJ1 > scoreJ2 ? scoreJ1 : scoreJ2) << " points!"
             <<"Tandis que l'horrible Joueur "<< (scoreJ1 > scoreJ2 ? '2' : '1') << " ne possède QUE "<< (scoreJ1 > scoreJ2 ? scoreJ1 : scoreJ2) << " points" << endl;
        Color (KColor.find("KReset")->second);
    }

}

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
    const unsigned KMaxPartyNum (param.NbColumn * param.NbRow * 3);
    int scoreJ1 = 0, scoreJ2 = 0;
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
    CMat Mat;

    //création des variable pour les touches

    bool Key_UP = false;
    bool Key_DOWN = false;
    bool Key_RIGHT = false;
    bool Key_LEFT = false;

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
            MenuP(window, clickablepool, Screen_size, menuid, start);
            break;

        case 1: //Options
            Options(window, clickablepool, Screen_size, menuid, start);
            break;

        case 2: //Credits
            Credits(window, clickablepool, Screen_size, menuid, start);
            break;

        case 3: //Pause
            Pause(window, clickablepool, Screen_size, menuid, start);
            break;

        case 4: //Jeu
            GameLoop(window, clickablepool,Mat, menuid, PartyNum,
                          Key_UP, Key_DOWN, Key_RIGHT, Key_LEFT, Screen_size, param,
                          Victory, KMaxPartyNum, PosPlayer1, PosPlayer2, PosTP1,
                          PosTP2, Player1Turn, N_move, objetJ1, objetJ2,
                          scoreJ1, scoreJ2, PosMonster);
            InitGrid(Mat, param.NbRow, param.NbColumn, PosPlayer1, PosPlayer2, param, PosTP1, PosTP2, PosMonster);
            menuid = 0;
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
