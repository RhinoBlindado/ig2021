#include "classTelescope_part_focusTube.h"

void _teleFocusTube::draw(int style, float gamma)
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
        this->focusTube.draw(style);
    glPopMatrix();
}
