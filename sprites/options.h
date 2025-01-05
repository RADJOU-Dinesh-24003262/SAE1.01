/**
 *
 * @file    menupause.h
 * @author
 * @date    January 2025
 * @version 1.0
 * @brief   Appearance of pause menu
 *
 **/

//include les différentes formes pour dessiner les sprites
#include "mingl/shape/rectangle.h"
// #include "mingl/shape/circle.h"
// #include "mingl/shape/line.h"
// #include "mingl/shape/triangle.h"
// #include "mingl/shape/oval.h"

//défini les éléments du sprite d'un mur
void Options(MinGL &window, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    window << nsShape::Rectangle(nsGraphics::Vec2D((0,0)), mat_x, mat_y, nsGraphics::KGray);
    window << nsShape::Rectangle(nsGraphics::Vec2D((0,0)), 120, 50, nsGraphics::KRed+8, nsGraphics::KTransparent);
    window << nsShape::Rectangle(nsGraphics::Vec2D((150,150)), 340, 340, nsGraphics::KTransparent, nsGraphics::KGray);
}
