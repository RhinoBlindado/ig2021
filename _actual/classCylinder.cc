#include "classCylinder.h"

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
    this->genTriangles(rCuts + 1, bottom, top, auxVer);

    // Calculating the normals.
    this->calculateTrigNormals();
    this->calculateVertNormals();

   this->mapTexture(rCuts + 1);

}

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

void _cylinder::genTriangles(int rCuts, bool bottomCap, bool topCap, vector<_vertex3f> caps)
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

    if(bottomCap)
    {
        Vertices.push_back(caps[0]);
        for(int i = 0; i < rCuts; i++)
        {
            Triangles.push_back(_vertex3ui(i * plySizeVert, vertSize, ((i+1) * plySizeVert) % (vertSize)));
        }
    }

    if(topCap)
    {
        Vertices.push_back(caps[1]);
        for(int i = 0; i < rCuts; i++)
        {
            Triangles.push_back(_vertex3ui(Vertices.size()-1, (plySizeVert-1)+ i * plySizeVert, ((plySizeVert-1) + (i+1) * plySizeVert) % (vertSize)));
        }
    }
}

void _cylinder::mapTexture(int rCuts)
{

    int vertSize = (Vertices.size() - 2);
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
