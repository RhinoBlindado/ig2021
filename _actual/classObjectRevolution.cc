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

void _objRev::genTriangles(int rCuts, int caps, vector<_vertex3f> aux)
{

    int plySizeVert = Vertices.size() / rCuts;
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
        Triangles.push_back(_vertex3ui(i + (rCuts-1)  * plySizeVert, i, i+1));
        Triangles.push_back(_vertex3ui(i + (rCuts-1) * plySizeVert, i+1, (i+1) + (rCuts-1) * plySizeVert));
    }

    switch (caps)
    {
        case 1:

        break;

        case 2:
            Vertices.push_back(aux[0]);
            Vertices.push_back(aux[1]);
            int l_aux = Vertices.size();
            for(int i = 0; i < rCuts; i++)
            {
                Triangles.push_back(_vertex3ui(i * plySizeVert, l_aux-2, ((i+1) * plySizeVert) % (l_aux-2)));
                Triangles.push_back(_vertex3ui(l_aux-1, (plySizeVert-1)+ i * plySizeVert, ((plySizeVert-1) + (i+1) * plySizeVert) % (l_aux-2)));
            }
        break;

    }

}
