#include "classSphere.h"

#define PI 3.14159265

void _sphere::initialize(float radius, int vCuts, int rCuts)
{
    // Check for correct inputs
    if( radius <= 0 )
    {
        cout<<"Sphere: Radius can't be zero or negative."<<endl;
        exit(1);
    }

    if( vCuts < 2 || rCuts < 3)
    {
        cout<<"Sphere: Erroneous number of cuts"<<endl;
        exit(1);
    }

    // Bottom of profile, left-most point.
    vector<_vertex3f> auxVer;
    //auxVer.push_back(_vertex3f(0, -radius, 0));
    Vertices.push_back(_vertex3f(0, -radius, 0));


    // Circumference
    float alpha = (PI / vCuts);
    float newX, newY;

    for(int i = 1; i < vCuts; i++)
    {
//        newX = auxVer[0].x * cos(alpha*i) - auxVer[0].y * sin(alpha*i);
//        newY = auxVer[0].x * sin(alpha*i) + auxVer[0].y * cos(alpha*i);
        newX = Vertices[0].x * cos(alpha*i) - Vertices[0].y * sin(alpha*i);
        newY = Vertices[0].x * sin(alpha*i) + Vertices[0].y * cos(alpha*i);
        Vertices.push_back(_vertex3f(newX, newY, 0));
    }

    // Top of profile, left-most point.
    //auxVer.push_back(_vertex3f(0, radius, 0));
    Vertices.push_back(_vertex3f(0, radius, 0));

    // Circular sweeping.
    this->rotation(rCuts);
    //_objRev::rotation(rCuts);

    // Generating triangles.
    this->genTriangles(rCuts + 1, true, true, auxVer);
    //_objRev::genTriangles(rCuts, true, true, auxVer);

    // Calculate the normals.
    this->calculateVertNormals();
    this->calculateTrigNormals();

    this->mapTexture(rCuts + 1);
}

void _sphere::calculateVertNormals()
{
    int vertSize = Vertices.size();
    double denominator;

    vectNormals.resize(vertSize);

    for(auto i = 0; i < vertSize; i++)
    {
        vectNormals[i].x = Vertices[i].x;
        vectNormals[i].y = Vertices[i].y;
        vectNormals[i].z = Vertices[i].z;

        // Normalization
        //  Making the denominator, that is, square root of the vector product.
        denominator =  sqrt((pow(vectNormals[i].x, 2)) + (pow(vectNormals[i].y, 2)) + (pow(vectNormals[i].z, 2)));

        //  Properly normalizing, do not divide if denominator = 0.
        if(denominator != 0)
        {
            vectNormals[i].x /= denominator;
            vectNormals[i].y /= denominator;
            vectNormals[i].z /= denominator;
        }

    }
}

void _sphere::calculateTrigNormals()
{
    int trigSize = Triangles.size();
    trigNormals.resize(trigSize);

    for(auto i = 0; i < trigSize ; i++)
    {
       trigNormals[i].x = (vectNormals[Triangles[i]._0].x + vectNormals[Triangles[i]._1].x + vectNormals[Triangles[i]._2].x) / 3;
       trigNormals[i].y = (vectNormals[Triangles[i]._0].y + vectNormals[Triangles[i]._1].y + vectNormals[Triangles[i]._2].y) / 3;
       trigNormals[i].z = (vectNormals[Triangles[i]._0].z + vectNormals[Triangles[i]._1].z + vectNormals[Triangles[i]._2].z) / 3;
    }

}

void _sphere::rotation(int rCuts)
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

void _sphere::genTriangles(int rCuts, bool bottomCap, bool topCap, vector<_vertex3f> caps)
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



void _sphere::mapTexture(int rCuts)
{

    int vertSize = Vertices.size();
    int plySizeVert = vertSize / rCuts;
    textCoords.resize(vertSize);

//    // Top vertex
//    textCoords[Vertices.size()-4] = _vertex2f(0, 0);
//    textCoords[Vertices.size()-3] = _vertex2f(1, 0);


//    // Bottom vertex
//    textCoords[Vertices.size()-2] = _vertex2f(0, 1);
//    textCoords[Vertices.size()-1] = _vertex2f(1, 1);


//    for(int i = 0; i < vertSize; i++)
//    {
//        cout<<"i="<<i<<" COORDS:"<<Vertices[i].x<<" "<<Vertices[i].y<<" "<<Vertices[i].z<<endl;
//    }
    // Main body

  //  cout<<"RCUTS:"<<rCuts<<" PLY:"<<plySizeVert<<" VECT:"<<vertSize<<endl;
    for(int j = 0; j < rCuts; j++)
    {
        for(int i = 0; i < plySizeVert; i++)
        {
            textCoords[i + ((plySizeVert) * j)] = _vertex2f( (1.0 / (rCuts - 1.0)) * (j), (1.0 / (plySizeVert - 1.0)) * (i) );

        //    cout<<"["<<i<<" "<<j<<"] VECT: "<<i + ((plySizeVert) * j)<<
  //                " COORD: "<<(1.0 / (rCuts - 1.0)) * (j)<<" "<<(1.0 / (plySizeVert - 1.0)) * (i)<<endl;
        }
  //      cout<<"---"<<endl;
    }
}
