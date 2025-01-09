/**
 *
 * @file    cigarette.h
 * @author  Matisse Quilliec
 * @date    December 2024
 * @version 1.0
 * @brief   Affiche le sprite d'une cigarette
 *
 **/

#include "mingl/shape/rectangle.h"
#include "mingl/shape/oval.h"

// Définit les éléments du sprite d'une cigarette

/**
 * @brief cette fonction dessine une cigarette
 * @param window Référence à l'objet MinGL pour dessiner les formes.
 * @param startX Position x du coin supérieur gauche de la cigarette.
 * @param startY Position y du coin supérieur gauche de la cigarette.
 * @param scaleX Facteur d'échelle pour la longueur et la taille horizontale des éléments.
 * @param scaleY Facteur d'échelle pour la largeur et la taille verticale des éléments.
 */

void Cigarette(MinGL &window, int startX, int startY, int scaleX, int scaleY) {
    // Calcul des variables de position et taille des formes
    int cig_length = 350 / scaleX;   // Longueur réduite de la cigarette
    int cig_width = 60 / scaleY;     // Largeur augmentée
    int filter_length = 80 / scaleX; // Longueur du filtre
    int flame_size = 30 / scaleX;    // Taille de la flamme
    int smoke_radius = 35 / scaleX;  // Taille des cercles de fumée

    // Rectangle principal pour le corps de la cigarette (blanc)
    window << nsShape::Rectangle(nsGraphics::Vec2D(startX, startY),
                                 nsGraphics::Vec2D(startX + cig_length, startY + cig_width),
                                 nsGraphics::KGray);

    // Rectangle pour le filtre (jaune-orange)
    window << nsShape::Rectangle(nsGraphics::Vec2D(startX + cig_length - filter_length, startY),
                                 nsGraphics::Vec2D(startX + cig_length, startY + cig_width),
                                 nsGraphics::KRed);

    // Ovale rouge pour simuler l'extrémité allumée de la cigarette
    window << nsShape::Oval(nsGraphics::Vec2D(startX, startY + cig_width / 2),
                            nsGraphics::Vec2D(flame_size, cig_width / 2),
                            nsGraphics::KRed);

    // Fumée (plusieurs ovales gris clair représentant des volutes de fumée)
    window << nsShape::Oval(nsGraphics::Vec2D(startX - smoke_radius * 1.5, startY - cig_width),
                            nsGraphics::Vec2D(smoke_radius * 1.5, smoke_radius),
                            nsGraphics::KGray); // Première volute
    window << nsShape::Oval(nsGraphics::Vec2D(startX - smoke_radius * 3, startY - cig_width * 2),
                            nsGraphics::Vec2D(smoke_radius * 1.3, smoke_radius * 0.9),
                            nsGraphics::KGray); // Deuxième volute
    window << nsShape::Oval(nsGraphics::Vec2D(startX - smoke_radius * 4.5, startY - cig_width * 3),
                            nsGraphics::Vec2D(smoke_radius, smoke_radius * 0.8),
                            nsGraphics::KGray); // Troisième volute
}
