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
 * @brief Set the material for the Tripod. Red Plastic.
 */
void _teleTripod::setMaterial()
{
    _vertex4f ambient = _vertex4f(0.0f, 0.0f, 0.0f, 1),
              diffuse = _vertex4f(0.5f, 0.0f, 0.0f, 1),
              specular = _vertex4f(0.7, 0.6, 0.6, 1);
    float shine = 25.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}
