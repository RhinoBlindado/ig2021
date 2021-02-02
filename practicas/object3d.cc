/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include "object3d.h"
#include <cmath>
#include <cfloat>
#include <map>
#include <utility>
using namespace _colors_ne;

/*****************************************************************************//**
 * [P1]
 * @brief Draw in wireframe mode.
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
 * [P1]
 * @brief Draw in solid mode.
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

            if(this->maxTriangle == (int)i)
                    glColor3fv((GLfloat *) &RED);

            if(this->minTriangle == (int)i)
                    glColor3fv((GLfloat *) &CYAN);

            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);

            if(this->trigSelectedNumber == (int)i || this->maxTriangle == (int)i || this->minTriangle == (int)i)
                    glColor3fv((GLfloat *) &BLUE);
        }
    glEnd();
}

/*****************************************************************************//**
 * [P1]
 * @brief Draw in "chess" mode. Alternating colors.
 * @param color1 First color, default is light pink.
 * @param color2 Second color, default is light blue.
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

/**
 * [P3]
 * @brief Wrapper function made to make it easier for the hierarchical model to use all modes of drawing.
 * @param style     The style of draw to make.
 */
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

/**
 * [P4]
 * @brief Draw with ilumination. Flat and Goraund supported.
 */
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

/**
 * [P4]
 * @brief Draw with textures. Can be unlit, flat or Goraund lit.
 */
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

/**
 * [P4]
 * @brief Calculate the Triangle Normals.
 */
