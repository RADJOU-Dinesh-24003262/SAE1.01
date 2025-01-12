/**
 *
 * @file    wall.h
 * @author  Matisse Quilliec
 * @date    Janvier 2025
 * @version 1.0
 * @brief   Affiche le sprite d'un bouton
 *
 **/

//include les différentes formes pour dessiner les sprites
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"

/**
 * @brief cette fonction dessine un bouton avec des coins arrondis
 * @param window Référence à l'objet MinGL pour dessiner les formes.
 * @param pos1_x Position x du coin supérieur gauche du bouton.
 * @param pos1_y Position y du coin supérieur gauche du bouton.
 * @param pos2_x Position x du coin inférieur droit du bouton.
 * @param pos2_y Position y du coin inférieur droit du bouton.
 * @param round Rayon des coins arrondis du bouton. Si ce rayon est plus grand que la moitié de la largeur du bouton, il sera ajusté.
 * @param color Couleur du bouton
 *
 */

//défini les éléments du sprite d'un mur
void Button(MinGL &window, int pos1_x, int pos1_y, int pos2_x, int pos2_y, int round, nsGraphics::RGBAcolor color){

    //calcul variable de position et taille des formes
    if (round > ((pos2_x-pos1_x)/2)){round = (pos2_x-pos1_x)/2;}

    //shape formant le sprite
    window << nsShape::Rectangle(nsGraphics::Vec2D((pos1_x+round),pos1_y), nsGraphics::Vec2D((pos2_x-round),pos2_y), color);
    window << nsShape::Rectangle(nsGraphics::Vec2D(pos1_x,(pos1_y+round)), nsGraphics::Vec2D(pos2_x,(pos2_y-round)), color);
    window << nsShape::Circle(nsGraphics::Vec2D((pos1_x+round),(pos1_y+round)), round, color);
    window << nsShape::Circle(nsGraphics::Vec2D((pos1_x+round),(pos2_y-round)), round, color);
    window << nsShape::Circle(nsGraphics::Vec2D((pos2_x-round),(pos1_y+round)), round, color);
    window << nsShape::Circle(nsGraphics::Vec2D((pos2_x-round),(pos2_y-round)), round, color);
}
