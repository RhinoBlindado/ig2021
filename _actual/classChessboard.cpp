#include "classChessboard.h"

void _chessBoard::initialize(float row, float col)
{
  //  xScale = 1.7778;
  //  yScale = 1;
    row = 1;
    col = 1;

//    // Define the points.
//    Vertices.resize(4);

//    Vertices[0] = _vertex3f(-row/2, -col/2, 0);
//    Vertices[1] = _vertex3f(-row/2, col/2, 0);
//    Vertices[2] = _vertex3f(row/2, -col/2, 0);
//    Vertices[3] = _vertex3f(row/2, col/2, 0);

//    // Defining the triangles of the cube.
//    Triangles.resize(2);

//    //      Front face.
//    Triangles[0]=_vertex3ui(0,2,3);
//    Triangles[1]=_vertex3ui(0,3,1);

    //  Row Generation
    //      Bottom-Most Point
    Vertices.push_back(_vertex3f(-0.5*row,-0.5*col,0));

    //      Middle Points
    for(auto i=1; i < row; i++)
    {
        Vertices.push_back(_vertex3f(-0.5*row, -(0.5*col) + i, 0));
    }

    //      Top-Most Point
    Vertices.push_back(_vertex3f(-0.5*row, 0.5*col,0));


    // Column Generation
    int numVert = Vertices.size();
    float newX;

    for(auto i=1; i <= col; i++)
    {
        for(auto j=0; j < numVert; j++)
        {
           newX = Vertices[j].x + i;
           Vertices.push_back(_vertex3f(newX, Vertices[j].y, 0));
        }
    }


    // Triangle Generation
    int vertSize = Vertices.size();
    int plySizeVert = vertSize / numVert;
    for(int j = 0; j < numVert - 1; j++)
    {
        for(int i = 0; i < plySizeVert - 1; i++)
        {
            Triangles.push_back(_vertex3ui(i + j * plySizeVert, (i + (j+1) * plySizeVert), ((i+1) + (j+1) * plySizeVert)));
            Triangles.push_back(_vertex3ui(i + j * plySizeVert, ((i+1) + (j+1) * plySizeVert), (i+1) + j * plySizeVert));
        }
    }

    // Calculate Normals
    this->calculateTrigNormals();
    this->calculateVertNormals();

    // Map the texture
    this->mapTexture();
}

void _chessBoard::mapTexture()
{
    float MAX_X = (Vertices[Vertices.size()-1].x) * 2;
    float MAX_Y = (Vertices[Vertices.size()-1].y) * 2;

    textCoords.resize(Vertices.size());

    for(unsigned int i=0; i<Vertices.size();i++)
    {
        textCoords[i] = _vertex2f( 0.5 + (Vertices[i].x) / MAX_X,  0.5 + (Vertices[i].y) / MAX_Y);
    }

}