void _object3D::calculateTrigNormals()
{
    int trigSize = Triangles.size();
    _vertex3f  vectorA, vectorB;
    double denominator;

    trigNormals.resize(trigSize);

    for(auto i=0; i<trigSize; i++)
    {
        // Using the 3 points make 2 vectors and then obtain the vector product to get a perpendicular vector of the other 2.
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

/**
 * [P4]
 * @brief Calculate the Vertex Normals.
 */
void _object3D::calculateVertNormals()
{
    int vectSize = Vertices.size();
    int trigSize = Triangles.size();

    // How many times a Vertex appears in a Triangle.
    float trigCount;

    // What Triangles contain a certain Vertex.
    vector<vector<int>> pointFace(vectSize);


    /*
     * In order to obtain a vertex normal, first we need to know what triangles use that vertex.
     *
     * "pointFace" saves the Triangles that contain the indexed vertex.
     *
     * pointFace[Triangles[i]._0].push_back(i) is saving the ith Triangle in the index of the Vertex that appears on the 0 Component.
     */
    for(auto i = 0; i < trigSize; i++)
    {
        pointFace[Triangles[i]._0].push_back(i);

        pointFace[Triangles[i]._1].push_back(i);

        pointFace[Triangles[i]._2].push_back(i);
    }

    /*
     * In order to obtain the Vertex Normal, we need the average of all the Triangles that contain that Vertex, so, the first loop
     * runs through all the Vertices and for each one, in the while loop it sums the normals of the Triangles that contain the ith Vertex
     * and then averages the each component with the total number of Triangles.
     */
    vectNormals.resize(vectSize);
    _vertex3f summation;
    double denominator;

    for(auto i = 0; i < vectSize; i++)
    {
        summation.x = 0;
        summation.y = 0;
        summation.z = 0;

        trigCount = pointFace[i].size();

        // Adding the values of the normals of the Triangles.
        while(!pointFace[i].empty())
        {
            summation.x += trigNormals[pointFace[i].back()].x;
            summation.y += trigNormals[pointFace[i].back()].y;
            summation.z += trigNormals[pointFace[i].back()].z;

            pointFace[i].pop_back();
        }

        // Average of the normals.
        if(trigCount != 0)
        {
            summation.x /= trigCount;
            summation.y /= trigCount;
            summation.z /= trigCount;
        }

        vectNormals[i] = summation;

        // Normalization.
        //  Making the denominator, that is, square root of the vector product.
        denominator =  sqrt((pow(vectNormals[i].x, 2)) + (pow(vectNormals[i].y, 2)) + (pow(vectNormals[i].z, 2)));

        //  Properly normalizing, do not divide if denominator = 0.
        if(denominator != 0)
        {
            vectNormals[i].x /= denominator;
            vectNormals[i].y /= denominator;
            vectNormals[i].z /= denominator;
        }
    }
}

/**
 * [P5]
 * @brief Draw the objects in a solid mode but each triangle has a different color. Used for selecting a triangle.
 */
void _object3D::drawSelection()
{
    float R, G, B;

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);

        for(unsigned int i=0; i<Triangles.size();i++)
        {
            // For a given triangle, convert its index into a color using bitmasking.
            R = (i & 0x00FF0000) >> 16;
            G = (i & 0x0000FF00) >> 8;
            B = (i & 0x000000FF);

            //  Use the mask to make a color.
            glColor3f(R/255.0f, G/255.0f, B/255.0f);

            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
    glEnd();
}

/**
 * [P5]
 * @brief Select a triangle.
 * @param trig      The index/ID of the triangle.
 */
void _object3D::setTrigSelected(int trig)
{
    this->trigSelectedNumber = trig;
}


/**
 * [P4]
 * @brief Set the lighting of the object.
 * @param type      0 - Unlit | 1 - Flat Lit | 2 - Goraund Lit
 */
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

    glTexImage2D(GL_TEXTURE_2D, 0, 3, Image.width(), Image.height(), 0, GL_RGB,GL_UNSIGNED_BYTE, Image.bits());

}

/** [EXTRA]
 * @brief Gets the minimum and maximum sized triangles of a given object.
 * @details See 'docs/Problema 2 - Triangulo Mayor y Menor.pdf'
 */
void _object3D::getMinMaxTriangle()
{
    float area, minTrig = FLT_MAX, maxTrig = -1.0;
    _vertex3f  vectorA, vectorB, vectorC;
    for(int i=0; i<(int)Triangles.size(); i++)
    {
        // Using the 3 points make 2 vectors and then obtain the vector product to get a perpendicular vector of the other 2.
        // Vector A = p1 - p0
        vectorA.x = Vertices[Triangles[i]._1].x - Vertices[Triangles[i]._0].x;
        vectorA.y = Vertices[Triangles[i]._1].y - Vertices[Triangles[i]._0].y;
        vectorA.z = Vertices[Triangles[i]._1].z - Vertices[Triangles[i]._0].z;

        // Vector B = p2 - p0
        vectorB.x = Vertices[Triangles[i]._2].x - Vertices[Triangles[i]._0].x;
        vectorB.y = Vertices[Triangles[i]._2].y - Vertices[Triangles[i]._0].y;
        vectorB.z = Vertices[Triangles[i]._2].z - Vertices[Triangles[i]._0].z;

        // Vector Product = A x B
        vectorC.x = (vectorA.y * vectorB.z) - (vectorA.z * vectorB.y);
        vectorC.y = (vectorA.z * vectorB.x) - (vectorA.x * vectorB.z);
        vectorC.z = (vectorA.x * vectorB.y) - (vectorA.y * vectorB.x);

        // Normalization
        // The area of a triangle is half the length of the normal vector
        area =  0.5 * sqrt((pow(vectorC.x, 2)) + (pow(vectorC.y, 2)) + (pow(vectorC.z, 2)));

        if(area > maxTrig)
        {
            maxTrig = area;
            this->maxTriangle = i;
        }

        if(area < minTrig)
        {
            minTrig = area;
            this->minTriangle = i;
        }
    }
}

/** [EXTRA]
 * @brief Auxiliar function to obtain the absolute value of a float number.
 * @param _number   Input float number
 * @return  Absolute value of number
 */
float absolute(float _number)
{
    return (_number < 0) ? -_number : _number;
}


/** [EXTRA]
 * @brief   Aproximates the volume of an object.
 * @return  Aproximate volume of given object.
 * @details See 'docs/Problema 4 - Volumen de un Modelo.pdf'
 */
float _object3D::getVolume()
{
    /* In order to aproximate the volume of an object, it is safe to think of an object as a bunch of triangles.
     *
     * These triangles can be then made into tetrahedrons, three points from the triangle and the fourth from the origin (0, 0, 0) point.
     *
     * Then the volume of the given tetrahedron is calculated, the formula is V = (1/6) * |a . (b x c)| with '.' being the dot product and 'x' the
     * cross product, a, b and c are each of the points of the triangle.
     *
     * Iterate over all the triangles and sum the volumes.
     */

    float volume = 0.0;
    _vertex3f a, b, c, vecProd;

    for(uint i = 0; i < Triangles.size(); i++)
    {
        a = Vertices[Triangles[i]._0];
        b = Vertices[Triangles[i]._1];
        c = Vertices[Triangles[i]._2];

        // Vector Product = b x c
        vecProd.x = (b.y * c.z) - (b.z * c.y);
        vecProd.y = (b.z * c.x) - (b.x * c.z);
        vecProd.z = (b.x * c.y) - (b.y * c.x);

        // V = (1/6 = 0.1666...) * |a . (b x c) |
        volume = volume + ( (0.1666667) * absolute((a.x * vecProd.x) + (a.y * vecProd.y) + (a.z * vecProd.z)) );
    }

    return volume;
}


/** [EXTRA]
 * @brief Deletes a triangle while preserving topology.
 * @param _trig     The triangle to delete.
 * @details See 'docs/Problema 5 - Eliminación de Triángulo.pdf'
 * @note This function produces degenerate triangles.
 */
void _object3D::deleteTriangle(int _trig)
{
    vector<_vertex3f> trigVertices;
    _vertex3f nPoint;
    int vertexNumber;

    trigVertices.resize(3);

    // Save the vertices of the triangle to be deleted.
    trigVertices[0] = Vertices[Triangles[_trig]._0];
    trigVertices[1] = Vertices[Triangles[_trig]._1];
    trigVertices[2] = Vertices[Triangles[_trig]._2];

    // nPoint defines the new point where the remaining triangles will converge, it is the middle of the triangle to be removed.
    nPoint.x = (trigVertices[0].x + trigVertices[1].x + trigVertices[2].x) / 3;
    nPoint.y = (trigVertices[0].y + trigVertices[1].y + trigVertices[2].y) / 3;
    nPoint.z = (trigVertices[0].z + trigVertices[1].z + trigVertices[2].z) / 3;

    // Add the point to the list of vertices.
    Vertices.push_back(nPoint);
    vertexNumber = Vertices.size() - 1;

    // Delete the triangle
    Triangles.erase(Triangles.begin() + _trig);

    /* Iterate over all triangles, if any points of the ith triangle formed the deleted triangle, then change that point to
     * the new point (nPoint).
     *
     * It has to be checked for all three points and for each of the 3 points of the deleted triangles.
     */


    for(uint i = 0; i < Triangles.size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(Vertices[Triangles[i]._0] == trigVertices[j])
                Triangles[i]._0 = vertexNumber;

            if(Vertices[Triangles[i]._1] == trigVertices[j])
                Triangles[i]._1 = vertexNumber;

            if(Vertices[Triangles[i]._2] == trigVertices[j])
                Triangles[i]._2 = vertexNumber;
        }
    }
}


