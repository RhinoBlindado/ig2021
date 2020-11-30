#include "classCylinder.h"

_cylinder::_cylinder(float height, float radius, int vCuts, int hCuts, int rCuts, bool bottom, bool top)
{
    // START: Debug profile
//    height = 1;
//    radius = 0.5;
//    hCuts = 1;
//    vCuts = 1;
//    rCuts = 10;
    // END

    // Check for correct inputs
    if( height <= 0 )
    {
        cout<<"Cylinder: Height can't be zero or negative."<<endl;
        exit(1);
    }

    if( radius <= 0 )
    {
        cout<<"Cylinder: Radius can't be zero or negative."<<endl;
        exit(1);
    }

    if( hCuts < 1 || vCuts < 1 || rCuts < 3)
    {
        cout<<"Cylinder: Erroneous number of cuts"<<endl;
        exit(1);
    }

    // Bottom of profile, left-most point.
    vector<_vertex3f> auxVer;
    auxVer.push_back(_vertex3f(0, -height/2, 0));

    // Bottom length of cylinder.
    for(int i=1; i < hCuts; i++)
    {
        Vertices.push_back(_vertex3f((radius/hCuts)*i, -height/2, 0));
    }

    // Botton of profile, right-most point.
    Vertices.push_back(_vertex3f(radius, -height/2, 0));

    // Height of cylinder.
    for(int i=1; i < vCuts; i++)
    {
        Vertices.push_back(_vertex3f(radius, -(height/2) + ((height/vCuts)*i), 0));
    }

    // Top of profile, right-most point.
    Vertices.push_back(_vertex3f(radius, height/2, 0));

    // Top length of cylinder.
    for(int i=0; i < hCuts-1; i++)
    {
        Vertices.push_back(_vertex3f(Vertices[(hCuts-2)-i].x, -Vertices[(hCuts-2)-i].y, 0));
    }

    // Top of profile, left-most point.
    auxVer.push_back(_vertex3f(0, height/2, 0));

    // Circular sweeping.
    this->rotation(rCuts);

    // Generating triangles.
    this->genTriangles(rCuts, bottom, top, auxVer);

    // Calculating the normals.
    this->calculateNormals();


}
