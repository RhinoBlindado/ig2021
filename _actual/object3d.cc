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

// [P3]
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

        case 4:
            this->drawIlum();
        break;

        case 5:
            this->drawTex();
        break;

        case 6:
            this->drawSelection();
        break;

        default:
            cout<<"Object 3D: Out of range type of draw style"<<endl;
            exit(1);
    }
}


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
            if(this->trigSelectedNumber == (int)i)
                    glColor3fv((GLfloat *) &YEllOW);

            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);

            if(this->trigSelectedNumber == (int)i)
                    glColor3fv((GLfloat *) &BLUE);
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

            glVertex3f(Vertices[Triangles[i]._0].x, Vertices[Triangles[i]._0].y, Vertices[Triangles[i]._0].z);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
    glEnd();
}

void _object3D::drawIlum()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);

        if(flatLight)
            glShadeModel(GL_FLAT);

        if(smoothLight)
            glShadeModel(GL_SMOOTH);

        for(unsigned int i=0; i<Triangles.size();i++)
        {
            if(flatLight)
                glNormal3f(trigNormals[i].x, trigNormals[i].y, trigNormals[i].z);

            if(smoothLight)
                glNormal3f(vectNormals[Triangles[i]._0].x, vectNormals[Triangles[i]._0].y, vectNormals[Triangles[i]._0].z);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

            if(smoothLight)
                glNormal3f(vectNormals[Triangles[i]._1].x, vectNormals[Triangles[i]._1].y, vectNormals[Triangles[i]._1].z);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

            if(smoothLight)
                glNormal3f(vectNormals[Triangles[i]._2].x, vectNormals[Triangles[i]._2].y, vectNormals[Triangles[i]._2].z);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);


        }
    glEnd();
    glDisable(GL_LIGHTING);
}

void _object3D::drawTex()
{

    if(!flatLight && !smoothLight)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    else
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    if(flatLight || smoothLight)
        glEnable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);

    if(flatLight)
        glShadeModel(GL_FLAT);

    if(smoothLight)
        glShadeModel(GL_SMOOTH);

    for(unsigned int i=0; i<Triangles.size();i++)
    {
        if(flatLight)
            glNormal3f(trigNormals[i].x, trigNormals[i].y, trigNormals[i].z);

        if(smoothLight)
            glNormal3f(vectNormals[Triangles[i]._0].x, vectNormals[Triangles[i]._0].y, vectNormals[Triangles[i]._0].z);

        glTexCoord2f(textCoords[Triangles[i]._0].x, textCoords[Triangles[i]._0].y);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

        if(smoothLight)
            glNormal3f(vectNormals[Triangles[i]._1].x, vectNormals[Triangles[i]._1].y, vectNormals[Triangles[i]._1].z);

        glTexCoord2f(textCoords[Triangles[i]._1].x, textCoords[Triangles[i]._1].y);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

        if(smoothLight)
            glNormal3f(vectNormals[Triangles[i]._2].x, vectNormals[Triangles[i]._2].y, vectNormals[Triangles[i]._2].z);

        glTexCoord2f(textCoords[Triangles[i]._2].x, textCoords[Triangles[i]._2].y);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    if(flatLight || smoothLight)
        glDisable(GL_LIGHTING);
}

