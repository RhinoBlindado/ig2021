#include "classChessboard.h"

void _chessBoard::initialize(int row, int col)
{
    row = 3;
    col = 3;
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

}
