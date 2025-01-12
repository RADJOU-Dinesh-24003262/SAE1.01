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

/**
 * @brief cette fonction dessine un monstre sous forme de rectangle
 * @param window Référence à l'objet MinGL pour dessiner les formes.
 * @param Circle1 Position x du centre du monstre.
 * @param Circle2 Position y du centre du monstre.
 * @param mat_x Facteur d'échelle pour la dimension horizontale du rectangle.
 * @param mat_y Facteur d'échelle pour la dimension verticale du rectangle.
 */


//défini les éléments du sprite d'un mur
void Monstre(MinGL &window, int Circle1, int Circle2, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    int wall_x = 320/mat_x;
    int wall_y = 320/mat_y;

    //shape formant le sprite
    window << nsShape::Rectangle(nsGraphics::Vec2D((Circle1-wall_x),(Circle2-wall_y)), nsGraphics::Vec2D((Circle1+wall_x),(Circle2+wall_y)), nsGraphics::KMaroon);// square
}
