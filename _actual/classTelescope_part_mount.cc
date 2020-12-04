 #include "classTelescope_part_mount.h"

_teleMount::_teleMount()
{
    this->mount2.initialize(1,0.5,2,6,8);
    this->mount1.initialize(1,0.5,1,1,6);
}

void _teleMount::draw(int style,  float alpha, float beta, float gamma)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

        glTranslated(0,1,0);
        glRotatef(alpha,0,1,0);
        this->__tube.draw(style, beta, gamma);
    glPopMatrix();

    glPushMatrix();
        glScaled(1.5,1.5,1.5);
        glColor3f(0.5,0,0.5);
        this->mount1.draw(style);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-0.85,0);
        glScaled(2,0.25,2);
        glColor3f(0.75,0,0.75);
        this->mount2.draw(style);
    glPopMatrix();
}
