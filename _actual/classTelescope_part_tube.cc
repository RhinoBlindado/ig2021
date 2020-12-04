#include <classTelescope_part_tube.h>

void _teleTube::draw(int style, float beta, float gamma)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glRotatef(beta,0,0,1);

        this->focusTube.draw(style, gamma);
        this->eyePiece.draw(style);

        glTranslated(-0.75,0,0);
        glRotated(90,0,0,1);
        glScaled(1.15,5,1.15);

        glColor3f(0.5,0,0);
        this->tube.draw(style);
    glPopMatrix();
}