void _object3D::drawSelection()
{
    float R, G, B;

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
//    cout<<"DIBUJADO SELECCION:"<<endl;
        for(unsigned int i=0; i<Triangles.size();i++)
        {
            R = (i & 0x00FF0000) >> 16;
            G = (i & 0x0000FF00) >> 8;
            B = (i & 0x000000FF);

//            cout<<"COLOR: "<<R/255.0<<G/255.0<<B/255.0<<endl;
            glColor3f(R/255.0, G/255.0, B/255.0);

            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
    glEnd();
}

void _object3D::setTrigSelected(int trig)
{
    this->trigSelectedNumber = trig;
}

// Practice 4
void _object3D::calculateTrigNormals()
{
    int trigSize = Triangles.size();
    _vertex3f  vectorA, vectorB;
    double denominator;

    trigNormals.resize(trigSize);

    for(auto i=0; i<trigSize; i++)
    {
        // Vector A = p1 - p0
        vectorA.x = Vertices[Triangles[i]._1].x - Vertices[Triangles[i]._0].x;
        vectorA.y = Vertices[Triangles[i]._1].y - Vertices[Triangles[i]._0].y;
        vectorA.z = Vertices[Triangles[i]._1].z - Vertices[Triangles[i]._0].z;

        // Vector B = p2 - p0
        vectorB.x = Vertices[Triangles[i]._2].x - Vertices[Triangles[i]._0].x;
        vectorB.y = Vertices[Triangles[i]._2].y - Vertices[Triangles[i]._0].y;
        vectorB.z = Vertices[Triangles[i]._2].z - Vertices[Triangles[i]._0].z;

        // Vector Product = A . B
        trigNormals[i].x = (vectorA.y * vectorB.z) - (vectorA.z * vectorB.y);
        trigNormals[i].y = (vectorA.z * vectorB.x) - (vectorA.x * vectorB.z);
        trigNormals[i].z = (vectorA.x * vectorB.y) - (vectorA.y * vectorB.x);

        // Normalization
        //  Making the denominator, that is, square root of the vector product.
        denominator =  sqrt((pow(trigNormals[i].x, 2)) + (pow(trigNormals[i].y, 2)) + (pow(trigNormals[i].z, 2)));

        //  Properly normalizing, do not divide if denominator = 0.
        if(denominator != 0)
        {
            trigNormals[i].x /= denominator;
            trigNormals[i].y /= denominator;
            trigNormals[i].z /= denominator;
        }
    }

}

void _object3D::calculateVertNormals()
{
    int vectSize = Vertices.size();
    int trigSize = Triangles.size();
    vector<int> pointCount(vectSize,0);
    _vertex3f summation;
    vector<vector<int>> pointFace(vectSize);

    for(auto i = 0; i < trigSize; i++)
    {
        pointCount[Triangles[i].x]++;
        pointFace[Triangles[i].x].push_back(i);

        pointCount[Triangles[i].y]++;
        pointFace[Triangles[i].y].push_back(i);

        pointCount[Triangles[i].z]++;
        pointFace[Triangles[i].z].push_back(i);

    }

    vectNormals.resize(vectSize);
    for(auto i = 0; i < vectSize; i++)
    {
        summation.x = 0;
        summation.y = 0;
        summation.z = 0;

        while(!pointFace[i].empty())
        {
            summation.x += trigNormals[pointFace[i].back()].x;
            summation.y += trigNormals[pointFace[i].back()].y;
            summation.z += trigNormals[pointFace[i].back()].z;

            pointFace[i].pop_back();
        }
        summation.x /= pointCount[i];
        summation.y /= pointCount[i];
        summation.z /= pointCount[i];

        vectNormals[i] = summation;
    }
}


void _object3D::setLighting(int type)
{
    switch (type)
    {
        case 0:
            flatLight = false;
            smoothLight = false;
        break;

        case 1:
            flatLight = true;
            smoothLight = false;
        break;

        case 2:
            flatLight = false;
            smoothLight = true;
        break;

    }
}

void _object3D::setFlatLight()
{
    flatLight = true;
    smoothLight = false;

}

void _object3D::setSmoothLight()
{
    flatLight = false;
    smoothLight = true;
}


void _object3D::setMaterialDiffuse(_vertex3f color)
{
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *) &color);
}

void _object3D::setMaterialSpecular(_vertex3f color)
{
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &color);

}

void _object3D::setMaterialAmbient(_vertex3f color)
{
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *) &color);

}

void _object3D::setMaterialShininess(float color)
{
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, color);
}

void _object3D::setTexture(QImage Image)
{
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,3,Image.width(),Image.height(),0,GL_RGB,GL_UNSIGNED_BYTE,Image.bits());

}
// http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
