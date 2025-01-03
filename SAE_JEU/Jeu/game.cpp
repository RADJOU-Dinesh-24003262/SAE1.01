#include <iostream>

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
        cout << "Illegal Move, Play again ! ";
        Color (KColor.find("KReset")->second);
        return false;
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
    ClearScreen();
    DisplayGrid(Mat, param);

    while (PartyNum <= KMaxPartyNum && ! Victory){

        char Move;
        string temp;
        //ask to the player the move to do till it's legal
        do{
            cout << "tour numero : " << PartyNum << ", Joueur "
                 << (Player1Turn ? '1' : '2') << ", entrez un déplacement : ";
            getline(cin, temp);
            Move = temp[0];
            Move = tolower(Move);
        }while(not IsMoveLegal(Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param));

        MoveToken (Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), param, PosTP1, PosTP2);
        if(Player1Turn){
            MoveMonster(PosMonster, Mat, param, PosPlayer1, PosPlayer2);
        }

        //ClearScreen();
        DisplayGrid (Mat, param);


        //Victiry test
        if (PosPlayer1 == PosPlayer2) Victory = true;
        bool MonsterEatPLay (false);
        for(const CPosition & posmonst : PosMonster){
            if(posmonst == PosPlayer1 || posmonst == PosPlayer2) MonsterEatPLay = true;
        }
        if(MonsterEatPLay) break;

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
