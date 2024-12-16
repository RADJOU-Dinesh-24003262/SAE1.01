#include <iostream>
#include <math.h>
#include "gridmanagement.h"

#include "type.h" //nos types


using namespace std;


//void translation

//void inversion

// forme (structure ou variable global)

void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
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
            else{
                cout << c;
            }
        }
        cout << '|' << endl;
    }
    cout << string (KNbCol + 2 , '-') << endl;
}// ShowMatrix ()


void InitGrid (CMat & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2, const CMyParamV2 & Param ){
    Mat.resize (NbLine);
    const CVLine KLine (NbColumn, KEmpty);
    for (CVLine &ALine : Mat)
        ALine = KLine;

    srand(time(0));
    // for (unsigned i = 0; i < pow(NbLine,0.5) * 2; ++i) // trouver calcul nbr
    // {

    //     v2 = rand();
    //     v1 = rand();
    //     v1 = v1%(NbLine-2)+1;
    //     v2 = v2%(NbColumn-2)+1;
    //     Mat[v1][v2] = 'M';
    //     cout << v1 << "  " << v2 << endl;
    //     v3 = v3 + time(0);

    unsigned x,y = 0;
    for (size_t i = 0; i < NbLine; i = i + 5)
    {
        for (size_t j = 0; j < NbColumn; j = j+5)
        {
            for (unsigned p = 0; p < 2; ++p)
            {
                x = x + rand();
                y = y + rand();
                x = x%(5-1);
                y = y%(5-1);
                Mat[i+x][j+y] = 'M';

            }
        }
    }


    //     cout << v3%2 << "test";

    //     switch(v3%2)
    //     {
    //         case 0:
    //         Mat[v1][v2+1] = 'M';
    //         Mat[v1+1][v2] = 'M';
    //         v3 = v3 + time(0);
    //         break;
    //         case 1:
    //         Mat[v1][v2-1] = 'M';
    //         Mat[v1-1][v2] = 'M';
    //         v3 = v3 + time(0);
    //         break;
    //     }

    PosPlayer1.first = 0;
    PosPlayer1.second = NbColumn - 1;
    Mat [PosPlayer1.first][PosPlayer1.second] = Param.tokenP1;
    PosPlayer2.first = NbLine - 1;
    PosPlayer2.second =0;
    Mat [PosPlayer2.first][PosPlayer2.second] = Param.tokenP2;
}//InitMat ()


