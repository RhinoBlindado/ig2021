#include "classObjectRevolution.h"

/**
 * @brief Given a generatrix curve, generate a full set of vertices.
 * @param rCuts     Number of cuts to the radius.
 * @param axis      Axis of rotation, default is around the Y axis.
 */
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

/**
 * @brief Generate triangles given a list of vertices
 * @param rCuts     Number of cuts of the radius.
 * @param bottomCap If the object has a top cap.
 * @param topCap    If the object has a bottom cap.
 * @param caps      Pair of vertices that indicate the caps.
 */
void _objRev::genTriangles(int rCuts, bool bottomCap, bool topCap, vector<_vertex3f> caps)
{
    int vertSize = Vertices.size();

    // Number of vertices per slice
    int verticesPerSlice = vertSize / rCuts;

    /*
     * This loop goes up to rCuts-1 since the last set of triangles need to connect to the first ones. It's handled on other, separate loop.
     * It goes up to the penultimate vertex per slice since the last vertex won't connect with anything just yet. It connects with the top cap later.
     */
    for(int j = 0; j < rCuts - 1; j++)
    {
        for(int i = 0; i < verticesPerSlice - 1; i++)
        {
            // Odd Triangles: Current Vertex - Vertex to the right (j+1) - Vertex Diagonal to the right (i+1), (j+1)
            Triangles.push_back(_vertex3ui(i + j * verticesPerSlice, (i + (j+1) * verticesPerSlice), ((i+1) + (j+1) * verticesPerSlice)));

            // Even Triangles: Current Vertex - Vertex Diagonal to the right (i+1), (j+1) - Vertex on top (i+1)
            Triangles.push_back(_vertex3ui(i + j * verticesPerSlice, ((i+1) + (j+1) * verticesPerSlice), (i+1) + j * verticesPerSlice));
        }
    }

    // Complete the last set of triangles, those that connect the last set of vertices with the first ones.
    for(int i = 0; i < verticesPerSlice - 1; i++)
    {
        Triangles.push_back(_vertex3ui(i + (rCuts-1) * verticesPerSlice, i, i+1));
        Triangles.push_back(_vertex3ui(i + (rCuts-1) * verticesPerSlice, i+1, (i+1) + (rCuts-1) * verticesPerSlice));
    }

    // If the object has caps, add them to the list of vertices and generate the triangles accordingly.
    if(bottomCap)
    {
        Vertices.push_back(caps[0]);
        for(int i = 0; i < rCuts; i++)
        {           
            Triangles.push_back(_vertex3ui(i * verticesPerSlice, vertSize, ((i+1) * verticesPerSlice) % (vertSize)));
        }
    }

    if(topCap)
    {
        Vertices.push_back(caps[1]);
        for(int i = 0; i < rCuts; i++)
        {
            Triangles.push_back(_vertex3ui(Vertices.size()-1, (verticesPerSlice-1)+ i * verticesPerSlice, ((verticesPerSlice-1) + (i+1) * verticesPerSlice) % (vertSize)));
        }
    }
}
