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
// #include "mingl/shape/circle.h"
// #include "mingl/shape/line.h"
// #include "mingl/shape/triangle.h"
// #include "mingl/shape/oval.h"

//défini les éléments du sprite d'un mur
void Monstre(MinGL &window, int Circle1, int Circle2, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    int wall_x = 320/mat_x;
    int wall_y = 320/mat_y;

    //shape formant le sprite
    window << nsShape::Rectangle(nsGraphics::Vec2D((Circle1-wall_x),(Circle2-wall_y)), nsGraphics::Vec2D((Circle1+wall_x),(Circle2+wall_y)), nsGraphics::KMaroon);// square
}
