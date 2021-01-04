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

    // Originally, the top and bottom of the Sphere where in the auxVer so that it could reuse code of the _objRev class
    //auxVer.push_back(_vertex3f(0, -height/2, 0));
    Vertices.push_back(_vertex3f(0,-height/2, 0));

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
    //auxVer.push_back(_vertex3f(0, height/2, 0));
    Vertices.push_back(_vertex3f(0, height/2, 0));

    // Circular sweeping.
    //      [P2] Original function of the superclass.
    //_objRev::rotation(rCuts);
    //      [P4] New function that repeats points.
    this->rotation(rCuts);
    rCuts++;

    // Generating triangles.
    //      [P2] Original function of the superclass.
    //_objRev::genTriangles(rCuts, bottom, top, auxVer);
    //      [P4] New function, removed the code to add the last set of triangles. It needs rCuts to be one more in order
    //      to handle the repeated vertices.
    this->genTriangles(rCuts);

    // [P4] Calculating the normals.
    this->calculateTrigNormals();
    this->calculateVertNormals();

    // [P4] Mapping the texture.
    this->mapTexture(rCuts, hCuts, vCuts);

}

/**
 * [Practice 4]
 * @brief Redefinition of the Rotation class from _objRev so that it can map the texture.
 * @param rCuts    Total number of slices of the Cylinder, that is,
 *                 how many times the radius is cut
 */
void _cylinder::rotation(int rCuts)
{
    float alpha = 2*PI / rCuts;
    float newX, newZ;
    int plySizeVert = Vertices.size();

    for(auto i = 1; i < rCuts + 1; i++)
    {
        for(auto j = 0; j < plySizeVert; j++)
        {
            newX = Vertices[j].x * cos(alpha*i);
            newZ = -Vertices[j].x * sin(alpha*i);
            Vertices.push_back(_vertex3f(newX, Vertices[j].y, newZ));
        }
    }
}

void _cylinder::genTriangles(int rCuts)
{
    int vertSize = Vertices.size();
    int plySizeVert = vertSize / rCuts;

    for(int j = 0; j < rCuts - 1; j++)
    {
        for(int i = 0; i < plySizeVert - 1; i++)
        {
            Triangles.push_back(_vertex3ui(i + j * plySizeVert, (i + (j+1) * plySizeVert), ((i+1) + (j+1) * plySizeVert)));
            Triangles.push_back(_vertex3ui(i + j * plySizeVert, ((i+1) + (j+1) * plySizeVert), (i+1) + j * plySizeVert));
        }
    }
}

void _cylinder::mapTexture(int rCuts, int hCuts, int vCuts)
{

    int vertSize = Vertices.size();
    int plySizeVert = vertSize / rCuts;
    textCoords.resize(vertSize);

    /*
     * To map the texture between [0,1] the texture coordinates of each point are calculated based on the number of radius cuts,
     * that can be thought of as the Longitude line that goes from North to South and the number of vertices in each line of Longitude.
     */
    for(int j = 0; j < rCuts; j++)
    {
        for(int i = 0; i < plySizeVert; i++)
        {
            textCoords[i + ((plySizeVert) * j)] = _vertex2f( (1.0 / (rCuts - 1.0)) * (j), (1.0 / (plySizeVert - 1.0)) * (i) );
        }
    }

}
