#include "classCube.h"

/**
 * @brief Initialization of the Cube Class.
 * @param size      Size of the cube. Default is 1.
 */
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

    // Defining the triangles of the cube.
    Triangles.resize(12);

    //      Front face.
    Triangles[0]=_vertex3ui(0,2,3);
    Triangles[1]=_vertex3ui(0,3,1);

    //      Left face.
    Triangles[2]=_vertex3ui(1,7,5);
    Triangles[3]=_vertex3ui(1,3,7);

    //      Back face.
    Triangles[4]=_vertex3ui(5,6,4);
    Triangles[5]=_vertex3ui(5,7,6);

    //      Right side.
    Triangles[6]=_vertex3ui(4,6,2);
    Triangles[7]=_vertex3ui(4,2,0);

    //      Bottom side.
    Triangles[8]=_vertex3ui(2,7,3);
    Triangles[9]=_vertex3ui(2,6,7);

    //      Top side.
    Triangles[10]=_vertex3ui(0,1,5);
    Triangles[11]=_vertex3ui(0,5,4);


    // [P4] Calculate the normals
    this->calculateTrigNormals();
    this->calculateVertNormals();
}
