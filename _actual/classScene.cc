#include "classScene.h"

_scene::_scene()
{
    _ply a,b,c,d;
        // e,f,g,h,
        // i,j,k,l,
        // m,n,o,p;

    a.initialize(1,"../ply_models/airplane_fixed.ply");
    b.initialize(1,"../ply_models/ant.ply");
    c.initialize(1,"../ply_models/bunny.ply");
    d.initialize(4,"../ply_models/happy.ply");

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glPushMatrix();
            glTranslated(0, 3, 0);
            c.draw_chess();
        glPopMatrix();

        glPushMatrix();
            glTranslated(0,0,-4);
            b.draw_chess();
        glPopMatrix();

        glPushMatrix();
            glTranslated(2,0,0);
            a.draw_chess();
        glPopMatrix();
    glPopMatrix();

}
