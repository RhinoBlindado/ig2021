/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "object3d.h"
#include <cmath>

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
            glNormal3f(Normals[i].x, Normals[i].y, Normals[i].z);

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

            glNormal3f(Normals[i].x, Normals[i].y, Normals[i].z);

            glVertex3f(Vertices[Triangles[i]._0].x, Vertices[Triangles[i]._0].y, Vertices[Triangles[i]._0].z);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
    glEnd();
}

// Practice 3
void _object3D::draw(int style)
{
    switch(style)
    {
        case 0:
            this->draw_point();
        break;

        case 1:
            this->draw_line();
        break;

        case 2:
            this->draw_fill();
        break;

        case 3:
            this->draw_chess();
        break;

        default:
            cout<<"Object 3D: Out of range type of draw style"<<endl;
            exit(1);
    }
}


// Practice 4
void _object3D::calculateNormals()
{
    int trigSize = Triangles.size();
    _vertex3f  vectorA, vectorB;
    double denominator;

    Normals.resize(trigSize);

    for(auto i=0; i<trigSize; i++)
    {
        //  Vector A = p1 - p0
        vectorA.x = Vertices[Triangles[i]._1].x - Vertices[Triangles[i]._0].x;
        vectorA.y = Vertices[Triangles[i]._1].y - Vertices[Triangles[i]._0].y;
        vectorA.z = Vertices[Triangles[i]._1].z - Vertices[Triangles[i]._0].z;

        // Vector B = p2 - p0
        vectorB.x = Vertices[Triangles[i]._2].x - Vertices[Triangles[i]._0].x;
        vectorB.y = Vertices[Triangles[i]._2].y - Vertices[Triangles[i]._0].y;
        vectorB.z = Vertices[Triangles[i]._2].z - Vertices[Triangles[i]._0].z;

        // Vector Product = A . B
        Normals[i].x = (vectorA.y * vectorB.z) - (vectorA.z * vectorB.y);
        Normals[i].y = (vectorA.z * vectorB.x) - (vectorA.x * vectorB.z);
        Normals[i].z = (vectorA.x * vectorB.y) - (vectorA.y * vectorB.x);

        // Normalization
        // Making the denominator, that is, square root of the Vector Product
        denominator =  sqrt((pow(Normals[i].x, 2)) + (pow(Normals[i].y, 2)) + (pow(Normals[i].z, 2)));

        // Properly normalizing
        Normals[i].x /= denominator;
        Normals[i].y /= denominator;
        Normals[i].z /= denominator;
    }

}

// http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
