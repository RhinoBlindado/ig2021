#include "classProfilePly.h"
#include "classObjectRevolution.h"
#include "file_ply_stl.h"
#include <cmath>

#define PI 3.14159265

_objPLYRev::_objPLYRev(float size, string path)
{
    path="../ply_revolutions/pawn.ply";

    // Declaracion variables para cargar PLY
    vector<float> plyObjVerts;
    vector<unsigned int> plyObjTrigs;
    vector<_vertex3f> auxVer;

    // Check for errors in input file.
    if(plyObjTrigs[0] < 3)
    {
        cout<<"plyRevolution error: Number of rotations is less than three."<<endl;
        exit(1);
    }

    if(plyObjTrigs[1] > 2)
    {
        cout<<"plyRevolution error: Incorrect axis indentifier. Must be 0, 1 or 2"<<endl;
        exit(1);
    }

    // Loading the vertices
    //  Obtaining the size of the generatrix curve, it's divided by 3 because plyObjVerts contains the XYZ points in a single vector.
    int plySizeVert = plyObjVerts.size() / 3;
    //  Capturing the points that touch the axis, the 'caps'.
    int numTapas = 0;
    for(auto i=0; i<plySizeVert; i++)
    {
        // 3*i refers to the X coordinate, 3*i+1 and 3*i+2 to Y and Z respectively.
        // If and X is 0, it touches the axis, it is a cap.
        if(plyObjVerts[3*i] == 0)
        {
            auxVer.push_back(_vertex3f(plyObjVerts[3*i]*size, plyObjVerts[3*i+1]*size, plyObjVerts[3*i+2]*size));
            numTapas++;
        }
        else
        {
            Vertices.push_back(_vertex3f(plyObjVerts[3*i]*size, plyObjVerts[3*i+1]*size, plyObjVerts[3*i+2]*size));
        }

    }

    if(numTapas > 2)
    {
        cout <<"plyRevolution: Error, numero de puntos tocando el eje excedido. Máx: 2"<<endl;
        exit(1);
    }

    // Realizando revolucion

    int rotation = plyObjTrigs[0];
    float alpha = 2*PI / rotation;
    float newX, newZ;
    plySizeVert = Vertices.size();

    for(auto i = 1; i < rotation; i++)
    {
        for(auto j = 0; j < plySizeVert; j++)
        {
            newX = Vertices[j].x * cos(alpha*i);
            newZ = -Vertices[j].x * sin(alpha*i);
            Vertices.push_back(_vertex3f(newX, Vertices[j].y, newZ));
        }
    }

    // Generando triangulos
    for(int j = 0; j < rotation - 1; j++)
    {
        for(int i = 0; i < plySizeVert - 1; i++)
        {
            Triangles.push_back(_vertex3ui(i + j * plySizeVert, (i + (j+1) * plySizeVert), ((i+1) + (j+1) * plySizeVert)));
            Triangles.push_back(_vertex3ui(i + j * plySizeVert, ((i+1) + (j+1) * plySizeVert), (i+1) + j * plySizeVert));
        }
    }

    for(int i = 0; i < plySizeVert - 1; i++)
    {
        Triangles.push_back(_vertex3ui(i + (rotation-1)  * plySizeVert, i, i+1));
        Triangles.push_back(_vertex3ui(i + (rotation-1) * plySizeVert, i+1, (i+1) + (rotation-1) * plySizeVert));
    }

    //  Añadiendo tapas
    switch (numTapas)
    {
        case 1:

        break;

        case 2:
            Vertices.push_back(auxVer[0]);
            Vertices.push_back(auxVer[1]);
            int l_aux = Vertices.size();
            for(int i = 0; i < rotation; i++)
            {
                Triangles.push_back(_vertex3ui(i * plySizeVert, l_aux-2, ((i+1) * plySizeVert) % (l_aux-2)));
                Triangles.push_back(_vertex3ui(l_aux-1, (plySizeVert-1)+ i * plySizeVert, ((plySizeVert-1) + (i+1) * plySizeVert) % (l_aux-2)));
            }
        break;

    }


    if(numTapas)
    {
        if(numTapas==1)
        {

        }
        else
        {

        }
    }

    // Realizando rotacion en ejes
    switch ((int) plyObjTrigs[1])
    {
        case 1:
            for(auto i = 0; i < (int) Vertices.size(); i++)
            {
                Vertices[i] = _vertex3f(Vertices[i].x, Vertices[i].y * cos(0.5 * PI) - Vertices[i].z * sin(0.5 * PI), Vertices[i].y * sin(0.5 * PI) + Vertices[i].z * cos(0.5 * PI));
            }
        break;

        case 2:
            for(auto i = 0; i < (int) Vertices.size(); i++)
            {
                Vertices[i] = _vertex3f(Vertices[i].x * cos(0.5 * PI) - Vertices[i].y * sin(0.5 * PI), Vertices[i].x * sin(0.5 * PI) + Vertices[i].y * cos(0.5 * PI), Vertices[i].z);
            }
        break;
    }
}
