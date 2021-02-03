#ifndef CLASSCHESSBOARD_H
#define CLASSCHESSBOARD_H

#include "object3d.h"

/**
 * [Practice 4]
 * @brief   Chessboard Class for displaying a texture on a flat surface
 */
class _chessBoard:public _object3D
{
    public:
        _chessBoard(){};
        void initialize(float height=1, float width=1, int hCuts=1, int wCuts=1);
        void mapTexture(float xSize, float ySize);
};

#endif // CLASSCHESSBOARD_H
