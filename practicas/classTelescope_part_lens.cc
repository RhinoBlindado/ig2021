#include "classTelescope_part_lens.h"

/**
 * @brief Initialization of the object.
 */
_teleLens::_teleLens()
{
    this->lens.initialize(0.5, 20, 20);
}

/**
 * @brief _teleLens::draw
 * @param style     Style of drawing.
 */
void _teleLens::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glTranslatef(3.25,0,0);
        glScaled(0.25,0.85,0.85);
        this->setMaterial();
        this->lens.draw(style);
    glPopMatrix();
}

/** [P4]
 * @brief _teleLens::setLighting
 * @param type      Type of lighting.
 */
void _teleLens::setLighting(int type)
{
    lens.setLighting(type);
}

/**
 * @brief Set the material for the lens. Turquoise.
 */
void _teleLens::setMaterial()
{
    _vertex4f ambient = _vertex4f(0.1f, 0.18725f, 0.1745f, 1),
              diffuse = _vertex4f(0.396f, 0.74151f, 0.69102f, 1),
              specular = _vertex4f(0.297254f, 0.30829f, 0.306678f, 1);
    float shine = 12.8f / 10;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

}
