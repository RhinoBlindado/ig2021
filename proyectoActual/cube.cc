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

    Triangles[0]=_vertex3ui(0,3,2);
    Triangles[1]=_vertex3ui(0,3,1);

    Triangles[2]=_vertex3ui(1,5,7);
    Triangles[3]=_vertex3ui(1,7,3);

    Triangles[4]=_vertex3ui(5,6,4);
    Triangles[5]=_vertex3ui(5,6,7);

    Triangles[6]=_vertex3ui(4,6,2);
    Triangles[7]=_vertex3ui(4,0,2);

    Triangles[8]=_vertex3ui(2,3,7);
    Triangles[9]=_vertex3ui(2,7,6);

    Triangles[10]=_vertex3ui(0,1,5);
    Triangles[11]=_vertex3ui(0,5,4);
}
