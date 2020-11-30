/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _basic_object3D
{
  public:
  vector<_vertex3ui> Triangles;
  vector<_vertex3f>  Normals;

  void draw(int style = 0);
  void draw_line();
  void draw_fill();
  void draw_chess(vector<float> color1 = {1,0.4451,0.8078}, vector<float> color2 = {0.0039,0.8039,0.9961});
  void calculateNormals();
};

#endif // OBJECT3D_H
