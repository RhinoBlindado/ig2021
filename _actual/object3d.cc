/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "object3d.h"

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
        for(unsigned int i=0; i<Triangles.size();i++)
        {
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
        for(unsigned int i=0; i<Triangles.size();i++)
        {
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess(vector<float> color1, vector<float> color2)
{
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
        for(unsigned int i=0; i<Triangles.size();i++)
        {
            if(i%2 == 0)
                 glColor3f(color1[0],color1[1],color1[2]);
            else
                 glColor3f(color2[0],color2[1],color2[2]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
    glEnd();
}