/** [EXTRA]
 * @brief Checks that the object complies with Euler's polyhedron formula, ( V - E + F = 2 ).
 * @return  Boolean value indicating if the object complies with Euler's polyhedron formula.
 * @details See 'docs/Prado - Examen Ordinaria Teoria 1819.pdf', 2b.
 */
bool _object3D::isEuler()
{
    int sizeVertex = Vertices.size(), sizeTriangles = Triangles.size();
    map <std::pair<int, int>, int> side;

    /* In order to know if there are the correct number of sides, the map container is used to save a pair of points as a key, if the contents
     * are 1, then it means that that side already has been acounted for, the function checks for (p0, p1) and (p1, p0) since it's the same side.
     * If 0, then it hasn't been acounted and maps it.
     */

    for(uint i=0; i<Triangles.size(); i++)
    {
        if(side.count(std::make_pair(Triangles[i]._0, Triangles[i]._1)) == 0 && side.count(std::make_pair(Triangles[i]._1, Triangles[i]._0)) == 0)
        {
            side.emplace(std::make_pair(Triangles[i]._0, Triangles[i]._1), 1);
        }

        if(side.count(std::make_pair(Triangles[i]._0, Triangles[i]._2)) == 0 && side.count(std::make_pair(Triangles[i]._2, Triangles[i]._0)) == 0)
        {
            side.emplace(std::make_pair(Triangles[i]._0, Triangles[i]._2), 1);
        }

        if(side.count(std::make_pair(Triangles[i]._1, Triangles[i]._2)) == 0 && side.count(std::make_pair(Triangles[i]._2, Triangles[i]._1)) == 0)
        {
            side.emplace(std::make_pair(Triangles[i]._1, Triangles[i]._2), 1);
        }
    }

    // If the size of the map container checks the formula, then it complies with Euler's formula.
    return sizeVertex+sizeTriangles-2 == (int)side.size();
}
