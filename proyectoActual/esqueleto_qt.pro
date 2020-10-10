HEADERS += \
  colors.h \
  basic_object3d.h \
  cube.h \
  file_ply_stl.h \
  object3d.h \
  axis.h \
  plyObject.h \
  plyRevolution.h \
  tetrahedron.h \
  glwidget.h \
  window.h

SOURCES += \
  basic_object3d.cc \
  cube.cc \
  file_ply_stl.cc \
  object3d.cc \
  axis.cc \
  plyObject.cc \
  plyRevolution.cc \
  tetrahedron.cc \
  main.cc \
  glwidget.cc \
  window.cc


LIBS += -L/usr/X11R6/lib64 -lGL


CONFIG += c++11
QT += widgets
