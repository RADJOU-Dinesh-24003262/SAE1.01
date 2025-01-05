/**
 *
 * @file    player1.h
 * @author  Matisse Quilliec
 * @date    December 2024
 * @version 1.0
 * @brief   Affiche le sprite du player 1
 *
 **/

//include les différentes formes pour dessiner les sprites
// #include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
// #include "mingl/shape/line.h"
// #include "mingl/shape/triangle.h"
#include "mingl/shape/oval.h"

//défini les éléments du sprite du joueur 1
void Player1(MinGL &window, int Circle1, int Circle2, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    int foot_x = 110/mat_x;
    int foot_y = 80/mat_y;
    int foot_x_size = 100/mat_x;
    int foot_y_size = 70/mat_y;
    int should_y = 170/mat_y;
    int should_size = 90/mat_x;
    int body_size = 180/mat_x;
    int eye_x = 130/mat_x;
    int eye_y = 50/mat_y;
    int eye_size = 20/mat_x;

    //shape formant le sprite
    window << nsShape::Oval(nsGraphics::Vec2D(Circle1-foot_x,Circle2-foot_y), nsGraphics::Vec2D(foot_x_size,foot_y_size), nsGraphics::KMaroon);// panard droit
    window << nsShape::Oval(nsGraphics::Vec2D(Circle1-foot_x,Circle2+foot_y), nsGraphics::Vec2D((100/mat_x),(70/mat_y)), nsGraphics::KMaroon);// panard gauche
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1, Circle2-should_y), should_size, nsGraphics::KMaroon);  //epaule droite
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1, Circle2+should_y), should_size, nsGraphics::KMaroon);  //epaule gauche
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1, Circle2), body_size, nsGraphics::KBlue);    //contenant de gras
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1-eye_x, Circle2-eye_y), eye_size, nsGraphics::KBlack);   //oeil droit
    window << nsShape::Circle(nsGraphics::Vec2D(Circle1-eye_x, Circle2+eye_y), eye_size, nsGraphics::KBlack);   //oeil gauche
}
