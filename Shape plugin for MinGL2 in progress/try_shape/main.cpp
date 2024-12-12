#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <cmath>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include <tuple>

using namespace std;

void draw_oval(MinGL &window, tuple <int, int> pos, tuple <int, int> size, int resolution){
    float degre = 2 * M_PI / resolution;
    for (int i=0; i < resolution; ++i){
        //calcul des positions des différents points avec sinus
        float TriP1_1 = (get<0>(size)*(cos(degre*(i+0))))+300;
        float TriP1_2 = (get<1>(size)*(sin(degre*(i+0))))+300;
        if (i == resolution-1){i = 0;}
        float TriP2_1 = get<0>(pos)+(get<1>(size)/2);
        float TriP2_2 = get<1>(pos)+(get<1>(size)/2);
        float TriP3_1 = get<0>(size)*(cos(degre*(i+1)))+300;
        float TriP3_2 = get<1>(size)*(sin(degre*(i+1)))+300;
        window << nsShape::Triangle(nsGraphics::Vec2D(TriP1_1,TriP1_2),
                                    nsGraphics::Vec2D(TriP2_1,TriP2_2),
                                    nsGraphics::Vec2D(TriP3_1,TriP3_2),
                                    nsGraphics::KBlue
                                    );
    }
}

void dessiner(MinGL &window)
{
    // window << nsShape::Circle(nsGraphics::Vec2D(CirP1, 320), 10, nsGraphics::KYellow);
    // window << nsShape::Triangle(nsGraphics::Vec2D(TriP1_1, 320), nsGraphics::Vec2D(TriP2_1, TriP2_2), nsGraphics::Vec2D(TriP3_1, TriP3_2), nsGraphics::KBlack);
    draw_oval(window, tuple <int, int>(300,300), tuple <int, int>(100,200), 100);

}

int main()
{
    // Initialise le système
    MinGL window("01 - Shapes", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les formes géométriques
        dessiner(window, mouth, move);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(2500 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
