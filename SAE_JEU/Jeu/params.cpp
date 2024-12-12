#include <string>
#include "params.h"
#include "game.h"
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
    ifstream ifs;
    ifs.open(Path);
    if (!ifs.is_open ()){
        cerr << "File not found" << endl;
        return;
    }

    string key;
    while (true){

        ifs >> key;
        if (ifs.eof ()) break;
        string tampon;

        if(key == "KeyUp"){
            char val;
            ifs >> tampon;
            ifs >> val;
            Param.KeyUp = val;

        }else if(key == "KeyDown"){
            char val1;
            ifs >> tampon;
            ifs >> val1;
            Param.KeyDown = val1;

        }else if(key == "KeyLeft"){
            char val2;
            ifs >> tampon;
            ifs >> val2;
            Param.KeyLeft = val2;

        }else if(key == "KeyRight"){
            char val3;
            ifs >> tampon;
            ifs >> val3;
            Param.KeyRight = val3;

        }else if(key == "NbColumn"){
            size_t val4;
            ifs >> tampon;
            ifs >> val4;
            cout << val4;
            Param.NbColumn = val4;

        }else if(key == "NbRow"){
            size_t val5;
            ifs >> tampon;
            ifs >> val5;
            cout << val5;
            Param.NbRow = val5;

        }else if(key == "ColorP1"){
            string val6;
            ifs >> tampon;
            ifs >> val6;
            Param.ColorP1 = val6;

        }else if(key == "ColorP2"){
            string val7;
            ifs >> tampon;
            ifs >> val7;
            Param.ColorP2 = val7;

        }else if(key == "TokenP1"){
            char val8;
            ifs >> tampon;
            ifs >> val8;
            Param.tokenP1 = val8;
            break;

        }else if(key == "TokenP2"){
            char val9;
            ifs >> tampon;
            ifs >> val9;
            Param.tokenP2 = val9;
        }
    }
    ifs.close ();
}
