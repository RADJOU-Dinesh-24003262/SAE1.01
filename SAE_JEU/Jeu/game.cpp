#include <iostream>

#include "game.h"
#include "params.h"
#include "gridmanagement.h"

#include <map>
using namespace std;


void MoveToken (CMat & Mat, const char & Move, CPosition & Pos, CMyParamV2 & Param)
{
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;

    // cout << Mat.size() << "  " << Mat[0]


    if (Move == Param.KeyUp){
        --Pos.first;
    }else if (Move == Param.KeyDown){
        ++Pos.first;
    }else if (Move == Param.KeyRight){
        ++Pos.second;
    }else if(Move == Param.KeyLeft){
        --Pos.second;
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


int ppal (void)
{
    CMyParamV2 param;
    initParams(param);
    LoadParams(param);

    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (param.NbColumn * param.NbRow);
    CMat Mat;

    bool Player1Turn (true);
    bool Victory (false);

    CPosition PosPlayer1, PosPlayer2;


    InitGrid(Mat, param.NbRow, param.NbColumn, PosPlayer1, PosPlayer2, param);

    DisplayGrid (Mat, param);

    while (PartyNum <= KMaxPartyNum && ! Victory)
    {

        cout << "tour numero : " << PartyNum << ", Joueur "
             << (Player1Turn ? '1' : '2') << ", entrez un déplacement : ";

        char Move;
        cin >> Move;

        Move = tolower (Move);
        MoveToken (Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param);
        // ClearScreen();
        DisplayGrid (Mat, param);

        //Victiry test
        if (PosPlayer1 == PosPlayer2) Victory = true;

        //Increase party's number
        ++PartyNum;

        //Player changing
        Player1Turn = !Player1Turn;

    }//while (no victory)

    if (!Victory)
    {
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
