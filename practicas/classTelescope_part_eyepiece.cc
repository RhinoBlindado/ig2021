#include "classTelescope_part_eyepiece.h"

/**
 * @brief Initialize the model.
 */
_teleEyePiece::_teleEyePiece()
{
    this->eyePiece.initialize(1, 0.5, 5, 10, 30, true, true);
}

/**
 * @brief _teleEyePiece::draw
 * @param style     Style of drawing.
 */
void _teleEyePiece::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glTranslated(-3.75,0,0);
        glRotated(90,0,0,1);
        glScaled(0.75,1,0.75);

        glColor3f(0.75,0.75,0);
        this->setMaterial();
        this->eyePiece.draw(style);
    glPopMatrix();
}

/** [P4]
 * @brief _teleEyePiece::setLighting
 * @param type      Type of lighting.
 */
void _teleEyePiece::setLighting(int type)
{
    eyePiece.setLighting(type);
}

/** [P4]
 * @brief Set the material for the Eye Piece. Chrome.
 */
void _teleEyePiece::setMaterial()
{
    _vertex4f ambient = _vertex4f(0.25f, 0.25f, 0.25f, 1),
              diffuse = _vertex4f(0.4f, 0.4f, 0.4f, 1),
              specular = _vertex4f(0.774597f, 0.774597f, 0.774597f, 1);
    float shine = 76.8f / 10;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

}
