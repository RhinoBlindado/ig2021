/*  ESPAÑOL
    Titulo: Práctica 3
    Fecha: 07/11/2020
    Autor: Valentino Lugli
    Versión: 0.1
    Descripción: Realización de un modelo jerárquico de 5 niveles.
    Opciones: N/A
    Uso: Generar un telescopio hecho de formas básicas.
*/
/*
    ENGLISH
    Title: Practice 3
    Date: 07/11/2020
    Author: Valentino Lugli
    Version: 0.1
    Description: Making a hierarchical model with 5 levels.
    Options: N/A
    Usage: Making a telescope made out of basic shapes.
*/

//  Libraries
#include "classTelescope.h"
#include "object3d.h"
#include "classCylinder.h"
#include "classSphere.h"
#include "cube.h"

//  Classes

class _teleLens:public _object3D
{
    public:
        _teleLens(){};
        void draw_fill()
        {
            _sphere lens(0.5, 20, 20);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
                glTranslatef(2.75,0,0);
                glScaled(0.95,0.95,0.95);
                lens.draw_fill();
                glColor3f(0,0,0);
            glPopMatrix();
        }
};

class _teleEyePiece:public _object3D
{
    public:
        _teleEyePiece(){};
};

class _teleFocusTube:public _object3D
{
   public:
        _teleFocusTube(){};

        void draw_fill()
        {
            _cylinder focusTube(1,0.5,12,2,10,false,false);
            _teleLens lens;

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
                lens.draw_fill();
                glTranslated(2,0,0);
                glRotated(90,0,0,1);
                glScaled(1,2,1);
                focusTube.draw_fill();
            glPopMatrix();
        }
};

class _teleTube:public _object3D
{
    public:
        _teleTube(){};

        void draw_fill()
        {
            _cylinder tube(1,0.5,12,2,10,false,false);
            _teleFocusTube focusTube;

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
                focusTube.draw_fill();
                glTranslated(-1.5,0,0);
                glRotated(90,0,0,1);
                glScaled(1.15,5,1);
                tube.draw_fill();
            glPopMatrix();
        }
};

class _teleMount:public _object3D
{
    public:
        _teleMount();
};

class _teleTripod:public _object3D
{
    public:
        _teleTripod();
};

void _telescope::draw_fill()
{
   // _teleLens a;
   // _teleFocusTube b;
    _teleTube c;
    c.draw_fill();
   // a.draw_fill();
}
