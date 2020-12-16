#ifndef CLASSCHESSBOARD_H
#define CLASSCHESSBOARD_H

#include "object3d.h"


class _chessBoard:public _object3D
{
    public:
        _chessBoard(){};
        void initialize(int row=1, int col=1);
};

#endif // CLASSCHESSBOARD_H
