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
#include <QImage>

class _object3D:public _basic_object3D
{
  public:
  vector<_vertex3ui> Triangles;
  // [P4]
  vector<_vertex3f>  trigNormals;
  vector<_vertex3f>  vectNormals;
  vector<_vertex2f>  textCoords;

  // [P1] DRAWING
  void draw_line();
  void draw_fill();
  void draw_chess(vector<float> color1 = {1,0.4451,0.8078}, vector<float> color2 = {0.0039,0.8039,0.9961});
  void draw(int style = 0);

  // [P5]
  void drawSelection();

  // [P4] LIGHTING
  bool flatLight;
  bool smoothLight;

  void drawIlum();
  void drawTex();

  void calculateTrigNormals();
  void calculateVertNormals();

  void setLighting(int type);

  void setTexture(QImage texture);

  void setMaterialDiffuse(_vertex3f color);
  void setMaterialSpecular(_vertex3f color);
  void setMaterialAmbient(_vertex3f color);
  void setMaterialShininess(float color);

  // [P5] PICK
  int trigSelectedNumber = -1;
  void setTrigSelected(int trig);

  // [EXTRA]
  //    Exercise 2
  int minTriangle = -1, maxTriangle = -1;
  void getMinMaxTriangle();

  //    Exercise 3
  void fillEdges();

  //    Exercise 4
  float getVolume();

  //    Exercise 5
  void deleteTriangle(int _trig);

  //    Exam, 2b.
  bool isEuler();
};

#endif // OBJECT3D_H
