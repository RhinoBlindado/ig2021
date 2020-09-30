#include "cube.h"

_cube::_cube(float size)
{
    // Define the points.
    Vertices.resize(8);

    Vertices[0] = _vertex3f(size/2,size/2,-size/2);
    Vertices[1] = _vertex3f(-size/2,size/2,-size/2);
    Vertices[2] = _vertex3f(size/2,-size/2,-size/2);
    Vertices[3] = _vertex3f(-size/2,-size/2,-size/2);
    Vertices[4] = _vertex3f(size/2,size/2,size/2);
    Vertices[5] = _vertex3f(-size/2,size/2,size/2);
    Vertices[6] = _vertex3f(size/2,-size/2,size/2);
    Vertices[7] = _vertex3f(-size/2,-size/2,size/2);


    // Defining the faces as triangles.
    Triangles.resize(12);

    Triangles[0]=_vertex3ui(0,1,5);
    Triangles[1]=_vertex3ui(0,5,4);
    Triangles[2]=_vertex3ui(1,6,5);
    Triangles[3]=_vertex3ui(1,2,6);
    Triangles[4]=_vertex3ui(2,3,7);
    Triangles[5]=_vertex3ui(2,6,7);
    Triangles[6]=_vertex3ui(3,0,7);
    Triangles[7]=_vertex3ui(0,4,7);
    Triangles[8]=_vertex3ui(4,6,7);
    Triangles[9]=_vertex3ui(4,5,6);
    Triangles[10]=_vertex3ui(0,1,2);
    Triangles[11]=_vertex3ui(0,2,3);
}
