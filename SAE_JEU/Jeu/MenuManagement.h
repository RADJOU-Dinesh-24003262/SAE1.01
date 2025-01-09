 #ifndef MENUMANAGEMENT_H
#define MENUMANAGEMENT_H

/**
 *
 * @file    menupause.h
 * @author  Alexandre Benhafessa
 * @date    January 2025
 * @version 1.0
 * @brief   The functions to manage main, pause, options, credits menus
 *
 **/

#include "mingl/mingl.h"
#include "vector"

#include "mingl/shape/rectangle.h"
//#include "sprites/button.h"
#include "mingl/gui/text.h"

using namespace std;

#endif // MENUMANAGEMENT_H

/**
 * @brief Display the main menu
 * @param[in] window : Mingl window
 * @param[in] mat_x / mat_y : dimensions of the window
 * @fn void MenuPrincipal(MinGL &window, int mat_x, int mat_y);
 */
void InterfaceMenuP(MinGL &window, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    window << nsShape::Rectangle(nsGraphics::Vec2D(0,0), mat_x, mat_y, nsGraphics::KGray);
    Button(window, 100, 48, 300, 148, 10, nsGraphics::KBlack);
    window << nsGui::Text(nsGraphics::Vec2D (168, 105), "PLAY",nsGraphics::KWhite, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
    Button(window, 100, 196, 300, 296, 10, nsGraphics::KBlack);
    window << nsGui::Text(nsGraphics::Vec2D (145, 253), "In Progress",nsGraphics::KWhite, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
    Button(window, 100, 344, 300, 444, 10, nsGraphics::KBlack);
    window << nsGui::Text(nsGraphics::Vec2D (110, 401), "In Developpement",nsGraphics::KWhite, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
    Button(window, 100, 492, 300, 592, 10, nsGraphics::KBlack);
    window << nsGui::Text(nsGraphics::Vec2D (170, 549), "QUIT",nsGraphics::KWhite, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
}


/**
 * @brief Display the pause menu
 * @param[in] window : Mingl window
 * @param[in] mat_x / mat_y : dimensions of the window
 * @fn void MenuPause(MinGL &window, int mat_x, int mat_y);
 */
void InterfacePause(MinGL &window, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    window << nsShape::Rectangle(nsGraphics::Vec2D(100, 0), mat_x, mat_y, nsGraphics::KGray);
    window << nsShape::Rectangle(nsGraphics::Vec2D(100, 48), 200, 100, nsGraphics::KBlue);
    window << nsShape::Rectangle(nsGraphics::Vec2D(100, 196), 200, 100, nsGraphics::KBlue);
    window << nsShape::Rectangle(nsGraphics::Vec2D(100, 344), 200, 100, nsGraphics::KBlue);
}

/**
 * @brief Display the options menu
 * @param[in] window : Mingl window
 * @param[in] mat_x / mat_y : dimensions of the window
 * @fn void Options(MinGL &window, int mat_x, int mat_y);
 */
void InterfaceOptions(MinGL &window, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    window << nsShape::Rectangle(nsGraphics::Vec2D(0,0), mat_x, mat_y, nsGraphics::KGray);
    window << nsShape::Rectangle(nsGraphics::Vec2D(0,0), 120, 50, nsGraphics::KRed+8, nsGraphics::KTransparent);
    window << nsShape::Rectangle(nsGraphics::Vec2D(150,150), 340, 340, nsGraphics::KTransparent, nsGraphics::KGray);
    window << nsGui::Text(nsGraphics::Vec2D (10, 105),
    "PLAY"
    ,nsGraphics::KWhite, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
}

/**
 * @brief Display the credits screen
 * @param[in] window : Mingl window
 * @param[in] mat_x / mat_y : dimensions of the window
 * @fn void Credits(MinGL &window, int mat_x, int mat_y);
 */
void InterfaceCredits(MinGL &window, int mat_x, int mat_y){

    //calcul variable de position et taille des formes
    window << nsShape::Rectangle(nsGraphics::Vec2D(0,0), mat_x, mat_y, nsGraphics::KGray);
    window << nsShape::Rectangle(nsGraphics::Vec2D(0,0), 120, 50, nsGraphics::KGray+8, nsGraphics::KTransparent);
    window << nsShape::Rectangle(nsGraphics::Vec2D(150,150), 340, 340, nsGraphics::KTransparent, nsGraphics::KGray);
}


nsGraphics::Vec2D rectPos;
nsGraphics::RGBAcolor rectColor = nsGraphics::KCyan;

/**
 * @brief Handle user input events such as mouse movement and clicks for menu navigation
 * @param[in] window : Mingl window
 * @param[in] clickablepool : list of clickable areas with their coordinates and associated menu ID
 * @param[in/out] menuid : current menu ID, which is updated based on user clicks
 * @fn void events(MinGL &window, vector<tuple<vector<int>, vector<int>, int>>& clickablepool, int& menuid)
 */
void events(MinGL &window, vector<tuple<vector<int>, vector<int>, int>>& clickablepool, int& menuid)
{

    while (window.getEventManager().hasEvent())
    {
        const nsEvent::Event_t actualEvent = window.getEventManager().pullEvent();

        // On regarde le type d'évènement
        switch (actualEvent.eventType)
        {
        case nsEvent::EventType_t::MouseMove:
            // Il s'agit d'un mouvement de souris
            rectPos.setX(actualEvent.eventData.moveData.x);
            rectPos.setY(actualEvent.eventData.moveData.y);
            break;

        case nsEvent::EventType_t::MouseClick:
            // Il s'agit d'un clic de souris
            if (actualEvent.eventData.clickData.state) // Clic enfoncé
            {
                for(unsigned i = 0; i < clickablepool.size() ; i = i+1){
                    if (rectPos.getX() >= get<0>(clickablepool[i])[0] && rectPos.getX() <= get<1>(clickablepool[i])[0] &&
                        rectPos.getY() >= get<0>(clickablepool[i])[1] && rectPos.getY() <= get<1>(clickablepool[i])[1]){
                        if (menuid == 4){menuid = 3; break;}
                        menuid = get<2>(clickablepool[i]);
                    }
                }
            }
            else // Relâchement du clic
            {
                rectColor = nsGraphics::KPurple;
            }
            break;

        default:
            // L'évènement ne nous intéresse pas
            break;
        }
    }
}
