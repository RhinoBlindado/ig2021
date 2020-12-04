#include "classTelescope_part_eyepiece.h"

void _teleEyePiece::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glTranslated(-3.75,0,0);
        glRotated(90,0,0,1);
        glScaled(0.75,1,0.75);

        glColor3f(0.75,0.75,0);
        this->eyePiece.draw(style);
    glPopMatrix();
}
