/**
 *
 * @file    oval.cpp
 * @author  Matisse QUILLIEC
 * @date    December 2024
 * @version 1.0
 * @brief   Représente un oval
 *
 **/

#include <cmath>

#include "mingl/shape/oval.h"
#include "mingl/macros.h"

nsShape::Oval::Oval(const nsGraphics::Vec2D &position, const nsGraphics::Vec2D &radius, const nsGraphics::RGBAcolor &fillColor, const nsGraphics::RGBAcolor &borderColor)
    : Shape(fillColor, borderColor)
    , m_position(position)
    , m_radius(radius)
{} // Oval()

void nsShape::Oval::draw(MinGL& window) const
{
    UNUSED(window);

    // Source: https://gist.github.com/linusthe3rd/803118

    int i;
    int triangleAmount = 20; // Nombre de triangles a dessiner

    // On règle la couleur du oval
    const nsGraphics::RGBAcolor inColor = getFillColor();
    glColor4ub(inColor.getRed(), inColor.getGreen(), inColor.getBlue(), inColor.getAlpha()); // Couleur du oval

    GLfloat twicePi = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(m_position.getX(), m_position.getY()); // Centre du oval

    for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(m_position.getX() + (m_radius.getX() * cos(i * twicePi / triangleAmount)),
                   m_position.getY() + (m_radius.getY() * sin(i * twicePi / triangleAmount)));
    }

    glEnd();

    if (getBorderColor() != nsGraphics::KTransparent) {
        // On a une bordure, on l'affiche
        const nsGraphics::RGBAcolor borderColor = getBorderColor();
        glColor4ub(borderColor.getRed(), borderColor.getGreen(), borderColor.getBlue(), borderColor.getAlpha());
        glLineWidth(1.f);

        glBegin(GL_LINE_LOOP);

        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(m_position.getX() + (m_radius.getX() * cos(i * twicePi / triangleAmount)),
                       m_position.getY() + (m_radius.getY() * sin(i * twicePi / triangleAmount)));
        }

        glEnd();
    }
} // draw()

void nsShape::Oval::getValues(const int &id, std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_FILL_COLOR_RGB:
            values[0] = m_fillColor.getRed();
            values[1] = m_fillColor.getGreen();
            values[2] = m_fillColor.getBlue();

            break;

        case TRANSITION_FILL_COLOR_ALPHA:
            values[0] = m_fillColor.getAlpha();

            break;

        case TRANSITION_BORDER_COLOR_RGB:
            values[0] = m_borderColor.getRed();
            values[1] = m_borderColor.getGreen();
            values[2] = m_borderColor.getBlue();

            break;

        case TRANSITION_BORDER_COLOR_ALPHA:
            values[0] = m_borderColor.getAlpha();

            break;

        case TRANSITION_POSITION:
            values[0] = m_position.getX();
            values[1] = m_position.getY();

            break;

        case TRANSITION_RADIUS:
            values[0] = m_radius.getX();
            values[0] = m_radius.getY();

            break;
    }
} // getValues()

void nsShape::Oval::setValues(const int &id, const std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_FILL_COLOR_RGB:
            m_fillColor.setRed(values[0]);
            m_fillColor.setGreen(values[1]);
            m_fillColor.setBlue(values[2]);

            break;

        case TRANSITION_FILL_COLOR_ALPHA:
            m_fillColor.setAlpha(values[0]);

            break;

        case TRANSITION_BORDER_COLOR_RGB:
            m_borderColor.setRed(values[0]);
            m_borderColor.setGreen(values[1]);
            m_borderColor.setBlue(values[2]);

            break;

        case TRANSITION_BORDER_COLOR_ALPHA:
            m_borderColor.setAlpha(values[0]);

            break;

        case TRANSITION_POSITION:
            m_position.setX(values[0]);
            m_position.setY(values[1]);

            break;

        case TRANSITION_RADIUS:
            m_radius.setX(values[0]);
            m_radius.setY(values[1]);

            break;
    }
} // setValues()

nsShape::Oval nsShape::Oval::operator+(const nsGraphics::Vec2D& position) const
{
    return Oval(m_position + position, m_radius, getFillColor(), getBorderColor());
} // operator+()

nsShape::Oval nsShape::Oval::operator*(const float& f) const
{
    return Oval(m_position * f, m_radius, getFillColor(), getBorderColor());
} // operator*()

const nsGraphics::Vec2D& nsShape::Oval::getRadius() const
{
    return m_radius;
} // getRadius()

void nsShape::Oval::setRadius(const nsGraphics::Vec2D &radius)
{
    m_radius = radius;
} // setRadius()

const nsGraphics::Vec2D& nsShape::Oval::getPosition() const
{
    return m_position;
} // getPosition()

void nsShape::Oval::setPosition(const nsGraphics::Vec2D &position)
{
    m_position = position;
} // setPosition()
