#include "classObjectRevolution.h"
#include "file_ply_stl.h"
#include <cmath>

#define PI 3.14159265

void _objRev::rotation(int rCuts)
{
    float alpha = 2*PI / rCuts;
    float newX, newZ;
    int plySizeVert = Vertices.size();

    for(auto i = 1; i < rCuts; i++)
    {
        for(auto j = 0; j < plySizeVert; j++)
        {
            newX = Vertices[j].x * cos(alpha*i);
            newZ = -Vertices[j].x * sin(alpha*i);
            Vertices.push_back(_vertex3f(newX, Vertices[j].y, newZ));
        }
    }
}


void _objRev::genTriangles(int rCuts, bool bottomCap, bool topCap, vector<_vertex3f> caps)
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

    for(int i = 0; i < plySizeVert - 1; i++)
    {
        Triangles.push_back(_vertex3ui(i + (rCuts-1) * plySizeVert, i, i+1));
        Triangles.push_back(_vertex3ui(i + (rCuts-1) * plySizeVert, i+1, (i+1) + (rCuts-1) * plySizeVert));
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
