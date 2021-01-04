#include "classTelescope_part_focusTube.h"


/**
 * @brief Initialization of object and angle.
 */
_teleFocusTube::_teleFocusTube()
{
    this->focusTube.initialize(1, 0.5, 2, 20, 30, false, false);
    gamma = 0;
}

/**
 * @brief _teleFocusTube::draw
 * @param style     Type of drawing.
 */
void _teleFocusTube::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glRotated(gamma*10,1,0,0);
        glTranslated(gamma/10,0,0);

        this->lens.draw(style);
        glTranslated(2,0,0);
        glRotated(90,0,0,1);
        glScaled(1,2.5,1);

        glColor3f(1,0,0);
        this->setMaterial();
        this->focusTube.draw(style);
    glPopMatrix();
}

/**
 * @brief _teleFocusTube::setGamma
 * @param nGamma        New angle for 3rd degree of freedom.
 */
void _teleFocusTube::setGamma(float nGamma )
{
    this->gamma = nGamma;
}

/** [P4]
 * @brief _teleFocusTube::setLighting
 * @param type      Type of lighting.
 */
void _teleFocusTube::setLighting(int type)
{
    focusTube.setLighting(type);
    lens.setLighting(type);
}

/** [P4]
 * @brief Set the material for the Tube. Brass.
 */
void _teleFocusTube::setMaterial()
{
    _vertex3f ambient = _vertex3f(0.329412f, 0.223529f, 0.027451f),
              diffuse = _vertex3f(0.780392f, 0.568627f, 0.113725f),
              specular = _vertex3f(0.992157f, 0.941176f, 0.807843f);
    float shine = 27.8974f / 10;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

}
