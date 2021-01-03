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

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _basic_object3D
{
  public:
  vector<_vertex3ui> Triangles;
  vector<_vertex2f>  textCoords;
  vector<_vertex3f>  trigNormals;
  vector<_vertex3f>  vectNormals;

  // Lighting Methods
  bool flatLight;
  bool smoothLight;
  void drawIlum();
  void drawTex();
  void calculateTrigNormals();
  void calculateVertNormals();

  // Drawing Methods
  void draw(int style = 0);
  void draw_line();
  void draw_fill();
  void draw_chess(vector<float> color1 = {1,0.4451,0.8078}, vector<float> color2 = {0.0039,0.8039,0.9961});
  void drawSelection();

  // Setters
  void setLighting(int type);
  void setFlatLight();
  void setSmoothLight();
  void setTexture(QImage texture);

  void setMaterialDiffuse(_vertex3f color);
  void setMaterialSpecular(_vertex3f color);
  void setMaterialAmbient(_vertex3f color);
  void setMaterialShininess(float color);

  // Interaction
  int trigSelectedNumber = -1;
  void setTrigSelected(int trig);

};

#endif // OBJECT3D_H
