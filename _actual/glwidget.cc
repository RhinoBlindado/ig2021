/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"
#include <cmath>

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
  Object = _gl_widget_ne::OBJECT_TETRAHEDRON;
}


/*****************************************************************************//**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
  case Qt::Key_1:Object=OBJECT_TETRAHEDRON;break;

  //Practice 1: Added Cube Key
  case Qt::Key_2:Object=OBJECT_CUBE;break;

  //Practice 2: Added PLY Object and Revolution Key
  case Qt::Key_3:Object=OBJECT_CONE;break;
  case Qt::Key_4:Object=OBJECT_CYLINDER;break;
  case Qt::Key_5:Object=OBJECT_SPHERE;break;
  case Qt::Key_6:Object=OBJECT_PLY;break;

  //Practice 3:
  //    - Added Hierarchical Model Key
  case Qt::Key_7:Object=OBJECT_HIER;break;

  //    - First degree of freedom keys and rate of modification
  case Qt::Key_Q:alpha+=ANGLE_STEP*modAlpha;break;
  case Qt::Key_W:alpha-=ANGLE_STEP*modAlpha;break;
  case Qt::Key_E:modAlpha+=0.5;break;
  case Qt::Key_R:modAlpha-=0.5;break;

  //    - Second degree of freedom keys and rate of modification
  case Qt::Key_S:beta+=ANGLE_STEP*modBeta;break;
  case Qt::Key_D:beta-=ANGLE_STEP*modBeta;break;
  case Qt::Key_T:modBeta+=0.5;break;
  case Qt::Key_Y:modBeta-=0.5;break;

  //    - Third degree of freedom keys and rate of modification
  case Qt::Key_Z:gamma+=ANGLE_STEP*modGamma;break;
  case Qt::Key_X:gamma-=ANGLE_STEP*modGamma;break;
  case Qt::Key_U:modGamma+=0.01;break;
  case Qt::Key_I:modGamma-=0.01;break;

  //    - Animation key
  case Qt::Key_A:animation=!animation;break;

  case Qt::Key_P:Draw_point=!Draw_point;break;
  case Qt::Key_L:Draw_line=!Draw_line;break;
  case Qt::Key_F:Draw_fill=!Draw_fill;break;
  case Qt::Key_C:Draw_chess=!Draw_chess;break;

  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_Minus:Observer_distance*=1.2;break;
  case Qt::Key_Plus:Observer_distance/=1.2;break;
  }

  this->constrainAngles();
  cout<<"ALPHA  :"<<alpha<<" ("<<modAlpha<<") BETA: "<<beta<<" ("<<modBeta<<")    GAMMA: "<<gamma<<" ("<<modGamma<<")"<<endl;
  update();
}


/*****************************************************************************//**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}



/*****************************************************************************//**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}



/*****************************************************************************//**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{
  Axis.draw_line();

//  _cylinder base(1,0.5,20,2,10);
//  _cylinder arm(1,0.5,20,2,10);

//  glPushMatrix();
//    glTranslatef(0,-0.5,0);
//    glScalef(5,1,1);
//    glRotatef(90,0,0,1);
//    base.draw_chess();
//  glPopMatrix();

//  glPushMatrix();
//    glColor3f(1,0,0);
//    glTranslatef(0,0.5,0);
//    glScalef(5,1,1);
//    glRotatef(90,0,0,1);
//    arm.draw_fill();
//  glPopMatrix();

//  _cube Cubitos;

//  glPushMatrix();
//    glTranslatef(1.5,2.5,1.5);
//    glScalef(1,5,1);
//    Cubitos.draw_chess();
//  glPopMatrix();

  if (Draw_point){
    glPointSize(5);
    glColor3fv((GLfloat *) &BLACK);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;

    // Added in Practice 1
    case OBJECT_CUBE:Cube.draw_point();break;

    // Added in Practice 2
    case OBJECT_CONE:Cone.draw_point();break;
    case OBJECT_CYLINDER:Cylinder.draw_point();break;
    case OBJECT_SPHERE:Sphere.draw_point();break;
    case OBJECT_PLY:Ply.draw_point();break;

    // Added in Practice 3
    case OBJECT_HIER:Hier.draw(0, alpha, beta, gamma);break;
    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(3);
    glColor3fv((GLfloat *) &MAGENTA);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;

    // Added in Practice 1
    case OBJECT_CUBE:Cube.draw_line();break;

    // Added in Practice 2
    case OBJECT_CONE:Cone.draw_line();break;
    case OBJECT_CYLINDER:Cylinder.draw_line();break;
    case OBJECT_SPHERE:Sphere.draw_line();break;
    case OBJECT_PLY:Ply.draw_line();break;

    // Added in Practice 3
    case OBJECT_HIER:Hier.draw(1, alpha, beta, gamma);break;
    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &BLUE);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;

    // Added in Practice 1
    case OBJECT_CUBE:Cube.draw_fill();break;

    // Added in Practice 2
    case OBJECT_CONE:Cone.draw_fill();break;
    case OBJECT_CYLINDER:Cylinder.draw_fill();break;
    case OBJECT_SPHERE:Sphere.draw_fill();break;
    case OBJECT_PLY:Ply.draw_fill();break;

    // Added in Practice 3
    case OBJECT_HIER:Hier.draw(2, alpha, beta, gamma);break;
    default:break;
    }
  }

  if (Draw_chess){
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;

    // Added in Practice 1
    case OBJECT_CUBE:Cube.draw_chess();break;

    // Added in Practice 2
    case OBJECT_CONE:Cone.draw_chess();break;
    case OBJECT_CYLINDER:Cylinder.draw_chess();break;
    case OBJECT_SPHERE:Sphere.draw_chess();break;
    case OBJECT_PLY:Ply.draw_chess();break;

    // Added in Practice 3
    case OBJECT_HIER:Hier.draw(3, alpha, beta, gamma);break;
    default:break;
    }
  }
}



/*****************************************************************************//**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}


/*****************************************************************************//**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
}


/*****************************************************************************//**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;

  //Practice 3: Initializing variables
  alpha = 0;
  beta  = 0;
  gamma = 0;
  modAlpha = 1;
  modBeta  = 1;
  modGamma = 1;
  animation = false;

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;
}


void _gl_widget::slotPoint(int state)
{
    if(state == Qt::Checked)
    {
        Draw_point = true;
    }
    else
    {
        Draw_point = false;
    }
    update();

}
void _gl_widget::slotLine(int state)
{

    if(state == Qt::Checked)
    {
        Draw_line = true;
    }
    else
    {
        Draw_line = false;
    }

    update();

}
void _gl_widget::slotFill(int state)
{
    if(state == Qt::Checked)
    {
        Draw_fill= true;
    }
    else
    {
        Draw_fill = false;
    }
    update();

}
void _gl_widget::slotChess(int state)
{
    if(state == Qt::Checked)
    {
        Draw_chess = true;
    }
    else
    {
        Draw_chess = false;
    }
    update();

}

void _gl_widget::slotModel(int index)
{
    switch(index)
    {
        case 0:Object=OBJECT_TETRAHEDRON;break;
        case 1:Object=OBJECT_CUBE;break;
        case 2:Object=OBJECT_CONE;break;
        case 3:Object=OBJECT_CYLINDER;break;
        case 4:Object=OBJECT_SPHERE;break;
        case 5:Object=OBJECT_PLY;break;
        case 6:Object=OBJECT_HIER;break;
    }
    update();
}

void _gl_widget::constrainAngles()
{
  if(beta > 42)
      beta = 42;

  if(beta < -42)
      beta = -42;

  if(gamma > 10)
      gamma = 10;

  if(gamma < -10)
      gamma = -10;

   alpha = fmod(alpha,360);
}


void _gl_widget::slotAnimationToggle()
{
    if(animation)
    {
        alpha += ANGLE_STEP*modAlpha;
        beta  += ANGLE_STEP*modBeta;
        gamma += ANGLE_STEP*modGamma;
        update();
    }
}
