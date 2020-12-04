#include "classTelescope_part_lens.h"


void _teleLens::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glTranslatef(3.25,0,0);
        glScaled(0.25,0.85,0.85);
        this->lens.draw(style);
    glPopMatrix();
}
