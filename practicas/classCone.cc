#include "classCone.h"

/**
 * @brief Initialize the Cone Object.
 * @param height    Total height desired for the Cone. Default is 1.
 * @param radius    Desired radius for the Cone. Default is 0,5.
 * @param vCuts     Total number of vertical cuts for the Cone. Default is 20.
 * @param hCuts     Total number of horizontal cuts for the Cone. Default is 10.
 * @param rCuts     Total number of slices of the Cone, that is,
 *                  how many times the radius is cut. Default is 30.
 */
void _cone::initialize(float height, float radius, int vCuts, int hCuts, int rCuts)
{
    // Check for correct inputs
    if( height <= 0 )
    {
        cout<<"Cone: Height can't be zero or negative."<<endl;
        exit(1);
    }

    if( radius <= 0 )
    {
        cout<<"Cone: Radius can't be zero or negative."<<endl;
        exit(1);
    }

    if( hCuts < 1 || vCuts < 1 || rCuts < 3)
    {
        cout<<"Cone: Erroneous number of cuts"<<endl;
        exit(1);
    }

    // Bottom of profile, left-most point. Added to auxiliar list so that it's easier later to generate triangles correctly.
    vector<_vertex3f> auxVer;
    auxVer.push_back(_vertex3f(0, -height/2, 0));

    // Bottom length of cone.
    for(int i=1; i < hCuts; i++)
    {
        Vertices.push_back(_vertex3f((radius/hCuts)*i, -height/2, 0));
    }

    // Botton of profile, right-most point.
    Vertices.push_back(_vertex3f(radius, -height/2, 0));

    // Top length of cone.
    for(int i=1; i < vCuts; i++)
    {
        Vertices.push_back(_vertex3f(radius - ((radius/vCuts) * i), -(height/2) + ((height/vCuts) * i), 0));
    }

    // Top of profile, left-most point.
    auxVer.push_back(_vertex3f(0, height/2, 0));

    // Circular sweeping.
    this->rotation(rCuts);

    // Generating triangles.
    this->genTriangles(rCuts, true, true, auxVer);

    // [P4] Calculating normals.
    this->calculateTrigNormals();
    this->calculateVertNormals();


}
