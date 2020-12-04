#ifndef OBJECTPLY_H
#define OBJECTPLY_H
#include "classObjectRevolution.h"

class _ply:public _objRev
{
    public:
        _ply(){};
        void initialize(float size = 1, string path="../ply_models/rev_pawn.ply");
        void readFile(vector<float> &plyObjVerts, vector<unsigned int> &plyObjTrigs, string path);
        void objectPly(float size, vector<float> plyVert, vector<unsigned int> plyTrig);
        void profilePly(float size, vector<float> plyVert, vector<unsigned int> plyTrig);
};

#endif // OBJECTPLY_H
