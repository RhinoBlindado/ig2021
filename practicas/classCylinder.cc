#include "classCylinder.h"

/**
 * @brief Initialize the Cylinder Object
 * @param height    Total height desired for the Cylinder. Default is 1.
 * @param radius    Desired radius for the Cylinder. Default is 0,5.
 * @param hCuts     Total number of vertical cuts for the Cylinder. Default is 20.
 * @param vCuts     Total number of horizontal cuts for the Cylinder. Default is 10.
 * @param rCuts     Total number of slices of the Cylinder, that is,
 *                  how many times the radius is cut. Default is 30.
 * @param bottom    If the Cylinder should have a bottom "cap". Default is TRUE.
 * @param top       If the Cylinder should have a top "cap". Default is TRUE.
 */
void _cylinder::initialize(float height, float radius, int hCuts, int vCuts, int rCuts, bool bottom, bool top)
{
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
    this->genTriangles(rCuts, top, bottom, auxVer);

    // [P4] Calculating the normals.
    this->calculateTrigNormals();
    this->calculateVertNormals();

}
