#include "plyRevolution.h"
#include "file_ply_stl.h"
#include <cmath>

#define PI 3.14159265

_plyRev::_plyRev(float size)
{
    string file="../ply_revolutions/cylinder.ply";

    // Declaracion variables para cargar PLY
    vector<float> plyObjVerts;
    vector<unsigned int> plyObjTrigs;
    vector<_vertex3f> auxVer;
    _file_ply plyObj;

    // Abrir el archivo contenido en 'file'
    plyObj.open(file);
    plyObj.read(plyObjVerts,plyObjTrigs);

    // Cargando los vectices
    int plySizeVert = plyObjVerts.size() / 3;
    int numTapas = 0;
    for(auto i=0; i<plySizeVert; i++)
    {
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

    // Cerrando el archivo PLY
    plyObj.close();

    // Realizando rotacion
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
    if(numTapas)
    {
        if(numTapas==1)
        {

        }
        else
        {
            Vertices.push_back(auxVer[0]);
            Vertices.push_back(auxVer[1]);
            int l_aux = Vertices.size();
            for(int i = 0; i < rotation; i++)
            {
                Triangles.push_back(_vertex3ui(i * plySizeVert, l_aux-2, ((i+1) * plySizeVert) % (l_aux-2)));
                Triangles.push_back(_vertex3ui(l_aux-1, (plySizeVert-1)+ i * plySizeVert, ((plySizeVert-1) + (i+1) * plySizeVert) % (l_aux-2)));
            }
        }
    }
}
