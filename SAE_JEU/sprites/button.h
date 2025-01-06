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
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
// #include "mingl/shape/line.h"
// #include "mingl/shape/triangle.h"
// #include "mingl/shape/oval.h"

//défini les éléments du sprite d'un mur
void Statue(MinGL &window, int pos1_x, int pos1_y, int pos2_x, int pos2_y, int round){

    //calcul variable de position et taille des formes
    if (round > ((pos2_x-pos1_x)/2)){round = (pos2_x-pos1_x)/2;}

    //shape formant le sprite
    window << nsShape::Rectangle(nsGraphics::Vec2D((pos1_x-round),(pos1_y)), nsGraphics::Vec2D((pos1_x-round),(pos1_y)), nsGraphics::KBlack);// square
    window << nsShape::Rectangle(nsGraphics::Vec2D((pos1_x),(pos1_y-round)), nsGraphics::Vec2D((pos1_x),(pos1_y-round)), nsGraphics::KBlack);// bretelle
    window << nsShape::Circle(nsGraphics::Vec2D((pos1_x-round),(pos1_y-round)), round, nsGraphics::KBlack);
    window << nsShape::Circle(nsGraphics::Vec2D((pos1_x-round),(pos2_y-round)), round, nsGraphics::KBlack);
    window << nsShape::Circle(nsGraphics::Vec2D((pos2_x-round),(pos1_y-round)), round, nsGraphics::KBlack);
    window << nsShape::Circle(nsGraphics::Vec2D((pos2_x-round),(pos2_y-round)), round, nsGraphics::KBlack);

}
