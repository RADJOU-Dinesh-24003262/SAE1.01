#include <string>
#include "params.h"
//#include "game.h" not use for the moment
#include <fstream>
#include <iostream>

using namespace std;

void initParams (CMyParamV2 & Param){
    //Move Keys
    Param.KeyUp = 'z';
    Param.KeyDown = 's';
    Param.KeyRight = 'd';
    Param.KeyLeft = 'q';

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

        if(key == "KeyUp"){
            ifs >> Param.KeyUp;

        }else if(key == "KeyDown"){
            ifs >> Param.KeyDown;

        }else if(key == "KeyLeft"){
            ifs >> Param.KeyLeft;

        }else if(key == "KeyRight"){
            ifs >> Param.KeyRight;

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
