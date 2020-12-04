 #include "classTelescope_part_tripod.h"




void _teleTripod::draw(int style, float alpha, float beta, float gamma)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glTranslated(0,0.9,0);
        this->__mount.draw(style, alpha, beta, gamma);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0,0,0.5);
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
