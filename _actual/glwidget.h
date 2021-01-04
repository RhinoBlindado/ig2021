/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

//#include <GL/gl.h>
#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>
#include "vertex.h"
#include "colors.h"
#include "axis.h"
#include "tetrahedron.h"

//  P1
#include "classCube.h"

//  P2
#include "classCone.h"
#include "classCylinder.h"
#include "classObjectPly.h"
#include "classObjectRevolution.h"
#include "classProfilePly.h"
#include "classSphere.h"

//  P3
#include "classTelescope.h"

//  P4
#include "classChessboard.h"
#include "classLights.h"

//  P5
#include "classScene.h"

namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE,OBJECT_CONE,OBJECT_CYLINDER,OBJECT_SPHERE,OBJECT_PLY,OBJECT_HIER,OBJECT_CHESS,OBJECT_SCENE} _object;
  typedef enum {MAT_GOLD, MAT_PLASTIC, MAT_RUBBER, MAT_NULL} _material;
  typedef enum {AMBIENT, DIFFUSE, SPECULAR, SHINE} _matProperty;
}
class _window;

struct  material
{
    _vertex3f diffuse;
    _vertex3f specular;
    _vertex3f ambient;
    float shine;
};


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();
  void constrainAngles();

  //    P4
  void lights();
  void getTexture(QImage _texture);

  //    P5
  void pick();

public slots:
  //    P2
  void slotPoint(int state);
  void slotLine(int state);
  void slotFill(int state);
  void slotChess(int state);
  void slotModel(int index);

  //    P3
  void slotAnimationToggle();

  //    P4
  void slotFlat(int state);
  void slotSmooth(int state);
  void slotUnlitText(int state);
  void slotFlatText(int state);
  void slotSmoothText(int state);

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

  //    P5
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private:
  _window *Window;
  _axis Axis;


  // MODELS
  _tetrahedron Tetrahedron;
  //    P1
  _cube Cube;

  //    P2
  _cone Cone;
  _cylinder Cylinder;
  _sphere Sphere;
  _ply Ply;

  //    P3
  _telescope Hier;

  //    P4
  _chessBoard Chess;
  _scene Scene;

  _gl_widget_ne::_object Object;


  // RENDER MODES
  bool Draw_point;
  //    P1
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;


  // [P3] ANIMATION
  //    Degrees of freedom and modifiers
  float alpha, beta, gamma, delta, modAlpha, modBeta, modGamma;
  //    Toggle ON/OFF the animation
  bool animation;
  bool foward1;
  bool foward2;


  // [P4] LIGHTING
  _lights light;
  //    Toggle Flat Ligting
  bool flatLit;
  //    Toggle Goraund Shading
  bool smoothLit;

  //    Toggle ON/OFF First Light
  bool firstLight;
  //    Toggle ON/OFF Second Light
  bool secondLight;


  // [P4] MATERIALS
  material __material[4];
  int actMaterial;


  // [P4] TEXTURES
  //    Load the texture
  QImage texture;

  //    Toggle Unlit Texture Mode
  bool unLitTextured;
  //    Toggle Flat Lit Texture Mode
  bool litFlatTextured;
  //    Toggle Smooth Lit Texture Mode
  bool litSmoothTextured;


  // [P5] CAMERA
  bool perspective;
  int lastClickX;
  int lastClickY;
  bool mouseDrag;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;

  // [P5] PICK
  int Window_width;
  int Window_height;
  int Selection_position_x;
  int Selection_position_y;

};

#endif
