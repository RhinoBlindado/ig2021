#include "plyObject.h"
#include "file_ply_stl.h"


_ply::_ply(float size)
{
    //Seleccionar fichero
    cout<<"SELECCIONAR FICHERO PLY: "<<endl;
    //cin>>file;
    string file="./ply_models/ant.ply";

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

    // Cargando los triangulos
    int plySizeTrig = plyObjTrigs.size() / 3;
    Triangles.resize(plySizeTrig);

    for(auto i=0; i<plySizeTrig; i++)
    {
        Triangles[i] = _vertex3ui(plyObjTrigs[3*i], plyObjTrigs[3*i+1], plyObjTrigs[3*i+2]);
    }

    // Cerrando el archivo PLY
    plyObj.close();
}
