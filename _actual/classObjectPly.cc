#include "classObjectPly.h"
#include "file_ply_stl.h"
#include <algorithm>    // std::reverse

#define PI 3.14159265

_ply::_ply(float size, string path)
{
    vector<float> plyObjVerts;
    vector<unsigned int> plyObjTrigs;
    path="../ply_models/rev_cylinder.ply";

    this->readFile(plyObjVerts, plyObjTrigs, path);
    if(plyObjTrigs.size() / 3 > 1)
        this->objectPly(size, plyObjVerts, plyObjTrigs);
    else
    {
        this->profilePly(size, plyObjVerts, plyObjTrigs);
    }

}

void _ply::readFile(vector<float> &plyObjVerts, vector<unsigned int> &plyObjTrigs, string path)
{
    // Declaracion variables para cargar PLY
    _file_ply plyObj;

    // Abrir el archivo contenido en 'file'
    plyObj.open(path);
    plyObj.read(plyObjVerts,plyObjTrigs);
    // Cerrando el archivo PLY
    plyObj.close();
}

void _ply::objectPly(float size, vector<float> plyVert, vector<unsigned int> plyTrig)
{
    // Cargando los vectices
    int plySizeVert = plyVert.size() / 3;
    Vertices.resize(plySizeVert);

    for(auto i=0; i<plySizeVert; i++)
    {
        Vertices[i] = _vertex3f(plyVert[3*i]*size, plyVert[3*i+1]*size, plyVert[3*i+2]*size);
    }

    // Cargando los triangulos
    int plySizeTrig = plyTrig.size() / 3;
    Triangles.resize(plySizeTrig);

    for(auto i=0; i<plySizeTrig; i++)
    {
        Triangles[i] = _vertex3ui(plyTrig[3*i], plyTrig[3*i+1], plyTrig[3*i+2]);
    }
}

void _ply::profilePly(float size, vector<float> plyVert, vector<unsigned int> plyTrig)
{

    // Declaracion variables para cargar PLY
    vector<_vertex3f> auxVer;
    auxVer.resize(2);
    bool hasTopCap = false,
         hasBottomCap = false;

    // Check for errors in input file.
    if(plyTrig[0] < 3)
    {
        cout<<"plyRevolution error: Number of rotations is less than three."<<endl;
        exit(1);
    }

    if(plyTrig[1] > 2)
    {
        cout<<"plyRevolution error: Incorrect axis indentifier. Must be Y: 0, Z: 1 or X: 2"<<endl;
        exit(1);
    }

    // Loading the vertices
    //  Obtaining the size of the generatrix curve, it's divided by 3 because plyObjVerts contains the XYZ points in a single vector.
    int plySizeVert = plyVert.size() / 3;
    //  Capturing the points that touch the axis, the 'caps'.
    int numTapas = 0;
    for(auto i=0; i<plySizeVert; i++)
    {
        // 3*i refers to the X coordinate, 3*i+1 and 3*i+2 to Y and Z respectively.
        // If a X coordinate is 0, it touches the axis, it is a cap.
        if(plyVert[3*i] == 0)
        {
            if(i == 0)
            {
                auxVer[0]=_vertex3f(plyVert[3*i]*size, plyVert[3*i+1]*size, plyVert[3*i+2]*size);
                hasBottomCap = true;
            }

            if(i == plySizeVert - 1)
            {
                auxVer[1]=_vertex3f(plyVert[3*i]*size, plyVert[3*i+1]*size, plyVert[3*i+2]*size);
                hasTopCap = true;
            }

            numTapas++;
            if(numTapas > 2)
            {
                cout <<"plyRevolution: Error, numero de puntos tocando el eje excedido. Máx: 2"<<endl;
                exit(1);
            }
        }
        else
        {
            Vertices.push_back(_vertex3f(plyVert[3*i]*size, plyVert[3*i+1]*size, plyVert[3*i+2]*size));
        }

    }

    // Checking the direction of the vertices
    if(auxVer[0].y > auxVer[1].y)
    {
        reverse(Vertices.begin(),Vertices.end());
        reverse(auxVer.begin(),auxVer.end());
        swap(hasTopCap,hasBottomCap);
    }

    // Circular sweeping.
    this->rotation(plyTrig[0]);

    // Generating triangles
    this->genTriangles(plyTrig[0], hasBottomCap, hasTopCap, auxVer);

    // Changing the main axis of rotation
    switch ((int) plyTrig[1])
    {
        // Default is around the Y axis.
        // Around the Z axis.
        case 1:
            for(auto i = 0; i < (int) Vertices.size(); i++)
            {
                Vertices[i] = _vertex3f(Vertices[i].x, Vertices[i].y * cos(0.5 * PI) - Vertices[i].z * sin(0.5 * PI), Vertices[i].y * sin(0.5 * PI) + Vertices[i].z * cos(0.5 * PI));
            }
        break;

        // Around the X axis.
        case 2:
            for(auto i = 0; i < (int) Vertices.size(); i++)
            {
                Vertices[i] = _vertex3f(Vertices[i].x * cos(-0.5 * PI) - Vertices[i].y * sin(-0.5 * PI), Vertices[i].x * sin(-0.5 * PI) + Vertices[i].y * cos(-0.5 * PI), Vertices[i].z);
            }
        break;
    }
}
