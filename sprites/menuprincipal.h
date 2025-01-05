/**
 *
 * @file    menuprincipal.h
 * @author
 * @date    January 2025
 * @version 1.0
 * @brief   Appearance of principal menu
 *
 **/

//include les différentes formes pour dessiner les sprites
#include "mingl/shape/rectangle.h"
// #include "mingl/shape/circle.h"
// #include "mingl/shape/line.h"
// #include "mingl/shape/triangle.h"
// #include "mingl/shape/oval.h"

//défini les éléments du sprite d'un mur
void MenuPrincipal(MinGL &window, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    window << nsShape::Rectangle(nsGraphics::Vec2D(0,0), mat_x, mat_y, nsGraphics::KGray);
    window << nsShape::Rectangle(nsGraphics::Vec2D(100, 48), 200, 100, nsGraphics::KBlack);
    window << nsShape::Rectangle(nsGraphics::Vec2D(100, 196), 200, 100, nsGraphics::KBlack);
    window << nsShape::Rectangle(nsGraphics::Vec2D(100, 344), 200, 100, nsGraphics::KBlack);
    window << nsShape::Rectangle(nsGraphics::Vec2D(100, 492), 200, 100, nsGraphics::KBlack);
    }
