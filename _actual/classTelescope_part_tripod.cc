 #include "classTelescope_part_tripod.h"

/**
 * @brief _teleTripod::draw
 * @param style     Style of drawing style.
 */
void _teleTripod::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glColor3f(0,0,0.5);
        this->setMaterial();
        glPushMatrix();
            glTranslated(1.5,-2.25,0);
            glRotated(25,0,0,1);
            glScaled(0.5,5,0.5);
            this->feet.draw(style);
        glPopMatrix();

        glPushMatrix();
            glRotated(120,0,1,0);
            glTranslated(1.5,-2.25,0);
            glRotated(25,0,0,1);
            glScaled(0.5,5,0.5);
            this->feet.draw(style);
        glPopMatrix();

        glPushMatrix();
            glRotated(-120,0,1,0);
            glTranslated(1.5,-2.25,0);
            glRotated(25,0,0,1);
            glScaled(0.5,5,0.5);
            this->feet.draw(style);
        glPopMatrix();
    glPopMatrix();
}

/** [P4]
 * @brief _teleTripod::setLighting
 * @param type      Type of Lighting.
 */
void _teleTripod::setLighting(int type)
{
    feet.setLighting(type);
}

/**
 * @brief Set the material for the Tripod. Ruby.
 */
void _teleTripod::setMaterial()
{
    _vertex3f ambient = _vertex3f(0.1745f, 0.01175f, 0.01175f),
              diffuse = _vertex3f(0.61424f, 0.04136f, 0.04136f),
              specular = _vertex3f(0.727811f, 0.626959f, 0.626959f);
    float shine = 76.8f / 10;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}
