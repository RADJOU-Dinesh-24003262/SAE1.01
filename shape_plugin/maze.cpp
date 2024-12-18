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

using namespace std;

const char kTokenPlayer1 = 'X';
const char kTokenPlayer2 = 'O';
const char kEmpty        = '_';

typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille
typedef pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille

//défini les éléments du sprite du joueur 2
void Player1Sprite(MinGL &window, int grid_x, int grid_y, int pos_x, int pos_y){
    //calcule la position de la tuile
    int Point1_1 = (grid_x*pos_x);
    int Point1_2 = (grid_x*pos_y);
    int Point2_1 = (grid_y*(pos_x+1));
    int Point2_2 = (grid_y*(pos_y+1));
    window << nsShape::Rectangle(nsGraphics::Vec2D(Point1_1,Point1_2),
                                 nsGraphics::Vec2D(Point2_1,Point2_2),
                                 nsGraphics::KYellow);
    //calcul de la position du personnage
    int Circle1 = Point1_1+((Point2_1-Point1_1)/2);
    int Circle2 = Point1_2+((Point2_2-Point1_2)/2);
    //shape formant le sprite
    window << nsShape::Oval(nsGraphics::Vec2D(Point1_1+20,Point1_2+25), nsGraphics::Vec2D(13,8), nsGraphics::KMaroon);// panard droit
    window << nsShape::Oval(nsGraphics::Vec2D(Point1_1+20,Point1_2+42), nsGraphics::Vec2D(13,8), nsGraphics::KMaroon);// panard gauche
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1, Circle2-17), 9, nsGraphics::KMaroon);  //epaule droite
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1, Circle2+17), 9, nsGraphics::KMaroon);  //epaule gauche
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1, Circle2), 20, nsGraphics::KBlue);    //contenant de gras
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1-10, Circle2-5), 2, nsGraphics::KBlack);   //oeil droit
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1-10, Circle2+5), 2, nsGraphics::KBlack);   //oeil gauche

}

//défini les éléments du sprite du joueur 1
void Player2Sprite(MinGL &window, int grid_x, int grid_y, int pos_x, int pos_y){
    //calcule la position de la tuile
    int Point1_1 = (grid_x*pos_x);
    int Point1_2 = (grid_x*pos_y);
    int Point2_1 = (grid_y*(pos_x+1));
    int Point2_2 = (grid_y*(pos_y+1));
    window << nsShape::Rectangle(nsGraphics::Vec2D(Point1_1,Point1_2),
                                 nsGraphics::Vec2D(Point2_1,Point2_2),
                                 nsGraphics::KRed);
}

//défini les éléments du sprite du mur
void WallSprite(MinGL &window, int grid_x, int grid_y, int pos_x, int pos_y){
    //calcule la position de la tuile
    int Point1_1 = (grid_x*pos_x);
    int Point1_2 = (grid_x*pos_y);
    int Point2_1 = (grid_y*(pos_x+1));
    int Point2_2 = (grid_y*(pos_y+1));
    window << nsShape::Rectangle(nsGraphics::Vec2D(Point1_1,Point1_2),
                                 nsGraphics::Vec2D(Point2_1,Point2_2),
                                 nsGraphics::KGreen);
}

//défini les éléments du sprite du sol
void FloorSprite(MinGL &window, int grid_x, int grid_y, int pos_x, int pos_y){
    //calcule la position de la tuile
    int Point1_1 = (grid_x*pos_x);
    int Point1_2 = (grid_x*pos_y);
    int Point2_1 = (grid_y*(pos_x+1));
    int Point2_2 = (grid_y*(pos_y+1));
    window << nsShape::Rectangle(nsGraphics::Vec2D(Point1_1,Point1_2),
                                 nsGraphics::Vec2D(Point2_1,Point2_2),
                                 nsGraphics::KTransparent);
}


void dessiner(MinGL &window)
{
    // window << nsShape::Circle(nsGraphics::Vec2D(0, 0), 10, nsGraphics::KYellow);
    // window << nsShape::Triangle(nsGraphics::Vec2D(TriP1_1, 320), nsGraphics::Vec2D(TriP2_1, TriP2_2), nsGraphics::Vec2D(TriP3_1, TriP3_2), nsGraphics::KBlack);
    // draw_oval(window, tuple <int, int>(310,300), tuple <int, int>(60,40), 50);
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
                Player1Sprite(window, grid_x, grid_y, i, j);
                break;
            case 'O':
                Player2Sprite(window, grid_x, grid_y, i, j);
                break;
            case 'M':
                WallSprite(window, grid_x, grid_y, i, j);
                break;
            default:
                FloorSprite(window, grid_x, grid_y, i, j);
            }
        }
    }
}

int main()
{
    // Initialise le système
    tuple <int, int> Screen_size(640,640);
    MinGL window("01 - Shapes", nsGraphics::Vec2D(get<0>(Screen_size), get<1>(Screen_size)), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();


    CPosition size (10,10);
    //CMatrix mat (size.first, CVLine (size.second, '1'));
    CMatrix mat (size.first, CVLine (size.second, '_'));
    mat[3][4] = 'X';
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
        //dessiner(window);
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
