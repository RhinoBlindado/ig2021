#include "plyRevolution.h"
#include "file_ply_stl.h"
#include <cmath>

#define PI 3.14159265

_plyRev::_plyRev(float size)
{
    //Seleccionar fichero
    //cout<<"SELECCIONAR FICHERO PLY: "<<endl;
    //cin>>file;
    string file="./ply_models/test.ply";

    // Declaracion variables para cargar PLY
    vector<float> plyObjVerts;
    vector<unsigned int> plyObjTrigs;
    _file_ply plyObj;

    // Abrir el archivo contenido en 'file'
    plyObj.open(file);
    plyObj.read(plyObjVerts,plyObjTrigs);

    // Cargando los vectices
    int plySizeVert = plyObjVerts.size() / 3;
    Vertices.resize(plySizeVert);

    for(auto i=0; i<plySizeVert; i++)
    {
        Vertices[i] = _vertex3f(plyObjVerts[3*i]*size, plyObjVerts[3*i+1]*size, plyObjVerts[3*i+2]*size);
    }

    // Cerrando el archivo PLY
    plyObj.close();

    // Realizando rotacion
    int rotation = 10;
    float alpha = 2*PI / rotation;
    float newX, newZ;

    for(auto i = 1; i < rotation; i++)
    {
        for(auto j = 0; j < plySizeVert; j++)
        {
            newX = Vertices[j].x * cos(alpha*i);
            newZ = -Vertices[j].x * sin(alpha*i);
            Vertices.push_back(_vertex3f(newX, Vertices[j].y, newZ));
        }
    }

    // Analizando por puntos tapa/base

    // Generando triangulos
    Triangles.resize(999);
    int tCount= 0, pCount = 0;
    for(auto i = 0; i < rotation; i++)
    {
        for(auto j = 0; j < plySizeVert; j++)
        {
            Triangles[tCount] = _vertex3ui(pCount, pCount + plySizeVert, pCount + plySizeVert + 1);
            Triangles[tCount+1] = _vertex3ui(pCount, pCount + plySizeVert + 1, pCount+1);
            tCount += 2;
            pCount++;
        }
    }



}
