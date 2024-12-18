#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <cmath>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/shape/oval.h"
#include <tuple>
#include "sprites/player1.h"
#include "sprites/player2.h"
#include "sprites/wall.h"

using namespace std;

const char kTokenPlayer1 = 'X';
const char kTokenPlayer2 = 'O';
const char kEmpty        = '_';

typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille
typedef pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille

//défini les éléments du sprite
void Sprite(MinGL &window, int grid_x, int grid_y, int pos_x, int pos_y, int mat_x, int mat_y, string sprite){
    //calcule la position de la tuile
    int Point1_1 = (grid_x*pos_x);
    int Point1_2 = (grid_x*pos_y);
    int Point2_1 = (grid_y*(pos_x+1));
    int Point2_2 = (grid_y*(pos_y+1));
    //calcul de la position centrale du personnage
    int Circle1 = Point1_1+((Point2_1-Point1_1)/2);
    int Circle2 = Point1_2+((Point2_2-Point1_2)/2);

    //affiche le sprite correspondant a l'élément de la case
    if (sprite == "player1")Player1(window, Circle1, Circle2, mat_x, mat_y);
    if (sprite == "player2")Player2(window, Circle1, Circle2, mat_x, mat_y);
    if (sprite == "wall")Wall(window, Circle1, Circle2, mat_x, mat_y);
}

void DisplayGrid (MinGL &window, const CMatrix & mat, tuple <int, int> Screen_size){
    int mat_x = size(mat);
    int mat_y = size(mat[0]);

    int grid_x = get<0>(Screen_size)/mat_x;
    int grid_y = get<1>(Screen_size)/mat_y;

    for (int i=0; i < mat_x; ++i){
        for (int j=0; j < mat_y; ++j){
            switch (mat[i][j]){
            case 'X':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "player1");
                break;
            case 'O':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "player2");
                break;
            case 'M':
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "wall");
                break;
            default:
                Sprite(window, grid_x, grid_y, i, j, mat_x, mat_y, "floor");
            }
        }
    }
}

int main()
{
    // Initialise le système
    tuple <int, int> Screen_size(640,640);
    MinGL window("Lethal Company  |  V0.0.1", nsGraphics::Vec2D(get<0>(Screen_size), get<1>(Screen_size)), nsGraphics::Vec2D(128, 128), nsGraphics::KWhite);
    window.initGlut();
    window.initGraphic();


    CPosition size (10,10);
    //CMatrix mat (size.first, CVLine (size.second, '1'));
    CMatrix mat (size.first, CVLine (size.second, '_'));
    mat[0][0] = 'X';
    mat[2][3] = 'O';
    mat[1][0] = 'M';

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les formes géométriques
        DisplayGrid(window, mat, Screen_size);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(2500 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
}
