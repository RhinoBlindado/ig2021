#include "classChessboard.h"

/**
 * @brief Initializing the Chessboard.
 * @param xScale    Scale of Chessboard in the X Axis.
 * @param yScale    Scale of Chessboard in the Y Axis.
 * @param xCuts     Number of cuts along the X Axis (Minimum 1).
 * @param yCuts     Number of cuts along the Y Axis (Minimum 1).
 */
void _chessBoard::initialize(float xScale, float yScale, int xCuts, int yCuts)
{
    // Bottom Left of Board
    Vertices.push_back(_vertex3f(-xScale/2, -yScale/2, 0));

    // Height Subdivisions
    for(int i = 1; i < xCuts; i++)
    {
        Vertices.push_back(_vertex3f(-xScale/2, -(yScale/2) + ((yScale/xCuts) * i), 0));
    }

    // Top Left of Board
    Vertices.push_back(_vertex3f(-xScale/2, yScale/2, 0));

    int rowSize = Vertices.size();

    // Moving the profile along the witdh
    for(int i = 1; i <= yCuts; i++)
    {
        for(int j = 0; j < rowSize; j++)
        {
            Vertices.push_back(_vertex3f( -(xScale/2) + ((xScale/yCuts) * i), Vertices[j].y, 0));
        }
    }

    // Generate triangles
    for(int j = 0; j < yCuts; j++)
    {
        for(int i = 0; i < rowSize - 1; i++)
        {
            // Odd Triangles: Current Vertex - Vertex to the right (j+1) - Vertex Diagonal to the right (i+1), (j+1)
            Triangles.push_back(_vertex3ui(i + j * rowSize, (i + (j+1) * rowSize), ((i+1) + (j+1) * rowSize)));

            // Even Triangles: Current Vertex - Vertex Diagonal to the right (i+1), (j+1) - Vertex on top (i+1)
            Triangles.push_back(_vertex3ui(i + j * rowSize, ((i+1) + (j+1) * rowSize), (i+1) + j * rowSize));
        }
    }

    // Calculate Normals
    this->calculateTrigNormals();
    this->calculateVertNormals();

    // Map the texture
    this->mapTexture(xScale, yScale);
}

/**
 * @brief   Method of mapping the texture to the Chessboard
 * @details The method can handle, if needed, a chessboard that
 *          has multiple triangles and map each triangle correctly
 *          to the texture.
 *
 * @param xScale    Scale of Chessboard in the X Axis.
 * @param yScale    Scale of Chessboard in the Y Axis.
 */
void _chessBoard::mapTexture(float xScale, float yScale)
{
    textCoords.resize(Vertices.size());

    /*
     * For each vertex, divide it by the total length of the chessboard,
     * that way the max value is 1, and add 0.5 so that the min possible
     * value is 0. Every number maps between 0 and 1.
     */

    for(unsigned int i=0; i<Vertices.size();i++)
    {
        textCoords[i] = _vertex2f( 0.5 + (Vertices[i].x) / xScale,  0.5 + (Vertices[i].y) / yScale);
    }

}
