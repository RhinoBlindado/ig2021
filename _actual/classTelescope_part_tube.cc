#include <classTelescope_part_tube.h>

/**
 * @brief Initialization of the object and angles.
 */
_teleTube::_teleTube()
{
    this->tube.initialize(1, 0.5, 2, 20, 30);
    alpha = 0;
    beta = 0;
}

/**
 * @brief _teleTube::draw
 * @param style     Style of drawing.
 */
void _teleTube::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glTranslated(0,2,0);
    glRotatef(alpha,0,1,0);

        glPushMatrix();
            glRotatef(beta,0,0,1);

            this->focusTube.draw(style);
            this->eyePiece.draw(style);

            glTranslated(-0.75,0,0);
            glRotated(90,0,0,1);
            glScaled(1.15,5,1.15);

            glColor3f(0.5,0,0);
            this->setMaterial();
            this->tube.draw(style);
        glPopMatrix();


      glPopMatrix();
}

/**
 * @brief _teleTube::setAlpha
 * @param nAlpha    New angle of 1st degree of freedom.
 */
void _teleTube::setAlpha(float nAlpha)
{
    this->alpha = nAlpha;
}

/**
 * @brief _teleTube::setBeta
 * @param nBeta     New angle of 2nd degree of freedom.
 */
void _teleTube::setBeta(float nBeta)
{
    this->beta = nBeta;
}

/**
 * @brief _teleTube::setGamma
 * @param nGamma    New angle of 3rd degree of freedom.
 */
void _teleTube::setGamma(float nGamma)
{
    focusTube.setGamma(nGamma);
}

/** [P4]
 * @brief _teleTube::setLighting
 * @param type      Type of Lighting.
 */
void _teleTube::setLighting(int type)
{
    tube.setLighting(type);
    eyePiece.setLighting(type);
    focusTube.setLighting(type);
}

/** [P4]
 * @brief Set the material of the tube. Polished copper.
 */
void _teleTube::setMaterial()
{
    _vertex4f ambient = _vertex4f(0.2295f, 0.08825f, 0.0275f, 1),
              diffuse = _vertex4f(0.5508f, 0.2118f, 0.066f, 1),
              specular = _vertex4f(0.580594f, 0.223257f, 0.0695701f, 1);
    float shine = 51.2f / 10;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

}
