#ifndef CLASSCHESSBOARD_H
#define CLASSCHESSBOARD_H

#include "object3d.h"


class _chessBoard:public _object3D
{
    public:
        _chessBoard(){};
        void initialize(float row=1, float col=1);
        void mapTexture();
};

#endif // CLASSCHESSBOARD_H
