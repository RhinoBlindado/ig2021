#include "classSphere.h"

#define PI 3.14159265

_sphere::_sphere(float radius, int vCuts, int rCuts)
{
    // START: Debug profile
    radius = 1;
    vCuts = 20;
    rCuts = 20;
    // END

    // Check for correct inputs
    if( radius <= 0 )
    {
        cout<<"Sphuere: Radius can't be zero or negative."<<endl;
        exit(1);
    }

    if( vCuts < 1 || rCuts < 3)
    {
        cout<<"Sphere: Erroneous number of cuts"<<endl;
        exit(1);
    }

    // Bottom of profile, left-most point.
    vector<_vertex3f> auxVer;
    auxVer.push_back(_vertex3f(0, -radius, 0));


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
    this->rotation(rCuts);

    // Generating triangles.
    this->genTriangles(rCuts, true, true, auxVer);
}

