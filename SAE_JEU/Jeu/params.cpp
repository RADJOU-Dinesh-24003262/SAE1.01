#include <string>
#include "params.h"
//#include "game.h" not use for the moment
#include <fstream>
#include <iostream>

using namespace std;

void initParams (CMyParamV2 & Param){
    //Move Keys
    Param.Key1Up = 'z';
    Param.Key1Down = 's';
    Param.Key1Right = 'd';
    Param.Key1Left = 'q';
    Param.Key2Up = 'o';
    Param.Key2Down = 'l';
    Param.Key2Right = 'm';
    Param.Key2Left = 'k';

    Param.tokenP1 = 'A';
    Param.tokenP2 = 'X';

    //Size of grid — suppose to be a rectangle
    Param.NbColumn = 10;
    Param.NbRow = 5;

    //Display Colors
    Param.ColorP1 = KColor.find("KRed")->second ;
    Param.ColorP2 = KColor.find("KBlue")->second ;
}

void LoadParams (CMyParamV2 & Param){
    string Path = "../../Nos_fichiers/config.yaml";
    ifstream ifs(Path);
    if (!ifs.is_open ()){
        cerr << "File not found" << endl;
        exit(-1);
    }

    for(string key, tampon; !ifs.eof(); ifs >> key){
        ifs >> tampon;

        if(key == "Key1Up"){
            ifs >> Param.Key1Up;

        }else if(key == "Key1Down"){
            ifs >> Param.Key1Down;

        }else if(key == "Key1Left"){
            ifs >> Param.Key1Left;

        }else if(key == "Key1Right"){
            ifs >> Param.Key1Right;

        }else if(key == "Key2Up"){
            ifs >> Param.Key2Up;

        }else if(key == "Key2Down"){
            ifs >> Param.Key2Down;

        }else if(key == "Key2Left"){
            ifs >> Param.Key2Left;

        }else if(key == "Key2Right"){
            ifs >> Param.Key2Right;

        }else if(key == "NbColumn"){
            ifs >> Param.NbColumn;

        }else if(key == "NbRow"){
            ifs >> Param.NbRow;

        }else if(key == "ColorP1"){
            ifs >> Param.ColorP1;

        }else if(key == "ColorP2"){
            ifs >> Param.ColorP2;

        }else if(key == "TokenP1"){
            ifs >> Param.tokenP1;

        }else if(key == "TokenP2"){
            ifs >> Param.tokenP2;
        }
        else{
            getline(ifs, tampon);
        }
    }
    ifs.close ();
}
