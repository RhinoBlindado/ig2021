/*  ESPAÑOL
    Titulo: Práctica 3
    Fecha: 07/11/2020
    Autor: Valentino Lugli
    Versión: 0.1
    Descripción: Realización de un modelo jerárquico de 5 niveles.
    Uso: Generar un telescopio hecho de formas básicas.

    ENGLISH
    Title: Practice 3
    Date: 07/11/2020
    Author: Valentino Lugli
    Version: 0.1
    Description: Making a hierarchical model with 5 levels.
    Usage: Making a telescope made out of basic shapes.
*/

//  Libraries
#include "classTelescope.h"
#include "object3d.h"
#include "classCylinder.h"
#include "classSphere.h"
#include "cube.h"
#include "tetrahedron.h"
#include "classCone.h"

//  Classes
class _teleLens:public _object3D
{
    private:
        _sphere lens{0.5, 20, 20};

    public:
        _teleLens(){};
        void draw_fill()
        {
            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
                glTranslatef(2.75,0,0);
                glScaled(0.95,0.95,0.95);
                this->lens.draw_fill();
            glPopMatrix();
        }
};

class _teleFocusTube:public _object3D
{
   private:
        _cylinder focusTube{1,0.5,12,2,10,false,false};
        _teleLens lens;

   public:
        _teleFocusTube(){};

        void draw_fill()
        {
            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
                this->lens.draw_fill();
                glTranslated(2,0,0);
                glRotated(90,0,0,1);
                glScaled(1,2,1);

                glColor3f(1,0,0);
                this->focusTube.draw_fill();
            glPopMatrix();
        }
};


class _teleEyePiece:public _object3D
{
    private:
        _cylinder eyePiece{1,0.5,12,2,10,true,true};

    public:
        _teleEyePiece(){};
        void draw_fill()
        {
            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
                glTranslated(-4.5,0,0);
                glRotated(90,0,0,1);
                glScaled(0.75,1,0.75);

                glColor3f(0.75,0.75,0);
                this->eyePiece.draw_fill();
            glPopMatrix();
        }
};


class _teleTube:public _object3D
{
    private:
        _cylinder tube{1,0.5,12,2,10};
        _teleFocusTube focusTube;
        _teleEyePiece eyePiece;

    public:
        _teleTube(){};

        void draw_fill()
        {
            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
                // Draw the next figure in hierarchy.
                glTranslated(0.75,0,0);
                this->focusTube.draw_fill();
                this->eyePiece.draw_fill();

                // Apply transformations, bottom first.
                glTranslated(-1.5,0,0);
                glRotated(90,0,0,1);
                glScaled(1.15,5,1.15);

                // Draw piece.
                glColor3f(0.5,0,0);
                this->tube.draw_fill();
            glPopMatrix();
        }
};

class _teleMount:public _object3D
{
    private:
        _cone mount1{1,0.5,1,1,6};
        _cylinder mount2{1,0.5,6,1,8};
        _teleTube __tube;

    public:
        _teleMount(){};
        void draw_fill()
        {
            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
                this->__tube.draw_fill();
                glTranslated(0,-1,0);
                glScaled(1.5,1.5,1.5);
                glColor3f(0.5,0,0.5);
                this->mount1.draw_fill();
            glPopMatrix();

            glPushMatrix();
                glTranslated(0,-1.75,0);
                glScaled(2,0.25,2);
                glColor3f(0.75,0,0.75);
                this->mount2.draw_fill();
            glPopMatrix();
        }
};

class _teleTripod:public _telescope
{
    private:
        _cube feet;
        _teleMount __mount;

    public:
        _teleTripod(){};
        void draw_fill()
        {
            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
                glTranslated(0,1.75,0);
                this->__mount.draw_fill();
            glPopMatrix();

            glPushMatrix();
                glColor3f(0,0,0.5);
                glPushMatrix();
                    glTranslated(1.5,-2.25,0);
                    glRotated(25,0,0,1);
                    glScaled(0.5,5,0.5);
                    this->feet.draw_fill();
                glPopMatrix();

                glPushMatrix();
                    glRotated(120,0,1,0);
                    glTranslated(1.5,-2.25,0);
                    glRotated(25,0,0,1);
                    glScaled(0.5,5,0.5);
                    this->feet.draw_fill();
                glPopMatrix();

                glPushMatrix();
                    glRotated(-120,0,1,0);
                    glTranslated(1.5,-2.25,0);
                    glRotated(25,0,0,1);
                    glScaled(0.5,5,0.5);
                    this->feet.draw_fill();
                glPopMatrix();
            glPopMatrix();
        }
};

void _telescope::draw_fill()
{
    _teleTripod c;
    c.draw_fill();
}