/**
 *
 * @file    wall.h
 * @author  Matisse Quilliec
 * @date    December 2024
 * @version 1.0
 * @brief   Affiche le sprite d'un mur
 *
 **/

//include les différentes formes pour dessiner les sprites
//#include "mingl/shape/rectangle.h"
#include "sprites/button.h"
// #include "mingl/shape/circle.h"
// #include "mingl/shape/line.h"
// #include "mingl/shape/triangle.h"
// #include "mingl/shape/oval.h"

//défini les éléments du sprite d'un mur
void Teleporter(MinGL &window, int Pos1, int Pos2, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    int wall_x = 320/mat_x;
    int wall_y = 320/mat_y;
    int x1 = (Pos1-wall_x);
    int x2 = (Pos1+wall_y);
    int y1 = (Pos2-wall_x);
    int y2 = (Pos2+wall_y);
    int difx = (x2-x1)/20;
    int dify = (y2-y1)/20;

    //shape formant le sprite
    Button(window, (x1+(2*(difx))), (y1+(2*(dify))), (x2-(2*(difx))), (y2-(2*(dify))), 5, nsGraphics::KDarkGray);
    Button(window, (x1+(4*(difx))), (y1+(4*(dify))), (x2-(4*(difx))), (y2-(4*(dify))), 2, nsGraphics::KGray);
    //window << nsShape::Rectangle(nsGraphics::Vec2D((Circle1-wall_x),(Circle2-wall_y)), nsGraphics::Vec2D((Circle1+wall_x),(Circle2+wall_y)), nsGraphics::KPurple);// square
}
