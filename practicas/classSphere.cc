#include "classSphere.h"

/**
 * @brief Initialization of the Sphere Class
 * @param radius    The desired radius of the Sphere. Default is 0,5.
 * @param vCuts     Total number of vertical cuts for the Sphere. Default is 20.
 * @param rCuts     Total number of horizontal cuts for the Sphere. Default is 20.
 */
void _sphere::initialize(float radius, int vCuts, int rCuts)
{
    // Check for correct inputs
    if( radius <= 0 )
    {
        cout<<"Sphere: Radius can't be zero or negative."<<endl;
        exit(1);
    }

    if( vCuts < 2 || rCuts < 3)
    {
        cout<<"Sphere: Erroneous number of cuts"<<endl;
        exit(1);
    }

    // Bottom of profile, left-most point.
    vector<_vertex3f> auxVer;

    auxVer.push_back(_vertex3f(0, -radius, 0));
    Vertices.push_back(_vertex3f(0, -radius, 0));


    // Circumference
    float alpha = (PI / vCuts);
    float newX, newY;

    for(int i = 1; i < vCuts; i++)
    {
        newX = auxVer[0].x * cos(alpha*i) - auxVer[0].y * sin(alpha*i);
        newY = auxVer[0].x * sin(alpha*i) + auxVer[0].y * cos(alpha*i);
        Vertices.push_back(_vertex3f(newX, newY, 0));
    }

    // Top of profile, left-most point.
    auxVer.push_back(_vertex3f(0, radius, 0));

    // Circular sweeping.
    //      [P2] Original function of the superclass.
    //_objRev::rotation(rCuts);
    //      [P4] New function that repeats points.
    this->rotation(rCuts);

    // Generating triangles.
    this->genTriangles(rCuts, true, true, auxVer);


    // [P4] Calculate the normals.
    this->calculateVertNormals();
    this->calculateTrigNormals();
}

/**
 * @brief Calculate the Vertex Normals of the Sphere.
 * @details It's easier to first calculate the Vertex Normals since each vertex
 *          already makes a vector from the origin to its position, it only needs to
 *          be normalized.
 */
void _sphere::calculateVertNormals()
{
    int vertSize = Vertices.size();
    double denominator;

    vectNormals.resize(vertSize);

    for(auto i = 0; i < vertSize; i++)
    {
        vectNormals[i].x = Vertices[i].x;
        vectNormals[i].y = Vertices[i].y;
        vectNormals[i].z = Vertices[i].z;

        // Normalization
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
 * @brief Calculate the Triangle Normals of the Sphere.
 * @details It's the average of the Vertex Normals of each Triangle.
 */
void _sphere::calculateTrigNormals()
{
    int trigSize = Triangles.size();
    trigNormals.resize(trigSize);
    double denominator;

    for(auto i = 0; i < trigSize ; i++)
    {
       trigNormals[i].x = (vectNormals[Triangles[i]._0].x + vectNormals[Triangles[i]._1].x + vectNormals[Triangles[i]._2].x) / 3;
       trigNormals[i].y = (vectNormals[Triangles[i]._0].y + vectNormals[Triangles[i]._1].y + vectNormals[Triangles[i]._2].y) / 3;
       trigNormals[i].z = (vectNormals[Triangles[i]._0].z + vectNormals[Triangles[i]._1].z + vectNormals[Triangles[i]._2].z) / 3;

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
