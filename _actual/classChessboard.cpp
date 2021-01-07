#include "classChessboard.h"

/**
 * @brief Initializing the Chessboard.
 * @param xScale    Scale of Chessboard in the X Axis.
 * @param yScale    Scale of Chessboard in the Y Axis.
 */
void _chessBoard::initialize(float xScale, float yScale)
{
    // Define the points.
    Vertices.resize(4);

    Vertices[0] = _vertex3f(-xScale/2, -yScale/2, 0);
    Vertices[1] = _vertex3f(-xScale/2, yScale/2, 0);
    Vertices[2] = _vertex3f(xScale/2, -yScale/2, 0);
    Vertices[3] = _vertex3f(xScale/2, yScale/2, 0);

    // Defining the triangles of the chessboard.
    Triangles.resize(2);

    //      Front face.
    Triangles[0]=_vertex3ui(0,2,3);
    Triangles[1]=_vertex3ui(0,3,1);

//    //  Row Generation
//    //      Bottom-Most Point
//    Vertices.push_back(_vertex3f(-0.5*xScale,-0.5*yScale,0));

//    //      Middle Points
//    for(auto i=1; i < xScale; i++)
//    {
//        Vertices.push_back(_vertex3f(-0.5*xScale, -(0.5*yScale) + i, 0));
//    }

//    //      Top-Most Point
//    Vertices.push_back(_vertex3f(-0.5*xScale, 0.5*yScale,0));


//    // Column Generation
//    int numVert = Vertices.size();
//    float newX;

//    for(auto i=1; i <= yScale; i++)
//    {
//        for(auto j=0; j < numVert; j++)
//        {
//           newX = Vertices[j].x + i;
//           Vertices.push_back(_vertex3f(newX, Vertices[j].y, 0));
//        }
//    }


//    // Triangle Generation
//    int vertSize = Vertices.size();
//    int plySizeVert = vertSize / numVert;
//    for(int j = 0; j < numVert - 1; j++)
//    {
//        for(int i = 0; i < plySizeVert - 1; i++)
//        {
//            Triangles.push_back(_vertex3ui(i + j * plySizeVert, (i + (j+1) * plySizeVert), ((i+1) + (j+1) * plySizeVert)));
//            Triangles.push_back(_vertex3ui(i + j * plySizeVert, ((i+1) + (j+1) * plySizeVert), (i+1) + j * plySizeVert));
//        }
//    }

    // Calculate Normals
    this->calculateTrigNormals();
    this->calculateVertNormals();

    // Map the texture
    this->mapTexture();
}

/**
 * @brief   Method of mapping the texture to the Chessboard
 * @details The method can handle, if needed, a chessboard that
 *          has multiple triangles and map each triangle correctly
 *          to the texture.
 */
void _chessBoard::mapTexture()
{
    /*
     * In order to map the texture to a coordinate space
     * between [0,1]; get the upper right point of the chessboard, that
     * would be the last vertex, multiply by 2 since it's centered in 0 to
     * obtain the lenght of the chessboard in X and Y.
     */
    float MAX_X = (Vertices[Vertices.size()-1].x) * 2;
    float MAX_Y = (Vertices[Vertices.size()-1].y) * 2;

    textCoords.resize(Vertices.size());


    /*
     * For each vertex, divide it by the total lenght of the chessboard,
     * that way the max value is 1, and add 0.5 so that the min possible
     * value is 0. Every number maps between 0 and 1.
     */

    for(unsigned int i=0; i<Vertices.size();i++)
    {
        textCoords[i] = _vertex2f( 0.5 + (Vertices[i].x) / MAX_X,  0.5 + (Vertices[i].y) / MAX_Y);
    }

}
