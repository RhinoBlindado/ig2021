 #include "classTelescope_part_mount.h"

/**
 * @brief Initialization of the objects and angle.
 */
_teleMount::_teleMount()
{
    this->mount2.initialize(1, 0.5, 10, 8, 30);
    this->mount1.initialize(1, 0.5, 20, 20, 20);
}

/**
 * @brief _teleMount::draw
 * @param style     Style of drawing style.
 */
void _teleMount::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslated(0,0.9,0);
        glScaled(1.5,1.5,1.5);
        glColor3f(0.5,0,0.5);
        this->setMaterial();
        this->mount1.draw(style);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,0.05,0);
        glScaled(2,0.25,2);
        glColor3f(0.75,0,0.75);
        this->setMaterial();
        this->mount2.draw(style);
    glPopMatrix();

}

/** [P4]
 * @brief _teleMount::setLighting
 * @param type      Type of lighting.
 */
void _teleMount::setLighting(int type)
{
    mount1.setLighting(type);
    mount2.setLighting(type);
}

/** [P4]
 * @brief Set the material for the Mount. Gold.
 */
void _teleMount::setMaterial()
{
    _vertex3f ambient = _vertex3f(0.24725f, 0.1995f, 0.0745f),
              diffuse = _vertex3f(0.75164f, 0.60648f, 0.22648f),
              specular = _vertex3f(0.628281f, 0.555802f, 0.366065f);
    float shine = 51.2f / 10;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}

