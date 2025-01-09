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
#include "mingl/shape/oval.h"

//défini les éléments du sprite d'un mur
void Statue(MinGL &window, int Center1, int Center2, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    float wall_x = 320/mat_x;
    float wall_y = 320/mat_y;
    float ratio = mat_x/10;
    float body_size       = wall_x/2.8;
    float body_x          = Center1;
    float body_y          = (5/ratio) + Center2;
    float foot_size_x     = body_size/(2/ratio);
    float foot_size_y     = body_size/(8/ratio);
    float foot1_x         = Center1 - (5/ratio);
    float foot2_x         = Center1 + (5/ratio);
    float foot_y          = (5/ratio) + Center2 + (9/ratio);
    float TopSocle1_x     = Center1 - body_size;
    float TopSocle1_y     = (5/ratio) + Center2 + (10/ratio);
    float TopSocle2_x     = Center1 + body_size;
    float TopSocle2_y     = (5/ratio) + Center2 + (11/ratio);
    float DownSocle1_x    = TopSocle1_x - (3/ratio);
    float DownSocle1_y    = TopSocle2_y;
    float DownSocle2_x    = TopSocle2_x + (3/ratio);
    float DownSocle2_y    = TopSocle2_y + (5/ratio);
    float Hand_size_x     = body_size/3;
    float Hand_size_y     = body_size/2;
    float Hand1_x         = TopSocle1_x;
    float Hand2_x         = TopSocle2_x;
    float Hand_y          = (5/ratio) + Center2 - (5/ratio);
    float Shoulder1_x     = Center1 - body_size;
    float Shoulder1_y     = (5/ratio) + Center2 - body_size;
    float Shoulder2_x     = Center1 + body_size;
    float Shoulder2_y     = (5/ratio) + Center2 - (body_size/2);
    float LeftBretelle1_x = Center1 - (body_size/2) - (1/ratio);
    float RightBretelle1_x= Center1 + (body_size/2) - (1/ratio);
    float Bretelle1_y     = Shoulder1_y;
    float LeftBretelle2_x = Center1 - (body_size/2) + (1/ratio);
    float RightBretelle2_x= Center1 + (body_size/2) + (1/ratio);
    float Bretelle2_y     = Shoulder2_y;
    float LeftButton_x    = LeftBretelle1_x + ((LeftBretelle2_x-LeftBretelle1_x)/2);
    float RightButton_x   = RightBretelle1_x + ((RightBretelle2_x-RightBretelle1_x)/2);
    float Button_y        = Bretelle2_y;
    float Button_size     = (2/ratio);
    float Head_size       = (8/ratio);
    float Head_x          = Center1;
    float Head_y          = (5/ratio) + Center2 - body_size - (2*(Head_size/3));
    float TopHat_size_x   = Head_size+1;
    float TopHat_size_y   = 2*(Head_size/5);
    float TopHat_x        = Center1;
    float TopHat_y        = Head_y - Head_size + (2/ratio);
    float DownHat_size_x  = Head_size;
    float DownHat_size_y  = TopHat_size_y/3;
    float DownHat_x       = Center1;
    float DownHat_y       = TopHat_y + TopHat_size_y;

    //shape formant le sprite
    window << nsShape::Rectangle(nsGraphics::Vec2D((Center1-wall_x),(Center2-wall_y)), nsGraphics::Vec2D((Center1+wall_x),(Center2+wall_y)), nsGraphics::KBlack);// square
    window << nsShape::Oval(nsGraphics::Vec2D(Hand1_x,Hand_y), nsGraphics::Vec2D(Hand_size_x,Hand_size_y), nsGraphics::KBeige);// pied droit
    window << nsShape::Oval(nsGraphics::Vec2D(Hand2_x,Hand_y), nsGraphics::Vec2D(Hand_size_x,Hand_size_y), nsGraphics::KBeige);// pied droit
    window << nsShape::Circle(nsGraphics::Vec2D(body_x,body_y), body_size, nsGraphics::KPurple);  //ventre
    window << nsShape::Oval(nsGraphics::Vec2D(foot1_x,foot_y), nsGraphics::Vec2D(foot_size_x,foot_size_y), nsGraphics::KGreen);// pied gauche
    window << nsShape::Oval(nsGraphics::Vec2D(foot2_x,foot_y), nsGraphics::Vec2D(foot_size_x,foot_size_y), nsGraphics::KGreen);// pied droit
    window << nsShape::Rectangle(nsGraphics::Vec2D(TopSocle1_x,TopSocle1_y), nsGraphics::Vec2D(TopSocle2_x,TopSocle2_y), nsGraphics::KGray);// haut du socle
    window << nsShape::Rectangle(nsGraphics::Vec2D(DownSocle1_x,DownSocle1_y), nsGraphics::Vec2D(DownSocle2_x,DownSocle2_y), nsGraphics::KGray);// bas du socle
    window << nsShape::Rectangle(nsGraphics::Vec2D(Shoulder1_x,Shoulder1_y), nsGraphics::Vec2D(Shoulder2_x,Shoulder2_y), nsGraphics::KYellow);// épaule
    window << nsShape::Rectangle(nsGraphics::Vec2D(LeftBretelle1_x,Bretelle1_y), nsGraphics::Vec2D(LeftBretelle2_x,Bretelle2_y), nsGraphics::KPurple);// bretelle
    window << nsShape::Rectangle(nsGraphics::Vec2D(RightBretelle1_x,Bretelle1_y), nsGraphics::Vec2D(RightBretelle2_x,Bretelle2_y), nsGraphics::KPurple);// bretelle
    window << nsShape::Circle(nsGraphics::Vec2D(LeftButton_x, Button_y), Button_size, nsGraphics::KWhite);  //bouton gauche
    window << nsShape::Circle(nsGraphics::Vec2D(RightButton_x, Button_y), Button_size, nsGraphics::KWhite);  //bouton droit
    window << nsShape::Circle(nsGraphics::Vec2D(Head_x,Head_y), Head_size, nsGraphics::KBeige);  //tête
    window << nsShape::Oval(nsGraphics::Vec2D(TopHat_x, TopHat_y), nsGraphics::Vec2D(TopHat_size_x,TopHat_size_y), nsGraphics::KYellow);// casquette
    window << nsShape::Oval(nsGraphics::Vec2D(DownHat_x, DownHat_y), nsGraphics::Vec2D(DownHat_size_x,DownHat_size_y), nsGraphics::KWhite);// visière de la casquette

}
