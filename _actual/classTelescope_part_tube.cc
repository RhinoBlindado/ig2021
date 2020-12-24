#include <classTelescope_part_tube.h>

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
            this->tube.draw(style);
        glPopMatrix();


      glPopMatrix();
}

void _teleTube::setAlpha(float nAlpha)
{
    this->alpha = nAlpha;
}

void _teleTube::setBeta(float nBeta)
{
    this->beta = nBeta;
}

void _teleTube::setGamma(float nGamma)
{
    focusTube.setGamma(nGamma);
}
