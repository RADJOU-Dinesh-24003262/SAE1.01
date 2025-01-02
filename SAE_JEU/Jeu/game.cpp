#include <iostream>
#include <vector>

#include <unistd.h>

#include "game.h"
#include "params.h"
#include "gridmanagement.h"

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
        cout << "Illegal Move, Play again ! " << endl;
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

    // switch (Move)
    // {
    // case 'A':
    //     -- Pos.first;
    //     -- Pos.second;
    //     break;
    // case 'Z':
    //     --Pos.first;
    //     break;
    // case 'E':
    //     --Pos.first;
    //     ++Pos.second;
    //     break;
    // case 'Q':
    //     --Pos.second;
    //     break;
    // case 'D':
    //     ++Pos.second;
    //     break;
    // case 'W':
    //     ++Pos.first;
    //     --Pos.second;
    //     break;
    // case 'X':
    //     ++Pos.first;
    //     break;
    // case 'C':
    //     ++Pos.first;
    //     ++Pos.second;
    //     break;
    // }
    Mat [Pos.first][Pos.second] = car;

} //MoveToken ()

int scoreJ1 = 0, scoreJ2 = 0;

int ppal (void){
    CMyParamV2 param;
    initParams(param);
    LoadParams(param);

    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (param.NbColumn * param.NbRow);
    CMat Mat;

    bool Player1Turn (true);
    bool Victory (false);

    CPosition PosPlayer1, PosPlayer2, PosTP1, PosTP2;


    vector <CPosition> PosMonster;

    InitGrid(Mat, param.NbRow, param.NbColumn, PosPlayer1, PosPlayer2, param, PosTP1, PosTP2, PosMonster);
    //ClearScreen();
    DisplayGrid(Mat, param);

    vector<char> objetJ1;
    vector<char> objetJ2;

    pair<char,CPosition> N_move;

    while (PartyNum <= KMaxPartyNum && ! Victory){

        char Move;
        string temp;
        //ask to the player the move to do till it's legal
        do{
            //cout << Mat[param.NbRow - 1][0] << " J2" << endl;
            //cout << Mat[0][param.NbColumn - 1] << " J1" << endl;
            cout << "Score J1: " << scoreJ1 << ", Score J2: " << scoreJ2 << endl;
            cout << "tour numero : " << PartyNum << ", Joueur "
                 << (Player1Turn ? '1' : '2') << ", entrez un déplacement : ";
            getline(cin, temp);
            Move = temp[0];
            Move = tolower(Move);

        }while(not IsMoveLegal(Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param));

        N_move = nextMove(Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param, PosTP1, PosTP2);

        // check si il ya un objet => ajouter a une liste
        if(IsCollectible(N_move.first))
        {
            if(Player1Turn == 1) objetJ1.push_back(N_move.first);
            if(Player1Turn == 0) objetJ2.push_back(N_move.first);
        }

        // check si joueur arrive a la maison => vide ses poches (comptage du score)

        if (!Player1Turn && N_move.second.first == param.NbRow - 1 && N_move.second.second == 0) {
            scoreJ2 += objetJ2.size() * 100;
            objetJ2.clear();
        }

        if (Player1Turn && N_move.second.first == 0 && N_move.second.second == param.NbColumn - 1) {
            scoreJ1 += objetJ1.size() * 100;
            objetJ1.clear();
        }


        MoveToken (Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param, PosTP1, PosTP2);
        if(Player1Turn)
            MoveMonster(PosMonster, Mat, param);


        //ClearScreen();
        DisplayGrid (Mat, param);

        //Victory test
        if (PosPlayer1 == PosPlayer2) Victory = true;
        bool playdead = false;
        for (const CPosition & posmont : PosMonster) {
            if(posmont == PosPlayer1 || posmont == PosPlayer2) playdead = true;
        }
        if(playdead) break;

        //Increase party's number
        ++PartyNum;

        //Player changing
        Player1Turn = !Player1Turn;

    }//while (no victory)

    if (!Victory){
        Color (KColor.find("KMAgenta")->second);
        cout << "Aucun vainqueur" << endl;
        return 1;
    }

    Color (KColor.find("KGreen")->second);
    cout << "Félicitations Joueur " << (Player1Turn ? '2' : '1')
         << " vous avez gagné :)" << endl;
    Color (KColor.find("KReset")->second);
    return 0;
} //ppal ()
