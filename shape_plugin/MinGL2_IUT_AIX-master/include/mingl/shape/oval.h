/**
 *
 * @file    oval.h
 * @author  Matisse Quilliec
 * @date    December 2024
 * @version 1.0
 * @brief   Représente un oval
 *
 **/

#ifndef OVAL_H
#define OVAL_H

#include "shape.h"

#include "../transition/itransitionable.h"

namespace nsShape
{

/**
 * @class Oval
 * @brief Classe représentant un Oval
 */
class Oval : public Shape, public nsTransition::ITransitionable
{

public:
    /**
     * @brief TransitionIds : Liste de toutes les transitions que cet élément peut exécuter
     */
    enum TransitionIds {
        TRANSITION_FILL_COLOR_RGB, /**< Transition pour la couleur de remplissage */
        TRANSITION_FILL_COLOR_ALPHA, /**< Transition pour la transparence de remplissage */
        TRANSITION_BORDER_COLOR_RGB, /**< Transition pour la couleur de bord */
        TRANSITION_BORDER_COLOR_ALPHA, /**< Transition pour la transparence de bord */
        TRANSITION_POSITION, /**< Transition pour la position */
        TRANSITION_RADIUS, /**< Transition pour le rayon */
    };

    /**
     * @brief Constructeur pour la classe Oval
     * @param[in] firstPosition : Position du centre
     * @param[in] radius : Rayon du oval
     * @param[in] fillColor : Couleur de remplissage
     * @param[in] borderColor : Couleur de bord
     * @fn Oval(const nsGraphics::Vec2D& position, const nsGraphics::Vec2D& radius, const nsGraphics::RGBAcolor& fillColor, const nsGraphics::RGBAcolor& borderColor = nsGraphics::KTransparent);
     */
    Oval(const nsGraphics::Vec2D& position, const nsGraphics::Vec2D& radius, const nsGraphics::RGBAcolor& fillColor, const nsGraphics::RGBAcolor& borderColor = nsGraphics::KTransparent);

    /**
     * @brief Destructeur virtuel pour la classe Oval
     * @fn virtual ~Oval() override = default;
     */
    virtual ~Oval() override = default;

    virtual void draw(MinGL& window) const override;

    virtual void getValues(const int &id, std::vector<float> &values) override;
    virtual void setValues(const int &id, const std::vector<float> &values) override;

    /**
     * @brief Opérateur de décalage
     * @param[in] position : Position a additionner
     * @fn Oval operator+(const nsGraphics::Vec2D& position) const
     */
    Oval operator+(const nsGraphics::Vec2D& getPosition) const;

    /**
     * @brief Opérateur de réduction
     * @param[in] f : Nombre avec lequel multiplier la position actuelle
     * @fn Oval operator*(const float& f) const
     */
    Oval operator*(const float& f) const;

    /**
     * @brief Récupère la position de l'oval
     * @fn const nsGraphics::Vec2D& getPosition() const;
     */
    const nsGraphics::Vec2D& getPosition() const;

    /**
     * @brief Définit la nouvelle position de l'oval
     * @param[in] position : Nouvelle position
     * @fn void setPosition(const nsGraphics::Vec2D &position);
     */
    void setPosition(const nsGraphics::Vec2D &position);

    /**
     * @brief Récupère le rayon de l'oval
     * @fn const nsGraphics::Vec2D getRadius() const;
     */
    const nsGraphics::Vec2D& getRadius() const;

    /**
     * @brief Définit le nouveau rayon de l'oval
     * @param[in] radius : Nouveau rayon
     * @fn void setRadius(const nsGraphics::Vec2D &radius);
     */
    void setRadius(const nsGraphics::Vec2D &radius);

private:
    /**
     * @brief m_position : Position du centre
     */
    nsGraphics::Vec2D m_position;

    /**
     * @brief m_radius : Rayon du oval
     */
    nsGraphics::Vec2D m_radius;

}; // class Oval

} // namespace nsShape

#endif // OVAL_H
